//
// Created by liuzheng on 18-2-4.
//

#ifndef UTIL_YLBASESOCKET_H
#define UTIL_YLBASESOCKET_H

#include "os.h"
#include "common.h"

enum
{
    SOCKET_STATE_IDLE,          //空闲
    SOCKET_STATE_LISTENING,
    SOCKET_STATE_CONNECTING,
    SOCKET_STATE_CONNECTED,
    SOCKET_STATE_CLOSING
};


class YLBaseSocket {
public:
    YLBaseSocket();
    virtual ~YLBaseSocket();

    void setCallback(callback_t callback)  { m_callback = callback; }
    void setCallbackData(void* data) {m_callback_data = data; }
    void setRemoteIP(const std::string& ip) { m_remote_ip = ip; }
    void setRemotePort(const uint16_t port) { m_remote_port = port; }
    void setSocket(SOCKET fd) { m_socket = fd; }
    void setState(uint8_t state) { m_state = state; }

    const std::string& getRemoteIP() const { return m_remote_ip; }
    const uint8_t getRemotePort() const { return m_remote_port; }
    SOCKET getSocket() const { return m_socket; }


public:
    int listen(const std::string& server_ip, uint16_t port, callback_t callback, void* callback_data);
    int connect(const std::string& server_ip, uint16_t port, callback_t callback, void* callback_data);

    int send(void* buf, int len);
    int recv(void* buf, int len);
    int close();

public:
    void onRead();
    void onWrite();
    void onClose();

private:
    void _SetNonBlock(SOCKET fd);
    void _SetReuseAddr(SOCKET fd);
    void _SetNoDelay(SOCKET fd);
    void _SetAddr(const std::string& ip, const uint16_t port, sockaddr_in* pAddr);


    bool _IsBlock(int err_code);
    int  _GetErrorCode();

public:
    void _AcceptNewSocket();
private:
    std::string     m_remote_ip;        //远程IP
    uint16_t        m_remote_port;      //远程端口

    callback_t      m_callback;         //回调函数
    void*           m_callback_data;    //回调函数需要的data

    uint8_t         m_state;            //连接状态
    SOCKET          m_socket;           // == fd

};

//根据描述符找到相应的实例
YLBaseSocket* findBaseSocket(int fd);

#endif //UTIL_YLBASESOCKET_H
