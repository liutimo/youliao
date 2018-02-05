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

