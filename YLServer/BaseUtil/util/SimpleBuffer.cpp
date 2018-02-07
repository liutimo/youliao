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
