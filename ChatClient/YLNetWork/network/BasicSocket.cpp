/*================================================================
*   
*   文件名称: BasicSocket.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午11:48
*
================================================================*/


#include "BasicSocket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include "../util/util.h"
#include "EventDispatch.h"
using namespace youliao::network;


typedef __gnu_cxx::hash_map<net_handle_t, BaseSocket*> SocketMap;
SocketMap g_socket_map;

BaseSocket* youliao::network::findBaseSocket(net_handle_t handle)
{
    auto iter = g_socket_map.find(handle);
    if (iter == g_socket_map.end())
        return nullptr;
    else
        return iter->second;
}

void addBaseSocket(BaseSocket* pSock)
{
    g_socket_map.insert(std::make_pair(pSock->getHandle(), pSock));
}

void removeBaseSocket(BaseSocket* pSock)
{
    g_socket_map.erase(pSock->getHandle());
}


BaseSocket::BaseSocket()
{
    m_state = BASESOCKET_STATE_IDLE;
    m_callback = nullptr;
    m_callback_data = nullptr;


    m_handle = socket(AF_INET, SOCK_STREAM, 0);
}

BaseSocket::~BaseSocket()
{

}

int BaseSocket::listen(const std::string &serv_ip, uint16_t port, callback_t callback, callback_data data)
{
    if (m_handle == NETWORK_ERROR)
        return NETWORK_ERROR;

    m_callback = callback;
    m_callback_data = data;

    _SetNonBlock();
    _SetReuseAddr();

    sockaddr_in t_sockaddr;
    _SetSockAddr(serv_ip, port, t_sockaddr);

    int ret = ::bind(m_handle, (sockaddr*)&t_sockaddr, sizeof(sockaddr));

    if (ret == NETWORK_ERROR)
    {
        log("bind address(%s:%d) failed, error str = %s", serv_ip.c_str(), port, _GetErrorStr());
        ::close(m_handle);
        return NETWORK_ERROR;
    }
    ret = ::listen(m_handle, 64);

    if (ret == NETWORK_ERROR)
    {
        log("listen failed, error str = %s", _GetErrorStr());
        ::close(m_handle);
        return NETWORK_ERROR;
    }

    //正在监听中, 将m_state设置未BASESOCKET_STATE_LISTENING 表明当前的socket用来接受连接.
    m_state = BASESOCKET_STATE_LISTENING;
    log("listen on (%s:%d)", serv_ip.c_str(), port);
    addBaseSocket(this);
    EventDispatch::instance()->addEvent(m_handle);

    return 0;
}

int BaseSocket::connect(const std::string &serv_ip, uint16_t port, callback_t callback, callback_data data)
{
    if (m_handle == NETWORK_ERROR)
        return NETWORK_ERROR;

    m_callback = callback;
    m_callback_data = data;

    sockaddr_in t_sockaddr;
    _SetSockAddr(serv_ip, port, t_sockaddr);

    int ret = ::connect(m_handle, (sockaddr*)&t_sockaddr, sizeof(t_sockaddr));

    if (ret == NETWORK_ERROR) {
        log("error str = %s", _GetErrorStr());
        return NETWORK_ERROR;
    }

    _SetNonBlock();
    _SetNoDelay();
    m_state = BASESOCKET_STATE_CONNECTING;

    //加入全局map
    //添加事件
    addBaseSocket(this);
    EventDispatch::instance()->addEvent(m_handle);

    return m_handle;
}

int BaseSocket::close()
{
    EventDispatch::instance()->removeEvent(m_handle);
    removeBaseSocket(this);
    return ::close(m_handle);
}

ssize_t BaseSocket::send(void *buf, size_t len)
{
    if (m_state != BASESOCKET_STATE_CONNECTED)
    {
        return -1;
    }

    ssize_t ret = ::send(m_handle, buf, len, 0);
    return ret;
}

ssize_t BaseSocket::recv(void *buf, size_t len)
{
    ssize_t ret = ::recv(m_handle, buf, len, 0);
    return ret;
}

