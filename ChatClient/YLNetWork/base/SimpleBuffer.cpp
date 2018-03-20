/*================================================================
*   
*   文件名称: SimpleBuffer.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月07日　 下午3:06
*
================================================================*/


#include "SimpleBuffer.h"

#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace youliao::util;

SimpleBuffer::SimpleBuffer()
{
    m_buf = nullptr;
    m_write_offest = m_aolloc_size = 0;
}

SimpleBuffer::~SimpleBuffer()
{
    delete []m_buf;
}

void SimpleBuffer::extend(uint32_t len)
{
    m_aolloc_size += len;
    m_aolloc_size += m_aolloc_size >> 2;

    uchar_t *new_buf = (uchar_t*)realloc(m_buf, m_aolloc_size);

    if (new_buf)
        m_buf = new_buf;
}

int SimpleBuffer::read(void *buf, int len)
{
    if (len > m_write_offest)
        len = m_write_offest;

    if (buf)
        memcpy(buf, m_buf, len);

    m_write_offest -= len;

    memmove(m_buf, m_buf + len, m_write_offest);
    return len;
}

int SimpleBuffer::write(void *buf, int len)
{
    if (len > m_aolloc_size - m_write_offest)
        extend(len);

    if (buf)
        memcpy(m_buf + m_write_offest, buf, len);

    m_write_offest += len;
    return len;
}

void SimpleBuffer::writeUInt32(uint32_t data)
{
    if (sizeof(uint32_t) > getFreeSize())
        extend(sizeof(uint32_t));

    uchar_t *buf = getCurrWritePos();
    buf[0] = (data >> 24) & 0xFF;
    buf[1] = (data >> 16) & 0xFF;
    buf[2] = (data >> 8)  & 0xFF;
    buf[3] = (data)       & 0xFF;

    incrWriteOffest(sizeof(uint32_t));
}
uint32_t  SimpleBuffer::readUInt32()
{
    if(getFreeSize() < sizeof(uint32_t))
        return (uint32_t)-1;

    uchar_t *buf = getBuffer();

    uint32_t ret = (uint32_t)((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
    std::cout << ret << std::endl;
    read(nullptr, sizeof(uint32_t));

    return ret;
}

void SimpleBuffer::writeUInt16(uint16_t data)
{
    if (sizeof(uint16_t) > getFreeSize())
        extend(sizeof(uint16_t));

    uchar_t *buf = getCurrWritePos();
    buf[0] = (data >> 8) & 0xFF;
    buf[1] = (data)      & 0xFF;

    incrWriteOffest(sizeof(uint16_t));
}

uint16_t SimpleBuffer::readUInt16()
{
    if(getFreeSize() < sizeof(uint16_t))
        return (uint16_t)-1;

    uchar_t *buf = getBuffer();
    uint16_t  ret = (uint16_t)((buf[0] << 8) | buf[1]);
    read(nullptr, sizeof(uint16_t));
    return  ret;
}

void SimpleBuffer::writeString(const std::string &str)
{
    write((void*)str.c_str(), str.length());
}

std::string SimpleBuffer::readString(uint32_t length)
{
    std::string str(" ", length);
    std::copy(getBuffer(), getBuffer() + length, str.begin());
    read(nullptr, length);
    return str;
}

uint32_t SimpleBuffer::getUint32()
{
    if(getFreeSize() < sizeof(uint32_t))
        return (uint32_t)-1;

    uchar_t *buf = getBuffer();

    uint32_t ret = (uint32_t)((buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3]);
    return ret;
}