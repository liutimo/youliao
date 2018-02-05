//
// Created by liuzheng on 18-2-5.
//

#include "YLPduBase.h"
#include "protobuf/YLBase.pb.h"

YLPdu::YLPdu()
{
    m_pdu_header.version = PDU_VERSION;
    m_pdu_header.flag = 0;
    m_pdu_header.service_id = YL::Base::SID_OTHER;
    m_pdu_header.command_id = 0;
    m_pdu_header.seq_num = 0;
    m_pdu_header.reversed = 0;
}

YLPdu::~YLPdu()
{

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
    u_char* buf = getBuffer();

    YLByteStream::writeInt32(buf, getLength());
    YLByteStream::writeUint16(buf + 4, m_pdu_header.version);
    YLByteStream::writeUint16(buf + 6, m_pdu_header.flag);
    YLByteStream::writeUint16(buf + 8, m_pdu_header.service_id);
    YLByteStream::writeUint16(buf + 10, m_pdu_header.command_id);
    YLByteStream::writeUint16(buf + 12, m_pdu_header.seq_num);
    YLByteStream::writeUint16(buf + 14, m_pdu_header.reversed);
}

void YLPdu::setVersion(uint16_t version)
{
    u_char* buf = getBuffer();
    YLByteStream::writeUint16(buf + 4, version);
}

void YLPdu::setFlag(uint16_t flag)
{
    u_char* buf = getBuffer();
    YLByteStream::writeUint16(buf + 6, flag);
}

void YLPdu::setSID(uint16_t sid)
{
    u_char* buf = getBuffer();
    YLByteStream::writeUint16(buf + 8, sid);
}

void YLPdu::setCID(uint16_t cid)
{
    u_char* buf = getBuffer();
    YLByteStream::writeUint16(buf + 10, cid);
}

void YLPdu::setError(uint16_t err)
{
    u_char* buf = getBuffer();
    YLByteStream::writeUint16(buf + 12, err);
}

void YLPdu::setSeqNum(uint16_t seq_num)
{
    u_char* buf = getBuffer();
    YLByteStream::writeUint16(buf + 14, seq_num);
}


void YLPdu::setReversed(uint32_t reversed)
{
    u_char* buf = getBuffer();
    YLByteStream::writeUint32(buf + 16, reversed);
}

int YLPdu::readPduHeader(u_char *buf, uint32_t len)
{
    int ret = -1;

    if (len >= PDU_HEADER_LEN && buf)
    {
        YLByteStream is(buf, len);

        is >> m_pdu_header.length;
        is >> m_pdu_header.version;
        is >> m_pdu_header.flag;
        is >> m_pdu_header.service_id;
        is >> m_pdu_header.command_id;
        is >> m_pdu_header.seq_num;
        is >> m_pdu_header.reversed;

        ret = 0;
    }
    return ret;
}

YLPdu* YLPdu::readPdu(u_char *buf, uint32_t len)
{
    uint32_t pdu_len = 0;

    if (!isPduAvailable(buf, len, pdu_len))
        return nullptr;

    YLPdu *pPdu = new YLPdu();
    pPdu->write(buf, pdu_len);
    pPdu->readPduHeader(buf, PDU_HEADER_LEN);

    return pPdu;
}

bool YLPdu::isPduAvailable(u_char *buf, uint32_t length, uint32_t &pdu_length)
{
    if (length < PDU_HEADER_LEN)
        return false;

    pdu_length = YLByteStream::readUint32(buf);

    if (pdu_length > length)
        return false;

    return true;
}

void YLPdu::setPBMsg(const google::protobuf::MessageLite *msg)
{
    m_buffer.read(nullptr, m_buffer.getWriteOffest());
    m_buffer.write(nullptr, sizeof(PduHeader_t));

    uint32_t msg_size = msg->ByteSize();
    u_char* sz_data = new u_char[msg_size];

    if (!msg->SerializeToArray(sz_data, msg_size))
    {
        //...
    }

    m_buffer.write(sz_data, msg_size);
    delete []sz_data;
    writeHeader();

}