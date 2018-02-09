/*================================================================
*   
*   文件名称: BasePdu.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月08日　 下午10:56
*   描   述:
*
================================================================*/


#include "BasePdu.h"

using namespace youliao::pdu;

BasePdu::BasePdu()
{

}

BasePdu::~BasePdu()
{

}

void BasePdu::writePduHeader(pdu_header_t *pduHeader)
{
    m_buff.writeUInt32(pduHeader->length);
    m_buff.writeUInt16(pduHeader->sid);
    m_buff.writeUInt16(pduHeader->cid);
}


void BasePdu::writeMessage(google::protobuf::MessageLite *messageLite)
{
    std::string msg = messageLite->SerializeAsString();

    m_header.length = PDU_HEADER_LENGTH + msg.size();

    writePduHeader(&m_header);

    m_buff.writeString(msg);
}



void BasePdu::readPduHeader(SimpleBuffer &buffer)
{
    m_header.length = buffer.readUInt32();
    m_header.sid = buffer.readUInt16();
    m_header.cid = buffer.readUInt16();
}

void BasePdu::readMessage(SimpleBuffer &buffer)
{
    m_message = buffer.readString(m_header.length - PDU_HEADER_LENGTH);
}

bool BasePdu::isAvailabel(SimpleBuffer &buffer)
{
    if (buffer.getWriteOffest() < PDU_HEADER_LENGTH)
        return false;

    uint32_t  length = buffer.getUint32();
    if (length > buffer.getWriteOffest())
        return false;

    return true;
}

BasePdu* BasePdu::readPduFromBuffer(SimpleBuffer &buffer)
{

    if (!isAvailabel(buffer))
        return nullptr;

    BasePdu *basePdu = new BasePdu;
    //获取包头
    basePdu->readPduHeader(buffer);
    //获取消息主体
    basePdu->readMessage(buffer);

    return basePdu;
}