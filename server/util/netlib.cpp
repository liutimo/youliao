//
// Created by liuzheng on 18-2-4.
//

#include "netlib.h"
#include "YLBaseSocket.h"
#include "YLEventDispatch.h"

int netlib_init()
{
    return NETLIB_OK;
}

int netlib_destroy()
{
    return NETLIB_OK;
}


int netlib_listen(
        const char* server_ip,
        uint16_t port,
        callback_t callback,
        void* callback_data)
{
    YLBaseSocket *pSocket = new YLBaseSocket();
    if (!pSocket)
        return NETLIB_ERROR;

    int ret = pSocket->listen(server_ip, port, callback, callback_data);
    if (ret == NETLIB_ERROR)
        delete pSocket;

    return ret;
}

//返回值为当前连接的描述符
int netlib_connect(
        const char* server_ip,
        uint16_t port,
        callback_t callback,
        void* callback_data)
{
    YLBaseSocket *pSocket = new YLBaseSocket();
    if (!pSocket)
        return NETLIB_ERROR;

    int ret = pSocket->connect(server_ip, port, callback, callback_data);
    if (ret == -1)
        delete pSocket;

    return ret;
}

int netlib_send(int fd, void* buf, int len)
{
    YLBaseSocket *pSocket = findBaseSocket(fd);
    if (!pSocket)
    {
        return NETLIB_ERROR;
    }

    int ret = pSocket->send(buf, len);
    return ret;
}

int netlib_recv(int fd, void* buf, int len)
{
    YLBaseSocket *pSocket = findBaseSocket(fd);
    if (!pSocket)
    {
        return NETLIB_ERROR;
    }

    int ret = pSocket->recv(buf, len);
    return ret;
}

int netlib_close(int fd)
{
    YLBaseSocket *pSocket = findBaseSocket(fd);
    if (!pSocket)
    {
        return NETLIB_ERROR;
    }

    return pSocket->close();
}



int netlib_option(int fd, int opt, void* opt_val)
{
    YLBaseSocket *pSocket = findBaseSocket(fd);
    if (!pSocket)
    {
        return NETLIB_ERROR;
    }

    if (opt >= NETLIB_OPT_MAX_VALUE || opt <= NETLIB_OPT_MIN_VALUE)
    {
        return NETLIB_ERROR;
    }

    switch (opt)
    {
        case NETLIB_OPT_SET_CALLBACK:
            pSocket->setCallback((callback_t)opt_val);
            break;
        case NETLIB_OPT_SET_CALLBACK_DATA:
            pSocket->setCallbackData(opt_val);
            break;
        case NETLIB_OPT_GET_REMOTE_IP:
            *((std::string*)opt_val) = pSocket->getRemoteIP();
            break;
        case NETLIB_OPT_GET_REMOTE_PORT:
            *((std::string*)opt_val) = pSocket->getRemotePort();
            break;
    }

    return NETLIB_OK;
}

void netlib_eventloop(uint32_t wait_time)
{
    YLEventDispatch::getInstance()->startDispatch(wait_time);
}

void netlib_stop_eventloop()
{
    YLEventDispatch::getInstance()->stopDispacth();
}

bool netlib_eventloop_is_running()
{
    return YLEventDispatch::getInstance()->isRunning();
}
