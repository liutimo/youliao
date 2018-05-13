//
// Created by liuzheng on 18-5-13.
//

#include "MsgServerConn.h"
#include "util/util.h"
#include "network/netlib.h"

#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"

static BaseConnMap_t g_msg_server_conn_map;

void msgServerConnCallback(void *callback_data, uint8_t msg, int handle, void*)
{
    if (msg == NETWORK_CONNECT)
    {
        MsgServerConn *conn = new MsgServerConn;
        conn->onConnect(handle);
    }
}


MsgServerConn::MsgServerConn() : m_connected(false)
{
}

MsgServerConn::~MsgServerConn()
{

}

void MsgServerConn::close()
{
    log("关闭消息服务器连接, handle = %d", m_handle);
    m_connected = false;
    if (m_handle != NETWORK_ERROR)
    {
        netlib_close(m_handle);
        g_msg_server_conn_map.erase(m_handle);
    }
}

void MsgServerConn::onConnect(net_handle_t handle)
{
    m_handle = handle;

    g_msg_server_conn_map.insert(std::make_pair(handle, this));
    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK, (void*)baseconn_callback);
    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)&g_msg_server_conn_map);
}

void MsgServerConn::onClose()
{
    close();
}

void MsgServerConn::handlePdu(BasePdu *pdu)
{
    switch (pdu->getCID())
    {
        case base::CID_SERVER_FILE_SERVER_IP_REQUEST:
            _HandleGetFileServerIpRequest(pdu);
            break;
        default:
            log("位置的CID:%d", pdu->getCID());
            break;
    }
}


void MsgServerConn::_HandleGetFileServerIpRequest(BasePdu *basePdu)
{
    server::FileServerIPRespone respone;

    base::IpAddress *address = respone.add_ip_addr_list();
    address->set_ip("127.0.0.1");
    address->set_port(9002);

    BasePdu pdu;
    pdu.setSID(base::SID_SERVER);
    pdu.setCID(base::CID_SERVER_FILE_SERVER_IP_RESPONE);
    pdu.writeMessage(&respone);
    sendBasePdu(&pdu);
}