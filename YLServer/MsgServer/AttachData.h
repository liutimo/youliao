//
// Created by liuzheng on 18-3-24.
//

#ifndef MSGSERVER_ATTACHDATA_H
#define MSGSERVER_ATTACHDATA_H

#include "util/SimpleBuffer.h"

using namespace youliao::util;


class AttachData {
    AttachData(uint32_t handle);
    AttachData(u_char *attach_data, uint32_t attach_len);
    virtual ~AttachData() {}

    u_char* getBuffer() { return m_buf.getBuffer(); }
    uint32_t getLength() const { return m_buf.getWriteOffest(); }
    uint32_t getType() const { return m_type; }
    uint32_t getHandle() const { return m_handle; }

private:
    SimpleBuffer  m_buf;
    uint32_t            m_type;
    uint32_t            m_handle;

};


#endif //MSGSERVER_ATTACHDATA_H
