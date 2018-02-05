//
// Created by liuzheng on 18-2-4.
//
/***
 * 关于listen和connect， 同一个实例只会调用两者之一
 * 前者是用于接受连接后者发起连接。
 * 通过 m_state 区分是接受还是发起连接
 *
 */

#include "YLBaseSocket.h"
#include "YLEventDispatch.h"

typedef __gnu_cxx::hash_map<int, YLBaseSocket*> SocketMap;
SocketMap g_socket_map;

void addBaseSocket(YLBaseSocket *pSocket)
{
    g_socket_map.insert(std::make_pair(pSocket->getSocket(), pSocket));
}

void removeBaseSocket(YLBaseSocket *pSocket)
{
    g_socket_map.erase(pSocket->getSocket());
}

YLBaseSocket* findBaseSocket(int fd)
{
    YLBaseSocket *pSocket = nullptr;

    auto iter = g_socket_map.find(fd);

    if (iter != g_socket_map.end())
    {
        pSocket = iter->second;
    }

    return pSocket;
}

YLBaseSocket::YLBaseSocket()
{
    m_socket = -1;
    m_state = SOCKET_STATE_IDLE;
}

YLBaseSocket::~YLBaseSocket()
{

}

int YLBaseSocket::listen(const std::string &server_ip, uint16_t port, callback_t callback, void *callback_data)
{

    m_callback = callback;
    m_callback_data = callback_data;

    m_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_socket == -1)
    {
        log("socket failed, error_code = %d \n", _GetErrorCode());
        return -1;
    }

    _SetReuseAddr(m_socket);
    _SetNonBlock(m_socket);

    sockaddr_in serv_addr;
    _SetAddr(server_ip, port, &serv_addr);
    int ret = ::bind(m_socket, (struct sockaddr*)&serv_addr, sizeof(sockaddr));
    if (ret == -1)
    {
        log("bind failed, error_code = %d", _GetErrorCode());
        ::close(m_socket);
        return -1;
    }

    ret = ::listen(m_socket, 64);
    if (ret == -1)
    {
        log("listen failed, error_code = %d\n", _GetErrorCode());
        ::close(m_socket);
        return -1;
    }


    m_state = SOCKET_STATE_LISTENING;

    log("YLBaseSocket::listen on %s:%d\n", server_ip.c_str(), port);

    addBaseSocket(this);
    YLEventDispatch::getInstance()->addEvent(m_socket, SOCKET_READ | SOCKET_EXCEP);
    return 0;
}


int YLBaseSocket::connect(const std::string &server_ip, uint16_t port, callback_t callback, void *callback_data)
{
    m_remote_ip = server_ip;
    m_remote_port = port;
    m_callback_data = callback_data;
    m_callback = callback;

    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1)
    {
        log("socket failed, error_code = %d \n", _GetErrorCode());
        return -1;
    }

    _SetNonBlock(m_socket);
    _SetNoDelay(m_socket);
    sockaddr_in serv_addr;
    _SetAddr(server_ip, port, &serv_addr);

    int ret = ::connect(m_socket, (sockaddr*)&serv_addr, sizeof(serv_addr));
    if ( (ret == -1) && !_IsBlock(_GetErrorCode()))
    {
        log("connect failed, err_code=%d", _GetErrorCode());
        ::close(m_socket);
        return -1;
    }

    m_state = SOCKET_STATE_CONNECTING;

    addBaseSocket(this);
    YLEventDispatch::getInstance()->addEvent(m_socket, SOCKET_ALL);
    return m_socket;
}

int YLBaseSocket::send(void *buf, int len)
{
    if (m_state != SOCKET_STATE_CONNECTED)
        return -1;

    int ret = ::send(m_socket, (char*)buf, len, 0);
    if (ret == -1)
    {
        if (_IsBlock(_GetErrorCode()))
            ret = 0;
    }

    return ret;
}

int YLBaseSocket::recv(void *buf, int len)
{
    return ::recv(m_socket, (char*)buf, len, 0);
}


int YLBaseSocket::close()
{
    YLEventDispatch::getInstance()->removeEvent(m_socket, SOCKET_ALL);
    removeBaseSocket(this);
    ::close(m_socket);
    return 0;
}


void YLBaseSocket::onRead()
{
    //表示新的连接进入
    if (m_state == SOCKET_STATE_LISTENING)
    {
        _AcceptNewSocket();
    }
    else
    {
        //获取socket的可读字节数
        u_long avail = 0;
        if ( (ioctl(m_socket, FIONREAD, &avail) == -1) || (avail == 0))
        {
            if (m_callback)
                m_callback(m_callback_data, NETLIB_MSG_CLOSE, m_socket, NULL);
        }
        else
        {
            if (m_callback)
                m_callback(m_callback_data, NETLIB_MSG_READ, m_socket, NULL);
        }
    }
}

