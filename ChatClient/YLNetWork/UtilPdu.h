//
// Created by liuzheng on 18-2-5.
//

#ifndef UTIL_UTILPDU_H
#define UTIL_UTILPDU_H

#include "os.h"
#include <string>

#define ERROR_CODE_PARSE_FAILED         1
#define ERROR_CODE_WRONG_SERVICE_ID     2
#define ERROR_CODE_WRONG_COMMAND_ID     3
#define ERROR_CODE_ALLO_FAILED          4


//
//
//PDU == 协议数据单元
//
//

class YLPduException
{
public:
    YLPduException(uint32_t sid, uint32_t cid, uint32_t err_code, const std::string& err_msg)
    {
        m_cid = cid;
        m_sid = sid;
        m_error_code = err_code;
        m_error_msg = err_msg;
    }

    YLPduException(uint32_t err_code, const std::string err_msg)
    {
        m_cid = 0;
        m_sid = 0;
        m_error_code = err_code;
        m_error_msg = err_msg;
    }

    virtual ~YLPduException() {}

    uint32_t getSID()                const { return m_sid; }
    uint32_t getCID()                const { return m_cid; }
    uint32_t getErrorCode()          const { return m_error_code; }
    const std::string& getErrorMsg() const { return m_error_msg; }

private:
    uint32_t m_sid;
    uint32_t m_cid;
    uint32_t m_error_code;
    std::string m_error_msg;

};


class YLSimpleBuffer
{
public:
    YLSimpleBuffer();
    ~YLSimpleBuffer();
    u_char*     getBuffer()      { return m_buffer; }
    uint32_t    getAllocSize()   { return m_alloc_size; }
    uint32_t    getWriteOffest() { return m_write_offest; }


    void extend(uint32_t len);
    void incrWriteOffest(uint32_t len) { m_write_offest += len; }
    uint32_t write(void* buf, uint32_t len);
    uint32_t read (void* buf, uint32_t len);

private:
    u_char*     m_buffer;
    uint32_t    m_alloc_size;
    uint32_t    m_write_offest;
};


#endif //UTIL_UTILPDU_H
