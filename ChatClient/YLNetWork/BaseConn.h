/*================================================================
*   
*   文件名称: BaseConn.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月07日　 下午3:40
*   描   述:
*
================================================================*/


#ifndef BASEUTIL_BASECONN_H
#define BASEUTIL_BASECONN_H

#include <ext/hash_map>
#include "type_define.h"
#include "SimpleBuffer.h"
#include "BasePdu.h"

namespace youliao
{
    namespace network
    {
        const int NETWORK_MAX_SIZE = 2048;

        class BaseConn {
        public:
            BaseConn();

            ~BaseConn();

            int sendBasePdu(pdu::BasePdu*);
            int send(void* buf, int len);
        public:
            virtual void onConnect(net_handle_t handle) { m_handle = handle; }
            virtual void onRead();
            virtual void onWrite();
            virtual void onClose();
            virtual void onWriteComplete() {}

            virtual void handlePdu(youliao::pdu::BasePdu *) {}


        protected:
            net_handle_t m_handle;
            bool m_busy;    //判断写缓冲区是否有数据
            youliao::util::SimpleBuffer m_read_buf;
            youliao::util::SimpleBuffer m_write_buf;
        };

        typedef __gnu_cxx::hash_map<net_handle_t, BaseConn*> BaseConnMap_t;

        void baseconn_callback(callback_data data, uint8_t msg, net_handle_t handle, void *pParam);
    }

}




#endif //BASEUTIL_BASECONN_H
