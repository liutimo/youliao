#include "ylfiletransferthread.h"
#include "ylfiletransfermanager.h"
#include "yltransferfile.h"
#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.file.pb.h"
using namespace youliao::pdu;

const uint32_t FILE_TRANSFER_BLOCK_SIZE = 1024 * 34;

YLFileTransferThread::YLFileTransferThread()
{

}

YLFileTransferThread::~YLFileTransferThread()
{

}

void YLFileTransferThread::shutDown()
{
    //终止线程
}

void YLFileTransferThread::run()
{

}

void YLFileTransferThread::openFileSocketByTaskId(std::string &taskId)
{
    YLFileTransferConn *conn = findFileTransferConnByTaskId(taskId);
    if (!conn)
    {
        conn = new YLFileTransferConn(taskId);
        m_file_transfer_conn_map.insert(std::make_pair(taskId, conn));
        //连接
        conn->startFileTransfer();
    }
}

void YLFileTransferThread::closeFileSocketByTaskId(std::string &taskId)
{
    AutoLock autoLock(m_mutex);

    YLFileTransferConn* conn = m_file_transfer_conn_map[taskId];
    if (conn)
    {
        conn->stopFileTransfer();
        delete conn;
        m_file_transfer_conn_map.erase(taskId);
    }
}

bool YLFileTransferThread::acceptFileTransfer(const std::string &taskId)
{
    auto conn = findFileTransferConnByTaskId(taskId);
    if (conn)
    {
        YLTransferFileEntity entity;
        if (YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId, entity))
        {
            base::TransferFileType mode = entity.m_client_role == base::CLIENT_OFFLINE_DOWNLOAD ? base::FILE_TYPE_OFFLINE : base::FILE_TYPE_ONLINE;
            file::GetFileBlockRequest request;
            request.set_task_id(taskId);
            request.set_user_id(entity.m_to_id);
            request.set_trans_mode(mode);
            request.set_offest(0);
            entity.m_file_size > FILE_TRANSFER_BLOCK_SIZE ? request.set_data_size(FILE_TRANSFER_BLOCK_SIZE) : request.set_data_size(entity.m_file_size);

            BasePdu basePdu;
            basePdu.setSID(base::SID_FILE);
            basePdu.setCID(base::CID_FILE_GET_BLOCK_REQUEST);
            basePdu.writeMessage(&request);
            conn->sendBasePdu(&basePdu);
            return true;
        }
    }
    return false;
}

bool YLFileTransferThread::rejectFileTransfer(const string &taskId)
{
    auto conn = findFileTransferConnByTaskId(taskId);
    if (conn)
    {
        YLTransferFileEntity entity;
        if (YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId, entity))
        {
            file::ClientFileState fileState;
            fileState.set_state(base::CLIENT_FILE_REFUSE);
            fileState.set_task_id(taskId);
            fileState.set_user_id(entity.m_to_id);

            BasePdu basePdu;
            basePdu.setSID(base::SID_FILE);
            basePdu.setCID(base::CID_FILE_STATE);
            basePdu.writeMessage(&fileState);
            conn->sendBasePdu(&basePdu);
            return true;
        }
    }
    return false;
}

bool YLFileTransferThread::cancelFileTransfer(const string &taskId)
{
    auto conn = findFileTransferConnByTaskId(taskId);
    if (conn)
    {
        YLTransferFileEntity entity;
        if (YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId, entity))
        {
            if (entity.m_file_object != nullptr)
            {
                delete entity.m_file_object;
                entity.m_file_object = nullptr;
            }
            uint32_t userId = 0;
            if (entity.m_client_role == base::CLIENT_REALTIME_SENDER || entity.m_client_role == base::CLIENT_OFFLINE_UPLOAD)
                userId = entity.m_from_id;
            else
                userId = entity.m_to_id;

            file::ClientFileState fileState;
            fileState.set_state(base::CLIENT_FILE_CANCEL);
            fileState.set_task_id(taskId);
            fileState.set_user_id(userId);

            BasePdu basePdu;
            basePdu.setSID(base::SID_FILE);
            basePdu.setCID(base::CID_FILE_STATE);
            basePdu.writeMessage(&fileState);
            conn->sendBasePdu(&basePdu);
            YLTransferFileEntityManager::instance()->deleteFileInfoByTaskId(taskId);
            return true;
        }
    }
    return false;
}

YLFileTransferConn* YLFileTransferThread::findFileTransferConnByTaskId(const string &taskId)
{
    auto iter = m_file_transfer_conn_map.find(taskId);
    if (iter != m_file_transfer_conn_map.end())
    {
        return iter->second;
    }

    return nullptr;
}

void YLFileTransferThread::closeAllFileSockets()
{
    for (auto iter = m_file_transfer_conn_map.begin(); iter != m_file_transfer_conn_map.end(); ++iter)
    {
        YLFileTransferConn *conn = iter->second;
        conn->stopFileTransfer();
        delete conn;
        conn = nullptr;
    }
    m_file_transfer_conn_map.clear();
}
