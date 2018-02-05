//
// Created by liuzheng on 18-2-5.
//

#ifndef UTIL_YLPDUBASE_H
#define UTIL_YLPDUBASE_H

#include "UtilPdu.h"
#include <google/protobuf/message_lite.h>

const int IM_PDU_HEADER_LEN    = 16;
const int IM_PDU_VERSION       = 1;

#define ALLOCK_FAIL_ASSERT(p) if (p == nullptr) {\
throw YLPduException(m_pdu_header.service_id, m_pdu_header.command_id, ERROR_CODE_ALLOC_FAILED, "allocate failed"); \
}

typedef struct
{
    uint32_t    length;
    uint16_t    version;
    uint16_t    flag;
    uint16_t    service_id;
    uint16_t    command_id;
    uint16_t    seq_num;    //包序号
    uint16_t    reversed;   //保留
}PduHeader_t;


class YLPdu
{
public:
    YLPdu();
    virtual ~YLPdu();

    u_char*     getBuffer();
    uint32_t    getLength();
    u_char*     getBodyData();
    uint32_t    getBodyLength();

    uint16_t getVersion() const { return m_pdu_header.version; }
    uint16_t getFlag() const { return m_pdu_header.flag; }
    uint16_t getSID() const { return m_pdu_header.service_id; }
    uint16_t getCID() const { return m_pdu_header.command_id; }
    uint16_t getSeqNum() const { return m_pdu_header.seq_num; }
    uint32_t getReversed() const { return m_pdu_header.reversed; }

    void setVersion(uint16_t version);
    void setFlag(uint16_t flag);
    void setSID(uint16_t sid);
    void setCID(uint16_t cid);
    void setError(uint16_t err);
    void setSeqNum(uint16_t seq_num);
    void setReversed(uint32_t reversed);
    void writeHeader();

    static bool isPduAvailable(u_char* buf, uint32_t length, uint32_t& pdu_length);
    static YLPdu* readPdu(u_char* buf, uint32_t len);
    void write(u_char* buf, uint32_t len) { m_buffer.write(buf, len); }
    int readPduHeader(u_char* buf, uint32_t len);
    void setPduMsg(const google::protobuf::MessageLite *msg);


protected:
    YLSimpleBuffer  m_buffer;
    PduHeader_t     m_pdu_header;
};


#endif //UTIL_YLPDUBASE_H
