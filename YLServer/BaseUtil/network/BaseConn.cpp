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
#include "../util/util.h"
using namespace youliao::network;
using namespace youliao::pdu;

static BaseConn* findBaseConn(BaseConnMap_t *connMap, net_handle_t handle)
{
    auto iter = connMap->find(handle);
    if (iter == connMap->end())
        return nullptr;

    return iter->second;
}

void youliao::network::baseconn_callback(callback_data data, uint8_t msg, net_handle_t handle, void *pParam)
{
    NO_USERD(pParam);
    if (data == nullptr)
        return;

    BaseConnMap_t *baseConnMap = static_cast<BaseConnMap_t*>(data);
    BaseConn *baseConn = findBaseConn(baseConnMap, handle);

    if (!baseConn)
        return;

    switch (msg)
    {
        case NETWORK_CONFIRM:
            baseConn->onConfirm();
            break;
        case NETWORK_CLOSE:
            baseConn->onClose();
            break;
        case NETWORK_READ:
            baseConn->onRead();
            break;
        case NETWORK_WRITE:
            baseConn->onWrite();
        default:
            break;
    }


}


BaseConn::BaseConn()
{
    m_busy = false;
    m_handle = -1;
}

BaseConn::~BaseConn()
{

}

int BaseConn::sendBasePdu(BasePdu *basePdu)
{
    return send(basePdu->getBuffer(), basePdu->getBufferLength());
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

        int ret = netlib_send(m_handle, buf + offest, size);

        if (ret <= 0)
        {
            log("netliib_send failed: %s", strerror(errno));
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
        {
            break;
        }
        m_read_buf.incrWriteOffest(ret);
    }


    youliao::pdu::BasePdu *basePdu = nullptr;

    while ( (basePdu = youliao::pdu::BasePdu::readPduFromBuffer(m_read_buf)) != nullptr)
    {
        //读pdu,
        handlePdu(basePdu);
        delete basePdu;
        basePdu = nullptr;
    }


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
        {
            break;
        }

        m_write_buf.read(nullptr, ret);
    }

    if (m_write_buf.empty())
        m_busy = false;
}


void BaseConn::onClose()
{
    netlib_close(m_handle);
}
