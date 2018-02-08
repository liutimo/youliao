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
            void incrWriteOffest(uint16_t len) { m_write_offest += len;}

            int getFreeSize() { return m_aolloc_size - m_write_offest; }
            uchar_t* getBuffer() { return m_buf; }
            uchar_t* getCurrWritePos() { return m_buf + m_write_offest; }
            bool empty() { return m_write_offest == 0; }
            uint32_t size() { return m_write_offest; }
        private:
            uchar_t *m_buf;

            uint32_t m_aolloc_size;
            uint32_t m_write_offest;
        };
    }
}


#endif //BASEUTIL_SIMPLEBUFFER_H
