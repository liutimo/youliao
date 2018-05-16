#include "ylfiletransferreceiver.h"
#include "YLNetWork/base/util.h"
#include "globaldata.h"
#include "YLNetWork/base/BasePdu.h"
#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.file.pb.h"
#include "ylfiletransfermanager.h"
#include "yltransferfile.h"
#include "YLNetWork/login/ylfiletransferconn.h"
#include <list>

using namespace youliao::pdu;

YLFileTransferReceiver *YLFileTransferReceiver::m_instance = nullptr;
std::list<std::pair<int, BasePdu*>> g_file_pdu_list;
Condition           g_file_condition;

YLFileTransferReceiver::YLFileTransferReceiver(QObject *parent) : QThread(parent)
{

}

YLFileTransferReceiver* YLFileTransferReceiver::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new YLFileTransferReceiver;
        m_instance->start();
    }

    return m_instance;
}

void YLFileTransferReceiver::run()
{
    for(;;)
    {
        g_file_condition.lock();

        if (g_file_pdu_list.empty())
            g_file_condition.wait();

        auto elem = g_file_pdu_list.front();
        m_current_handle = elem.first;
        BasePdu *basePdu = elem.second;

        g_file_pdu_list.pop_front();
        g_file_condition.unlock();

        _HandleBasePdu(basePdu);
        delete basePdu;
    }
}


void YLFileTransferReceiver::_HandleBasePdu(BasePdu *pdu)
{
    switch (pdu->getCID()) {
    case base::CID_FILE_LOGIN_RESPONE:
        _HandleLoginFileServerRespone(pdu);
        break;
    case base::CID_FILE_STATE:
        _HandleFileState(pdu);
        break;
    case base::CID_FILE_GET_BLOCK_REQUEST:
        _HandleGetFileBlockRequest(pdu);
        break;
    case base::CID_FILE_GET_BLOCK_RESPONE:
        _HandleGetFileBlockRespone(pdu);
        break;
    default:
        break;
    }
}



void YLFileTransferReceiver::_HandleLoginFileServerRespone(BasePdu *basePdu)
{
    file::LoginFileServerRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t resultCode = respone.result_code();
    std::string taskId = respone.task_id();

    if (resultCode != 0)
    {
        log("登录文件服务器失败");
        return;
    }

    YLTransferFileEntity entity;

    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId, entity))
    {
        log("没法找到文件信息, taskId:%s", taskId.c_str());
        return;
    }
    log("登录文件服务器成功");

    //提示UI插入ITEM
    if (base::CLIENT_REALTIME_SENDER == entity.m_client_role || base::CLIENT_OFFLINE_UPLOAD == entity.m_client_role)
    {
        //通知UI。
        //item 类型  发送文件
        emit addSendFileItem(entity.m_to_id, taskId.c_str());
    }
    else if(base::CLIENT_REALTIME_RECVER == entity.m_client_role || base::CLIENT_OFFLINE_DOWNLOAD == entity.m_client_role)
    {
        //通知UI
        //item 类型 接收文件
        emit addRecvFileItem(entity.m_from_id, taskId.c_str());
    }
}



void YLFileTransferReceiver::_HandleFileState(BasePdu *pdu)
{
    file::ClientFileState fileState;
    fileState.ParseFromString(pdu->getMessage());

    base::ClientFileState state = fileState.state();
    std::string taskId = fileState.task_id();

    YLTransferFileEntity entity;
    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId, entity))
        return;

    switch (state) {
    case base::CLIENT_FILE_PEER_READY:
        break;
    case base::CLIENT_FILE_CANCEL:
        {
            if (entity.m_file_object)
            {
                delete entity.m_file_object;
                entity.m_file_object = nullptr;
            }
            YLTransferFileEntityManager::instance()->updateFileInfoBysTaskID(entity);
            //通知UI
        }
        break;
    case base::CLIENT_FILE_REFUSE:
        {
            if (entity.m_file_object)
            {
                delete entity.m_file_object;
                entity.m_file_object = nullptr;
            }
            YLTransferFileEntityManager::instance()->updateFileInfoBysTaskID(entity);
            //通知UI
        }
        break;
    case base::CLIENT_FILE_DONE:
        {
            if (entity.m_file_object)
            {
                delete entity.m_file_object;
                entity.m_file_object = nullptr;
            }
            YLTransferFileEntityManager::instance()->updateFileInfoBysTaskID(entity);
            //通知UI
        }
        break;
    default:
        break;
    }
}


