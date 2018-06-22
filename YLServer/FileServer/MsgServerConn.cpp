//
// Created by liuzheng on 18-5-13.
//

#include "MsgServerConn.h"
#include "util/util.h"
#include "network/netlib.h"
#include "TransferTask.h"
#include "TransferTaskManager.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"

static BaseConnMap_t g_msg_server_conn_map;

MsgServerConn* get_msg_server_conn()
{
    return (MsgServerConn*)g_msg_server_conn_map.begin()->second;
}


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
        case base::CID_SERVER_FILE_TRANSFER_REQUEST:
            _HandleMsgFileTransfreRequest(pdu);
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


void MsgServerConn::_HandleMsgFileTransfreRequest(BasePdu *pdu)
{
    server::FileTransferRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t fromId = request.from_user_id();
    uint32_t toId = request.to_user_id();

    server::FileTransferRespone respone;
    respone.set_result_code(1);
    respone.set_from_user_id(fromId);
    respone.set_to_user_id(toId);
    respone.set_file_name(request.file_name());
    respone.set_file_size(request.file_size());
    respone.set_task_id("");
    respone.set_trans_mode(request.trans_mode());

    bool rv = false;

    do {
        std::string taskId = generateUUID();
        if (taskId.empty())
            break;

        BaseTransferTask* transferTask = TransferTaskManager::instance()->newTransferTask(request.trans_mode(), taskId, fromId, toId, request.file_name(), request.file_size());

        if (transferTask == nullptr)
        {
            //创建失败
            break;
        }

        respone.set_result_code(0);
        respone.set_task_id(taskId);
        rv = true;
    }while (0);

    BasePdu basePdu;
    basePdu.setSID(base::SID_SERVER);
    basePdu.setCID(base::CID_SERVER_FILE_TRANSFER_RESPONE);
    basePdu.writeMessage(&respone);
    sendBasePdu(&basePdu);

    if (!rv) //任务创建失败
    {
        //告知客户端，无法传输文件
    }
}