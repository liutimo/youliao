#include "msgservconn.h"
#include "netlib.h"
#include "util.h"
#include "protobuf/youliao.base.pb.h"
#include "pdusender.h"
static BaseConnMap_t g_msg_serv_conn_map;

MsgServConn::MsgServConn()
{

}

void MsgServConn::onRead()
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
        m_read_buf.incrWriteOffest(ret);
    }


    youliao::pdu::BasePdu *basePdu = nullptr;

    while ( (basePdu = youliao::pdu::BasePdu::readPduFromBuffer(m_read_buf)) != nullptr)
    {
        //读pdu,
        handlePdu(basePdu);
    }
}

void MsgServConn::connect(const std::string &server_ip, uint16_t port)
{
    m_handle = netlib_connect(server_ip, port, baseconn_callback, (void*)&g_msg_serv_conn_map);

    if (m_handle == -1)
    {
        log("连接消息服务器(%s:%d)失败.", server_ip.c_str(), port);
        onClose();
        return;
    }
    log("连接消息服务器成功");
    g_msg_serv_conn_map.insert(std::make_pair(m_handle, this));

    log("启动pdu发送线程");
    PduSender *pduSender = PduSender::instance();
    pduSender->setMsgServConn(this);
}

void MsgServConn::handlePdu(BasePdu *pdu)
{
    //忽略心跳包
//    if (pdu->getCID() == base::CID_HEARTBEAT)
//    {
//         delete pdu;
//         rteurn;
//    }
    g_condition.lock();
    g_pdu_list.push_back(pdu);
    g_condition.signal();
    g_condition.unlock();
}
