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


class YLByteStream
{
public:
    YLByteStream(u_char* buf, uint32_t len);
    YLByteStream(YLSimpleBuffer* pSimpBuf, uint32_t pos);
    ~YLByteStream() {}

    unsigned char* getBuf() { return m_pSimpBuf ? m_pSimpBuf->getBuffer() : m_pBuf; }
    uint32_t getPos() { return m_pos; }
    uint32_t getLen() { return m_len; }
    void skip(uint32_t len)
    {
        m_pos += len;
        if(m_pos > m_len)
        {
            throw YLPduException(ERROR_CODE_PARSE_FAILED, "parase packet failed!");
        }
    }

    static int16_t readInt16(u_char* buf);
    static uint16_t readUint16(u_char* buf);
    static int32_t readInt32(u_char* buf);
    static uint32_t readUint32(u_char* buf);
    static void writeInt16(u_char* buf, int16_t data);
    static void writeUint16(u_char* buf, uint16_t data);
    static void writeInt32(u_char* buf, int32_t data);
    static void writeUint32(u_char* buf, uint32_t data);

    void operator << (int8_t data);
    void operator << (uint8_t data);
    void operator << (int16_t data);
    void operator << (uint16_t data);
    void operator << (int32_t data);
    void operator << (uint32_t data);

    void operator >> (int8_t& data);
    void operator >> (uint8_t& data);
    void operator >> (int16_t& data);
    void operator >> (uint16_t& data);
    void operator >> (int32_t& data);
    void operator >> (uint32_t& data);

    void writeString(const char* str);
    void writeString(const char* str, uint32_t len);
    char* readString(uint32_t& len);

    void writeData(u_char* data, uint32_t len);
    u_char* readData(uint32_t& len);
private:
    void _WriteByte(void* buf, uint32_t len);
    void _ReadByte(void* buf, uint32_t len);
private:
    YLSimpleBuffer*	m_pSimpBuf;
    u_char*		m_pBuf;
    uint32_t		m_len;
    uint32_t		m_pos;
};
#endif //UTIL_UTILPDU_H
