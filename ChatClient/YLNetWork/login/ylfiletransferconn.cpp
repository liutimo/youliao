#include "ylfiletransferconn.h"
#include "../base/util.h"
#include "../base/netlib.h"
#include "globaldata.h"
#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.file.pb.h"
#include "YLFileTransfer/ylfiletransfermanager.h"

using namespace youliao::network;
using namespace youliao::pdu;


static BaseConnMap_t g_file_conn_map;


YLFileTransferConn *findFileTransferConnByHandle(int handle)
{
    auto iter = g_file_conn_map.find(handle);
    if (iter != g_file_conn_map.end())
        return static_cast<YLFileTransferConn *>(iter->second);
    else
        return nullptr;
}



YLFileTransferConn::YLFileTransferConn(std::string &taskId)
    : m_task_id(taskId)
{

}

void YLFileTransferConn::connect(const std::string &server_ip, uint16_t port)
{
    m_handle = netlib_connect(server_ip, port, baseconn_callback, (void*)&g_file_conn_map);

    if (m_handle == -1)
    {
        log("连接文件服务器(%s:%d)失败.", server_ip.c_str(), port);
        onClose();
        return;
    }
    g_file_conn_map.insert(std::make_pair(m_handle, this));

}

void YLFileTransferConn::onConfirm()
{
    log("连接文件服务器成功");
    startHeartBeat();

    YLTransferFileEntity entity;
    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(m_task_id, entity))
    {
        log("无法获得文件信息， task_id: %s", m_task_id.c_str());
        return;
    }

    file::LoginFileServerRequest request;
    request.set_task_id(m_task_id);
    request.set_user_id(GlobalData::getCurrLoginUserId());
    request.set_client_role(static_cast<base::ClientFileRole>(entity.m_client_role));

    //发送
    BasePdu basePdu;
    basePdu.setSID(base::SID_FILE);
    basePdu.setCID(base::CID_FILE_LOGIN_REQUEST);
    basePdu.writeMessage(&request);
    sendBasePdu(&basePdu);
}

void YLFileTransferConn::onRead()
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


void YLFileTransferConn::handlePdu(BasePdu* pdu)
{
    //忽略心跳包
    if (pdu->getCID() == base::CID_OTHER_HEARTBEAT)
    {
         delete pdu;
         return;
    }
    g_file_condition.lock();
    g_file_pdu_list.push_back(std::make_pair(m_handle, pdu));
    g_file_condition.signal();
    g_file_condition.unlock();
}

void YLFileTransferConn::shutdown()
{
    stopHeartBeat();

    if (m_handle == NETWORK_ERROR)
    {
        netlib_close(m_handle);
        g_file_conn_map.erase(m_handle);
    }
}

void YLFileTransferConn::startHeartBeat()
{

}

void YLFileTransferConn::stopHeartBeat()
{

}

void YLFileTransferConn::onClose()
{
    shutdown();
}

bool YLFileTransferConn::startFileTransfer()
{
    YLTransferFileEntity entity;
    if (YLTransferFileEntityManager::instance()->getFileInfoByTaskId(m_task_id, entity))
    {
        log("连接文件服务器 ip:%s, port:%d", entity.m_ip.c_str(), entity.m_port);
        connect(entity.m_ip, entity.m_port);
    }
    if (m_handle != NETWORK_ERROR)
        return true;
    return false;
}

void YLFileTransferConn::stopFileTransfer()
{
    shutdown();
}


