/*================================================================
*   
*   文件名称: SimpleBuffer.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月07日　 下午3:06
*   描   述:
*
================================================================*/


#ifndef BASEUTIL_SIMPLEBUFFER_H
#define BASEUTIL_SIMPLEBUFFER_H

#include <stdint.h>
#include <string>
namespace youliao
{
    namespace util
    {
        typedef unsigned char uchar_t;
        class SimpleBuffer {
        public:
            SimpleBuffer();
            ~SimpleBuffer();

            int read(void* buf, int len);
            int write(void* buf, int len);
            void extend(uint32_t len);

            uint32_t getWriteOffest() const { return m_write_offest; }
            //当使用使用getBuffer直接写入时,需要调用这个方法来增加写偏移
            void incrWriteOffest(uint16_t len) { m_write_offest += len;}
            //获取空闲内存大小
            int getFreeSize() const { return m_aolloc_size - m_write_offest; }

            //获取当前写入的位置.每次写入缓冲时都应该调用该method,而不是getBuffer
            uchar_t* getCurrWritePos() const { return m_buf + m_write_offest; }
            uchar_t* getBuffer() const { return m_buf; }
            uint32_t size() const { return m_write_offest; }
            bool empty() const { return m_write_offest == 0; }

            void writeUInt32(uint32_t);
            uint32_t  readUInt32();

            void writeUInt16(uint16_t );
            uint16_t readUInt16();

            void writeString(const std::string &);
            std::string readString(uint32_t);

            //只是读一个值,不会清空缓冲中的数据
            uint32_t getUint32();
        private:
            uchar_t *m_buf;

            uint32_t m_aolloc_size;
            uint32_t m_write_offest;
        };
    }
}


#endif //BASEUTIL_SIMPLEBUFFER_H
