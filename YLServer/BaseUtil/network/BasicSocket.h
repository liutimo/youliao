/*================================================================
*   
*   文件名称: BasicSocket.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月06日　 下午11:48
*   描   述: 封装socket
*
================================================================*/


#ifndef BASEUTIL_BASICSOCKET_H
#define BASEUTIL_BASICSOCKET_H

#include "type_define.h"
#include <string>


struct sockaddr_in;

namespace youliao
{
    namespace network
    {
        class BaseSocket
        {
        public:
            typedef enum
            {
                BASESOCKET_STATE_IDLE = 0,      //空闲
                BASESOCKET_STATE_LISTENING,     //监听
                BASESOCKET_STATE_CONNECTING,    //连接中
                BASESOCKET_STATE_CONNECTED,     //已连接
                BASESOCKET_STATE_CLOSE          //关闭
            }SocketState;

            BaseSocket();
            virtual ~BaseSocket();

            void setHandle(net_handle_t handle) { m_handle = handle; }
            void setCallBack(callback_t callback) { m_callback = callback; }
            void setCallBackData(callback_data data) { m_callback_data = data; }
            void setSocketState(SocketState state) { m_state = state; }
            void setSendBufferSize(uint32_t sendSize);
            void setRecvBufferSize(uint32_t recvSize);

            net_handle_t getHandle() const { return m_handle; }

        public:
            int listen(const std::string &serv_ip, uint16_t port, callback_t callback, callback_data data);
            int connect(const std::string &serv_ip, uint16_t port, callback_t callback, callback_data data);


            ssize_t send(void *buf, size_t len);
            ssize_t recv(void *buf, size_t len);
            int close();


        public:
            void onRead();
            void onWrite();
            void onClose();


        private:
            /*禁用Nagle算法*/
            void _SetNoDelay();
            void _SetReuseAddr();
            void _SetNonBlock();
            void _SetSockAddr(const std::string &ip, uint16_t port, sockaddr_in&);
            void _AcceptNewConn();
            int _GetErrorCode();
            char* _GetErrorStr();
            bool _IsBlock(int errCode);
        private:
            net_handle_t    m_handle;

            callback_t      m_callback;
            callback_data   m_callback_data;
            SocketState     m_state;
        };

        BaseSocket* findBaseSocket(net_handle_t handle);
    }
}


#endif //BASEUTIL_BASICSOCKET_H
