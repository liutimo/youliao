/*================================================================
*   
*   文件名称: BaseConn.h
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月07日　 下午3:40
*   描   述:
*
================================================================*/


#include "BaseConn.h"
#include "netlib.h"
using namespace youliao::network;

BaseConn::BaseConn()
{
    m_busy = false;
    m_handle = -1;
}

BaseConn::~BaseConn()
{

}

int BaseConn::send(void *buf, int len)
{
    if (m_busy)
    {
        m_write_buf.write(buf, len);
        return len;
    }

    int offest = 0;
    int remain = len;

    while (remain > 0)
    {
        int size = remain;
        if (size > NETWORK_MAX_SIZE)
            size = NETWORK_MAX_SIZE;

        int ret = netlib_send(m_handle, buf + offest, offest);

        if (ret <= 0)
        {
            break;
        }

        offest += size;
        remain -= size;
    }

    if (remain > 0)
    {
        m_write_buf.write(buf + offest, remain);
        m_busy = true;
    }
    else
    {
        onWriteComplete();
    }

    return len;
}

void BaseConn::onRead()
{
    //全部读入缓冲区
    for (;;)
    {
        int free_buf_size = m_read_buf.getFreeSize();
        if (free_buf_size < NETWORK_MAX_SIZE)
            m_read_buf.extend(NETWORK_MAX_SIZE);

        int ret = netlib_recv(m_handle, m_read_buf.getCurrWritePos(), NETWORK_MAX_SIZE);

        if (ret <= 0)
            break;
    }

    //读pdu,
    handlePdu();

}


void BaseConn::onWrite()
{
    //缓冲区无数据
    if (!m_busy)
        return;

    while (!m_write_buf.empty())
    {
        int send_size = m_write_buf.size();
        if (send_size > NETWORK_MAX_SIZE)
            send_size = NETWORK_MAX_SIZE;

        int ret = netlib_send(m_handle, m_write_buf.getBuffer(), send_size);
        if (ret <= 0)
            break;

        m_write_buf.read(nullptr, ret);
    }

    if (m_write_buf.empty())
        m_busy = false;
}


void BaseConn::onClose()
{
    netlib_close(m_handle);
}
