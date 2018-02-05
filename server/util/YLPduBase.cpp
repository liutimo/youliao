//
// Created by liuzheng on 18-2-5.
//

#include "YLPduBase.h"
#include "protobuf/YLBase.pb.h"

YLPdu::YLPdu()
{
    m_pdu_header.version = IM_PDU_VERSION;
    m_pdu_header.flag = 0;
    m_pdu_header.service_id = YL::Base::SID_OTHER;
    m_pdu_header.command_id = 0;
    m_pdu_header.seq_num = 0;
    m_pdu_header.reversed = 0;
}

u_char* YLPdu::getBuffer()
{
    return m_buffer.getBuffer();
}

uint32_t YLPdu::getLength()
{
    return m_buffer.getWriteOffest();
}

u_char* YLPdu::getBodyData()
{
    return getBuffer() + sizeof(PduHeader_t);
}

uint32_t YLPdu::getBodyLength()
{
    return getLength() - sizeof(PduHeader_t);
}

void YLPdu::writeHeader()
{
    // ...
}

void YLPdu::setVersion(uint16_t version)
{

}

void YLPdu::setFlag(uint16_t flag) {}

void YLPdu::setSID(uint16_t sid) {}

void YLPdu::setCID(uint16_t cid) {}

void YLPdu::setError(uint16_t err) {}

void YLPdu::setSeqNum(uint16_t seq_num) {}

void YLPdu::setReversed(uint32_t reversed) {}

int YLPdu::readPduHeader(u_char *buf, uint32_t len)
{
    return -1;
}

YLPdu* YLPdu::readPdu(u_char *buf, uint32_t len)
{

    return nullptr;
}

bool YLPdu::isPduAvailable(u_char *buf, uint32_t length, uint32_t &pdu_length)
{
    return true;
}

void YLPdu::setPduMsg(const google::protobuf::MessageLite *msg)
{

}