void YLFileTransferReceiver::_HandleGetFileBlockRequest(BasePdu *basePdu)
{
    file::GetFileBlockRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t fileSize   = request.data_size();
    uint32_t fileOffest = request.offest();
    std::string taskId  = request.task_id();

    YLTransferFileEntity entity;
    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId, entity))
        return;

//    if (!entity.m_file_object);
//        return;

    std::string buff;
    entity.m_file_object->readBlock(fileOffest, fileSize, buff);    //读取文件

    file::GetFileBlockRespone respone;
    respone.set_result_code(0);
    respone.set_user_id(entity.m_from_id);
    respone.set_task_id(taskId);
    respone.set_offest(fileOffest);
    respone.set_file_data(buff);

    //发送
    auto conn = findFileTransferConnByHandle(m_current_handle);
    if (conn)
    {
        BasePdu pdu;
        pdu.setSID(base::SID_FILE);
        pdu.setCID(base::CID_FILE_GET_BLOCK_RESPONE);
        pdu.writeMessage(&respone);
        conn->sendBasePdu(&pdu);
    }

    entity.m_progress = fileOffest + fileSize;
    if (entity.m_progress < entity.m_file_size)
    {
        //通知UI更新进度条
        emit updateProgressBar(entity.m_to_id, taskId.c_str(), entity.m_progress);
    }
    else
    {
        //文件传输完成
        if (entity.m_file_object)
        {
            delete entity.m_file_object;
            entity.m_file_object = nullptr;
        }
        //通知更新UI
        emit transferComplete(entity.m_to_id, taskId.c_str());
    }

    YLTransferFileEntityManager::instance()->updateFileInfoBysTaskID(entity);
}

void YLFileTransferReceiver::_HandleGetFileBlockRespone(BasePdu *basePdu)
{
    file::GetFileBlockRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t resultCode = respone.result_code();
    if (resultCode != 0)
        return;

    std::string taskId      = respone.task_id();
    const std::string &data = respone.file_data();
    uint32_t offest         = respone.offest();
    uint32_t dataSize       = data.size();

    YLTransferFileEntity entity;
    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId, entity))
        return;

    if (!entity.m_file_object->writeBlock(offest, dataSize, data.data()))
        return;

    entity.m_progress = offest + dataSize;
    if (entity.m_progress < entity.m_file_size)
    {
        //更新ui

        //继续请求
        base::TransferFileType mode = entity.m_client_role == base::CLIENT_OFFLINE_DOWNLOAD ? base::FILE_TYPE_OFFLINE : base::FILE_TYPE_OFFLINE;
        file::GetFileBlockRequest request;
        request.set_task_id(taskId);
        request.set_user_id(entity.m_to_id);
        request.set_trans_mode(mode);
        request.set_offest(entity.m_progress);

        uint32_t requestSize = entity.m_file_size - entity.m_progress;
        requestSize > dataSize ? request.set_data_size(dataSize) : request.set_data_size(requestSize);

        //发送
        auto conn = findFileTransferConnByHandle(m_current_handle);
        if (conn)
        {
            BasePdu pdu;
            pdu.setSID(base::SID_FILE);
            pdu.setCID(base::CID_FILE_GET_BLOCK_REQUEST);
            pdu.writeMessage(&request);
            conn->sendBasePdu(&pdu);
        }
    }
    else
    {
        //文件传输完成
        if (entity.m_file_object)
        {
            delete entity.m_file_object;
            entity.m_file_object = nullptr;
        }

        file::ClientFileState fileState;
        fileState.set_state(base::CLIENT_FILE_DONE);
        fileState.set_task_id(taskId);
        fileState.set_user_id(entity.m_to_id);
        //发送
        auto conn = findFileTransferConnByHandle(m_current_handle);
        if (conn)
        {
            BasePdu pdu;
            pdu.setSID(base::SID_FILE);
            pdu.setCID(base::CID_FILE_STATE);
            pdu.writeMessage(&fileState);
            conn->sendBasePdu(&pdu);
        }

        //更新UI
    }

    YLTransferFileEntityManager::instance()->updateFileInfoBysTaskID(entity);

}