void YLBaseSocket::onWrite()
{
    if (m_state == SOCKET_STATE_CONNECTING)
    {
        //首先判断是否有错误
        int error = 0;
        socklen_t len = sizeof(int);

        getsockopt(m_socket, SOL_SOCKET, SO_ERROR, (void*)&error, &len);
        if (error)
        {
            m_callback(m_callback_data, NETLIB_MSG_CLOSE, m_socket, nullptr);
        }
        else
        {
            //无错，表示连接已经成功建立
            m_state = SOCKET_STATE_CONNECTED;
            m_callback(m_callback_data, NETLIB_MSG_CONFIRM, m_socket, nullptr);
        }
    }
    else if(m_state == SOCKET_STATE_CONNECTED)
    {
        //写操作
        m_callback(m_callback_data, NETLIB_MSG_WRITE, m_socket, nullptr);
    }

}

void YLBaseSocket::onClose()
{
    m_state = SOCKET_STATE_CLOSING;
    //关闭操作。
    log("关闭连接\n", "");

}

void YLBaseSocket::_SetNonBlock(SOCKET fd)
{
    int ret = fcntl(fd, F_SETFL, O_NONBLOCK | fcntl(fd, F_GETFL));

    if (ret == -1)
    {
        log("void YLBaseSocket::_SetNonBlock(SOCKET fd) failed, error_code = %d \n", _GetErrorCode());
    }
}

//允许地址重用
void YLBaseSocket::_SetReuseAddr(SOCKET fd)
{
    int reuse_on = 1;

    int ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse_on, sizeof(int));

    if (ret == -1)
    {
        log("void YLBaseSocket::_SetReuseAddr(SOCKET fd) failed, error_code = %d\n", _GetErrorCode());
    }

}

//禁用nagle算法
void YLBaseSocket::_SetNoDelay(SOCKET fd)
{
    int nodelay = 1;
    int ret = setsockopt(fd, IPPROTO_IP, TCP_NODELAY, (char*)&nodelay, sizeof(int));

    if (ret == -1)
    {
        log("void YLBaseSocket::_SetNoDelay(SOCKET fd) failed, error_code = %d\n", _GetErrorCode());
    }
}

int YLBaseSocket::_GetErrorCode()
{
    return errno;
}



void YLBaseSocket::_SetAddr(const std::string &ip, const uint16_t port, sockaddr_in *pAddr)
{
    memset(pAddr, 0, sizeof(sockaddr_in));

    pAddr->sin_family = AF_INET;
    pAddr->sin_addr.s_addr = inet_addr(ip.c_str());
    pAddr->sin_port = htons(port);
//    pAddr->sin_port = port;
}

bool YLBaseSocket::_IsBlock(int err_code)
{
    return (err_code == EINPROGRESS) || (err_code = EWOULDBLOCK);
}

void YLBaseSocket::_AcceptNewSocket()
{
    SOCKET fd = 0;
    sockaddr_in peer_addr;
    socklen_t addr_len = sizeof(sockaddr_in);
    char str_ip[64];


    //接受连接

    while ( (fd = accept(m_socket, (sockaddr*)&peer_addr, &addr_len))!= -1)
    {
        YLBaseSocket* pSocket = new YLBaseSocket();

        uint32_t ip = ntohl(peer_addr.sin_addr.s_addr);
        uint16_t port = ntohs(peer_addr.sin_port);

        //将ip地址转换成形如:0.0.0.0
        snprintf(str_ip, sizeof(str_ip), "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);

        log("Accept new connect from %s : %d and socket = %d\n", str_ip, port, fd);

        pSocket->setSocket(fd);
        pSocket->setCallback(m_callback);
        pSocket->setCallbackData(m_callback_data);
        pSocket->setState(SOCKET_STATE_CONNECTED);
        pSocket->setRemoteIP(str_ip);
        pSocket->setRemotePort(port);

        _SetNonBlock(fd);
        _SetNoDelay(fd);

        char buf[4] = "123";


//      for (int  i = 0; i < 1000; ++i)
//      {
//     	    for(int j = 0; j < 1000000; ++j);
//          log("send 123 to socket fd = %d, id = %d\n", fd, i);
//          ::send(fd, buf, 4, 0);
//      }



        addBaseSocket(pSocket);
        YLEventDispatch::getInstance()->addEvent(fd, SOCKET_READ | SOCKET_EXCEP);
        if (m_callback)
            m_callback(m_callback_data, NETLIB_MSG_CONNECT, fd, NULL);

    }

    log("accept failed, error_str = %s\n", strerror(_GetErrorCode()));

}
