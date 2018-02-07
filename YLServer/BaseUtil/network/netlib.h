/*================================================================
*   
*   文件名称: netlib.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月07日　 下午4:00
*   描   述:
*
================================================================*/


#ifndef BASEUTIL_NETLIB_H
#define BASEUTIL_NETLIB_H

#include "BasicSocket.h"
#include "EventDispatch.h"
#include "type_define.h"
namespace youliao
{
    namespace network
    {
        const int NETLIB_OPT_SET_CALLBACK        =  1;
        const int NETLIB_OPT_SET_CALLBACK_DATA   =  2;

        inline int netlib_init()
        {
            return NETWORK_OK;
        }

        inline netlib_listen(const std::string& serv_ip,
                             uint16_t port,
                             callback_t callback,
                             callback_data callbackData)
        {
            BaseSocket *baseSocket = new BaseSocket;
            int ret = baseSocket->listen(serv_ip, port, callback, callbackData);
            if (ret == NETWORK_ERROR)
                delete baseSocket;

            return ret;
        }


        inline netlib_connect(const std::string& serv_ip,
                              uint16_t port,
                              callback_t callback,
                              callback_data callbackData)
        {
            BaseSocket *baseSocket = new BaseSocket;
            int ret = baseSocket->connect(serv_ip, port, callback, callbackData);
            if (ret == NETWORK_ERROR)
                delete baseSocket;
            return baseSocket;
        }

        inline int netlib_send(int handle, void* buf, int len)
        {
            BaseSocket *baseSocket = findBaseSocket(handle);
            if (!baseSocket)
                return NETWORK_ERROR;

            int ret = baseSocket->send(buf, len);
            return ret;
        }

        inline int netlib_recv(int handle, void* buf, int len)
        {
            BaseSocket *baseSocket = findBaseSocket(handle);
            if (!baseSocket)
                return NETWORK_ERROR;

            int ret = baseSocket->recv(buf, len);
        }

        inline int netlib_close(int handle)
        {
            BaseSocket *baseSocket = findBaseSocket(handle);
            if (!baseSocket)
                return NETWORK_ERROR;

            baseSocket->close();
        }

        int netlib_option(int handle, int opt, void* optval)
        {
            BaseSocket *baseSocket = findBaseSocket(handle);
            if (!baseSocket)
                return NETWORK_ERROR;

            switch (opt)
            {
                case NETLIB_OPT_SET_CALLBACK:
                    baseSocket->setCallBack((callback_t)optval);
                    break;
                case NETLIB_OPT_SET_CALLBACK_DATA:
                    baseSocket->setCallBackData((callback_data)optval);
                    break;
                default:
                    break;
            }

            return NETWORK_OK;
        }

        inline int netlib_eventloop(uint32_t wait_time = 100)
        {
            EventDispatch::instance()->eventLoop(wait_time);
        }

        inline int nettlib_destory()
        {
            return NETWORK_OK;
        }

    }


};


#endif //BASEUTIL_NETLIB_H
