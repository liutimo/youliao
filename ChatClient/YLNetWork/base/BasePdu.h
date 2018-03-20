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

#include "SimpleBuffer.h"
#include "Lock.h"
#include <google/protobuf/message_lite.h>
using namespace youliao::util;
using namespace youliao::thread;
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

            //发送数据时使用
            //发送数据时  消息头和消息主体都会被写进m_buff
            void writePduHeader(pdu_header_t *pduHeader);
            void writeMessage(google::protobuf::MessageLite *messageLite);

            //解析数据时使用
            //解析数据时 消息头写入m_header,消息主体写入m_buff
            void readPduHeader(SimpleBuffer&);
            void readMessage(SimpleBuffer&);

            void setCID(uint16_t cid) {m_header.cid = cid;}
            void setSID(uint16_t sid) {m_header.sid = sid;}

            uint16_t getSID() const {return m_header.sid;}
            uint16_t getCID() const {return m_header.cid;}

            std::string getMessage() const { return m_message; }
            uchar_t* getBuffer() const { return m_buff.getBuffer(); }
            uint32_t getBufferLength() const { return m_buff.getWriteOffest();}

            static BasePdu* readPduFromBuffer(SimpleBuffer &buffer);
            static bool isAvailabel(SimpleBuffer &buffer);

        private:


            //只在发送数据时使用
            SimpleBuffer m_buff;
            pdu_header_t m_header;
            //只在解析数据时使用
            std::string  m_message;

            static const int PDU_HEADER_LENGTH = sizeof(pdu_header_t);

        };

    }

}


#endif //BASEUTIL_BASEPDU_H