void BaseSocket::_SetSockAddr(const std::string &ip, uint16_t port, sockaddr_in &sock_addr)
{
    memset(&sock_addr, 0, sizeof(sockaddr_in));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(port);
    if (ip.empty())
        sock_addr.sin_addr.s_addr = INADDR_ANY;
    else
        sock_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

void BaseSocket::_SetNoDelay()
{
    int noDelay = 1;
    int ret = setsockopt(m_handle, IPPROTO_IP, TCP_NODELAY, &noDelay, sizeof(int));
    if (ret == -1)
    {
        log("set socket %d nodelay failed, error strr = %s", m_handle, _GetErrorStr());
    }
}

void BaseSocket::_SetReuseAddr()
{
    int reuse = 1;
    int ret = setsockopt(m_handle, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    if (ret == -1)
    {
        log("set socket %d reuse address failed, error str = %s", m_handle, _GetErrorStr());
    }
}

void BaseSocket::_SetNonBlock()
{
    int ret = fcntl(m_handle, F_SETFL, O_NONBLOCK | fcntl(m_handle, F_GETFL));
    if (ret == -1)
    {
        log("set socket %d nonblock failed, error str = %s", m_handle, _GetErrorStr());
    }
}

int BaseSocket::_GetErrorCode()
{
    return errno;
}

char* BaseSocket::_GetErrorStr()
{
    return strerror(_GetErrorCode());
}

void BaseSocket::onRead()
{
    //只有监听socket可读时是有连接进入
    if (m_state == BASESOCKET_STATE_LISTENING)
    {
        _AcceptNewConn();
    }
    else
    {
        //获取socket可读字节数
        u_long avail = 0;
        int ret = ioctl(m_handle, FIONREAD, &avail);

        if (avail == 0 || ret == -1)
        {
            log("socket %d get avail bytes failed, error str = %s", m_handle, _GetErrorStr());
            m_callback(m_callback_data, NETWORK_CLOSE, m_handle, NULL);
        }
        else
        {
            //通过回调函数去读数据
            m_callback(m_callback_data, NETWORK_READ, m_handle, NULL);
        }
    }
}

void BaseSocket::onWrite()
{
    //建立连接后第一次读之前
    if (m_state == BASESOCKET_STATE_CONNECTING)
    {
        //判断m_handle有没有错误
        int error = 0;
        socklen_t len = sizeof(int);
        getsockopt(m_handle, SOL_SOCKET, SO_ERROR, &error, &len);

        if (error)
        {
            m_callback(m_callback_data, NETWORK_ERROR, m_handle, NULL);
        }
        else
        {
            //连接成功建立
            m_state = BASESOCKET_STATE_CONNECTED;
            m_callback(m_callback_data, NETWORK_WRITE, m_handle, NULL);
        }
    }
    else if (m_state == BASESOCKET_STATE_CONNECTED)
        m_callback(m_callback_data, NETWORK_WRITE, m_handle, NULL);
}

void BaseSocket::onClose()
{
    m_state = BASESOCKET_STATE_CLOSE;
    close();
}

void BaseSocket::_AcceptNewConn()
{
    sockaddr_in t_sockaddr;
    socklen_t  len = sizeof(sockaddr_in);
    net_handle_t t_handle;
    char str_ip[64];
    while ( (t_handle = accept(m_handle, (sockaddr*)&t_sockaddr, &len)) != -1)
    {
        uint32_t ip = ntohl(t_sockaddr.sin_addr.s_addr);
        uint16_t port = ntohs(t_sockaddr.sin_port);
        //将ip地址转换成形如:0.0.0.0
        snprintf(str_ip, sizeof(str_ip), "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);

        log("Accept new connect from (%s:%d)", str_ip, port);

        BaseSocket *t_basesocket = new BaseSocket;
        t_basesocket->setHandle(t_handle);
        t_basesocket->setSocketState(BASESOCKET_STATE_CONNECTED);
        t_basesocket->_SetNoDelay();
        t_basesocket->_SetNonBlock();
        t_basesocket->setCallBack(m_callback);
        t_basesocket->setCallBackData(m_callback_data);

        addBaseSocket(t_basesocket);
        EventDispatch::instance()->addEvent(t_handle);

        m_callback(m_callback_data, NETWORK_CONNECT, t_handle, NULL);
    }
}