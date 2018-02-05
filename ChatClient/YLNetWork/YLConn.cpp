//
// Created by liuzheng on 18-2-5.
//

#include "YLConn.h"
/////////////////////////////////////////////////////
static YLConn* findConn(ConnMap* conn_map, int fd)
{
    YLConn *pConn = nullptr;
    auto iter = conn_map->find(fd);

    if (iter != conn_map->end())
    {
        pConn = iter->second;
    }

    return pConn;
}

void conn_callback(void* callback_data, uint8_t msg, uint32_t fd, void* pParam)
{

    YLConn *pConn = new YLConn();
    pConn->setFD(fd);

    switch (msg)
    {
        case NETLIB_MSG_CONFIRM:
            pConn->OnConfirm();
            break;
        case NETLIB_MSG_READ:
            pConn->onRead();
            break;
        case NETLIB_MSG_WRITE:
            pConn->onWrite();
            break;
        case NETLIB_MSG_CLOSE:
            pConn->onClose();
        default:
            break;
    }
}

void readPolicyFile()
{

}

/////////////////////////////////////////////////////
YLConn::YLConn()
{
    m_busy = false;
    m_fd = -1;
    m_recv_bytes = 0;

    m_last_send_tick = m_last_recv_tick = get_tick_count();
}

YLConn::~YLConn()
{

}

int YLConn::send(void *data, int len)
{
    m_last_recv_tick = get_tick_count();

    if (m_busy)
    {
        m_out_buf.write(data, len);
        return len;
    }

    int offest = 0;
    int remain = len;
    while (remain > 0)
    {
        int send_size = remain;

        if (send_size > NETLIB_MAX_SOCKET_BUF_SIZE)
            send_size = NETLIB_MAX_SOCKET_BUF_SIZE;

        int ret = netlib_send(m_fd, (char*)data + offest, send_size);

        if (ret <= 0)
        {
            ret = 0;
            break;
        }
        offest += ret;
        remain -= ret;
    }

    if (remain > 0)
    {
        m_out_buf.write((char*)data + offest, remain);
        m_busy = true;
    }
    else
    {
        onWriteCompelete();
    }

    return len;
}

void YLConn::onRead()
{
    for (;;)
    {
        //读缓冲区中  剩余的空闲内存 长度
        uint32_t  free_buf_len = m_in_buf.getAllocSize() - m_in_buf.getWriteOffest();

        if (free_buf_len < READ_BUFFER_SIZE)
            m_in_buf.extend(READ_BUFFER_SIZE);

        int ret = netlib_recv(m_fd, m_in_buf.getBuffer() + m_in_buf.getWriteOffest(), READ_BUFFER_SIZE);

        if (ret <= 0)
            break;

        m_recv_bytes += ret;
        m_in_buf.incrWriteOffest(ret);

        m_last_recv_tick = get_tick_count();
    }

    //从读缓冲中读取YLPdu
    YLPdu *pPdu = nullptr;
    try
    {
        while ( (pPdu = YLPdu::readPdu(m_in_buf.getBuffer(), m_in_buf.getWriteOffest())))
        {
            uint32_t  pdu_len = pPdu->getLength();

            //处理pdu
            handlePdu(pPdu);

            //将已经读取的数据内存置空
            //具体看read的实现
            m_in_buf.read(NULL, pdu_len);

            delete pPdu;
            pPdu = nullptr;
        }
    }
    catch (YLPduException& ex)
    {
        if (pPdu)
        {
            delete pPdu;
            pPdu = nullptr;
        }

        onClose();
    }
}

//将写缓冲区中的数据全部发送出去
void YLConn::onWrite()
{
    if(!m_busy)
        return;

    while (m_out_buf.getWriteOffest() > 0)
    {
        int send_size = m_out_buf.getWriteOffest();
        if (send_size > NETLIB_MAX_SOCKET_BUF_SIZE)
            send_size = NETLIB_MAX_SOCKET_BUF_SIZE;

        int ret = netlib_send(m_fd, m_out_buf.getBuffer(), send_size);

        if (ret <= 0)
        {
            ret = 0;
            break;
        }

        m_out_buf.read(nullptr, ret);
    }

    if (m_out_buf.getWriteOffest() == 0)
        m_busy = false;
}

