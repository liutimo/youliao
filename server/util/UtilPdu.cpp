//
// Created by liuzheng on 18-2-5.
//

#include "UtilPdu.h"
#include <stdlib.h>
#include <string.h>

YLSimpleBuffer::YLSimpleBuffer()
{
    m_buffer       = nullptr;

    m_alloc_size   = 0;
    m_write_offest = 0;
}

YLSimpleBuffer::~YLSimpleBuffer()
{
    m_alloc_size = 0;
    m_write_offest = 0;

    if (m_buffer)
    {
        free(m_buffer);
        m_buffer = nullptr;
    }
}

void YLSimpleBuffer::extend(uint32_t len)
{
    m_alloc_size = m_write_offest + len;
    m_alloc_size += m_alloc_size >> 2; //增加需求的1/4
    u_char *new_buf = (u_char*)realloc(m_buffer, m_alloc_size);
    m_buffer = new_buf;
}

uint32_t YLSimpleBuffer::write(void *buf, uint32_t len)
{
    if (m_write_offest + len >= m_alloc_size)
    {
        extend(len);
    }

    if (buf)
    {
        memcpy(m_buffer + m_write_offest, buf, len);
    }

    m_write_offest += len;

    return len;
}

uint32_t YLSimpleBuffer::read(void *buf, uint32_t len)
{
    if (len > m_write_offest)
        len = m_write_offest;

    if (buf)
    {
        memcpy(buf, m_buffer, len);
    }

    m_write_offest -= len;
    memmove(m_buffer, m_buffer + len, m_write_offest);

    return len;
}


////// YLByteStream //////
YLByteStream::YLByteStream(u_char* buf, uint32_t len)
{
    m_pBuf = buf;
    m_len = len;
    m_pSimpBuf = NULL;
    m_pos = 0;
}

YLByteStream::YLByteStream(YLSimpleBuffer* pSimpBuf, uint32_t pos)
{
    m_pSimpBuf = pSimpBuf;
    m_pos = pos;
    m_pBuf = NULL;
    m_len = 0;
}

int16_t YLByteStream::readInt16(u_char *buf)
{
    int16_t data = (buf[0] << 8) | buf[1];
    return data;
}

uint16_t YLByteStream::readUint16(u_char* buf)
{
    uint16_t data = (buf[0] << 8) | buf[1];
    return data;
}

int32_t YLByteStream::readInt32(u_char *buf)
{
    int32_t data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    return data;
}

uint32_t YLByteStream::readUint32(u_char *buf)
{
    uint32_t data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    return data;
}

void YLByteStream::writeInt16(u_char *buf, int16_t data)
{
    buf[0] = static_cast<u_char>(data >> 8);
    buf[1] = static_cast<u_char>(data & 0xFF);
}

void YLByteStream::writeUint16(u_char *buf, uint16_t data)
{
    buf[0] = static_cast<u_char>(data >> 8);
    buf[1] = static_cast<u_char>(data & 0xFF);
}

void YLByteStream::writeInt32(u_char *buf, int32_t data)
{
    buf[0] = static_cast<u_char>(data >> 24);
    buf[1] = static_cast<u_char>((data >> 16) & 0xFF);
    buf[2] = static_cast<u_char>((data >> 8) & 0xFF);
    buf[3] = static_cast<u_char>(data & 0xFF);
}

void YLByteStream::writeUint32(u_char *buf, uint32_t data)
{
    buf[0] = static_cast<u_char>(data >> 24);
    buf[1] = static_cast<u_char>((data >> 16) & 0xFF);
    buf[2] = static_cast<u_char>((data >> 8) & 0xFF);
    buf[3] = static_cast<u_char>(data & 0xFF);
}

void YLByteStream::operator << (int8_t data)
{
    _WriteByte(&data, 1);
}

void YLByteStream::operator << (uint8_t data)
{
    _WriteByte(&data, 1);
}

void YLByteStream::operator << (int16_t data)
{
    unsigned char buf[2];
    buf[0] = static_cast<u_char>(data >> 8);
    buf[1] = static_cast<u_char>(data & 0xFF);
    _WriteByte(buf, 2);
}

void YLByteStream::operator << (uint16_t data)
{
    unsigned char buf[2];
    buf[0] = static_cast<u_char>(data >> 8);
    buf[1] = static_cast<u_char>(data & 0xFF);
    _WriteByte(buf, 2);
}

void YLByteStream::operator << (int32_t data)
{
    unsigned char buf[4];
    buf[0] = static_cast<u_char>(data >> 24);
    buf[1] = static_cast<u_char>((data >> 16) & 0xFF);
    buf[2] = static_cast<u_char>((data >> 8) & 0xFF);
    buf[3] = static_cast<u_char>(data & 0xFF);
    _WriteByte(buf, 4);
}

void YLByteStream::operator << (uint32_t data)
{
    unsigned char buf[4];
    buf[0] = static_cast<u_char>(data >> 24);
    buf[1] = static_cast<u_char>((data >> 16) & 0xFF);
    buf[2] = static_cast<u_char>((data >> 8) & 0xFF);
    buf[3] = static_cast<u_char>(data & 0xFF);
    _WriteByte(buf, 4);
}

void YLByteStream::operator >> (int8_t& data)
{
    _ReadByte(&data, 1);
}

void YLByteStream::operator >> (uint8_t& data)
{
    _ReadByte(&data, 1);
}

void YLByteStream::operator >> (int16_t& data)
{
    unsigned char buf[2];

    _ReadByte(buf, 2);

    data = (buf[0] << 8) | buf[1];
}

void YLByteStream::operator >> (uint16_t& data)
{
    unsigned char buf[2];

    _ReadByte(buf, 2);

    data = (buf[0] << 8) | buf[1];
}

void YLByteStream::operator >> (int32_t& data)
{
    unsigned char buf[4];

    _ReadByte(buf, 4);

    data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

void YLByteStream::operator >> (uint32_t& data)
{
    unsigned char buf[4];

    _ReadByte(buf, 4);

    data = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

void YLByteStream::writeString(const char *str)
{
    uint32_t size = str ? (uint32_t)strlen(str) : 0;

    *this << size;
    _WriteByte((void*)str, size);
}

void YLByteStream::writeString(const char *str, uint32_t len)
{
    *this << len;
    _WriteByte((void*)str, len);
}

char* YLByteStream::readString(uint32_t& len)
{
    *this >> len;
    char* pStr = (char*)getBuf() + getPos();
    skip(len);
    return pStr;
}

void YLByteStream::writeData(u_char *data, uint32_t len)
{
    *this << len;
    _WriteByte(data, len);
}

u_char* YLByteStream::readData(uint32_t &len)
{
    *this >> len;
    u_char* pData = (u_char*)getBuf() + getPos();
    skip(len);
    return pData;
}

void YLByteStream::_ReadByte(void* buf, uint32_t len)
{
    if (m_pos + len > m_len)
    {
        throw YLPduException(ERROR_CODE_PARSE_FAILED, "parase packet failed!");
    }

    if (m_pSimpBuf)
        m_pSimpBuf->read((char*)buf, len);
    else
        memcpy(buf, m_pBuf + m_pos, len);

    m_pos += len;
}

void YLByteStream::_WriteByte(void* buf, uint32_t len)
{
    if (m_pBuf && (m_pos + len > m_len))
        return;

    if (m_pSimpBuf)
        m_pSimpBuf->write((char*)buf, len);
    else
        memcpy(m_pBuf + m_pos, buf, len);

    m_pos += len;
}