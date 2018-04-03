//
// Created by liuzheng on 18-3-24.
//

#include "AttachData.h"

AttachData::AttachData(uint32_t handle)
{
    m_buf.writeUInt32(handle);
}

AttachData::AttachData(u_char *attach_data, uint32_t attach_len)
{
    m_buf.write(attach_data, attach_len);
}

