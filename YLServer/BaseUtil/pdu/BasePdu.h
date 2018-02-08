/*================================================================
*   
*   文件名称: BasePdu.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月08日　 下午10:56
*   描   述:
*
================================================================*/


#ifndef BASEUTIL_BASEPDU_H
#define BASEUTIL_BASEPDU_H

#include "../util/SimpleBuffer.h"

using namespace youliao::util;
namespace youliao
{
    namespace pdu
    {

        typedef struct {
            uint32_t    length;       //整个消息包的长度  sizeof(pdu_header_t) + message.length()
            uint16_t    sid;          //消息归属.    例如:  客户机消息, 消息服务器消息, 数据库服务器消息...
            uint16_t    cid;          //消息类型.    例如: 客户机: 登录,请求好友列表...
        }pdu_header_t;

        class BasePdu {
        public:
            BasePdu();

            ~BasePdu();

            void writePduHeader(pdu_header_t *pduHeader);
        private:
            //pdu数据缓冲
            SimpleBuffer m_buff;

        };

    }

}


#endif //BASEUTIL_BASEPDU_H
