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
    m_buff.write(pduHeader, sizeof(pdu_header_t));
}


BasePdu* BasePdu::readPduFromBuffer(SimpleBuffer &buffer)
{
    if (buffer.getWriteOffest() < PDU_HEADER_LENGTH)
        return nullptr;


}

void BasePdu::readHeader(SimpleBuffer &buffer)
{
    m_header.length = buffer.readUInt32();
    m_header.sid = buffer.readUInt16();
    m_header.cid = buffer.readUInt16();


}