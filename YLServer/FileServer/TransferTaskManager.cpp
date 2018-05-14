//
// Created by liuzheng on 18-5-14.
//

#include "TransferTaskManager.h"
#include "pdu/protobuf/youliao.base.pb.h"

using namespace youliao::pdu;

TransferTaskManager* TransferTaskManager::m_instance = nullptr;

TransferTaskManager* TransferTaskManager::instance()
{
    if (m_instance == nullptr)
        m_instance = new TransferTaskManager;
    return m_instance;
}

TransferTaskManager::TransferTaskManager()
{

}

void TransferTaskManager::onTimer(uint64_t tick)
{
    for (auto iter = m_transfer_tasks.begin(); iter != m_transfer_tasks.end();)
    {
        BaseTransferTask *task = iter->second;
        if (task == nullptr)
        {
            m_transfer_tasks.erase(iter++);
            continue;
        }

        if (task->getState() != WaitingUpload && task->getState() == TransferDone)
        {
            long esp = time(nullptr) - task->getCreateTime();
            if (esp > 3600)
            {
                if (task->getFromConn())
                {
                    //关闭连接
                }

                if (task->getToConn())
                {
                    //关闭连接
                }
                delete task;
                m_transfer_tasks.erase(iter++);
                continue;
            }
        }
        ++iter;
    }
}


BaseTransferTask* TransferTaskManager::newTransferTask(uint32_t transMode, const std::string &taskId,
                                                       uint32_t fromUserId, uint32_t toUserId,
                                                       const std::string &fileName, uint32_t fileSize)
{
    BaseTransferTask *transferTask = nullptr;
    auto iter = m_transfer_tasks.find(taskId);

    if (iter == m_transfer_tasks.end())
    {
        if (transMode == base::FILE_TYPE_ONLINE)
        {
            transferTask = new OnlineTransferTask(taskId, fromUserId, toUserId, fileName, fileSize);
        }
        else if (transMode == base::FILE_TYPE_OFFLINE)
        {
            //离线文件
        }
        else
        {
            //
        }

        if (transferTask)
        {
            m_transfer_tasks.insert(std::make_pair(taskId, transferTask));
        }
    }
    else
    {
        //
    }
    return  transferTask;
}

bool TransferTaskManager::deleteTransferTaskByConnClose(const std::string &taskId)
{
    bool rv = false;
    auto iter = m_transfer_tasks.find(taskId);
    if (iter != m_transfer_tasks.end())
    {
        BaseTransferTask *transferTask = iter->second;
        if (transferTask->getTransferMode() == base::FILE_TYPE_ONLINE)
        {
            //未连接，直接删除
            if (transferTask->getFromConn() == nullptr && transferTask->getToConn() == nullptr)
            {
                delete transferTask;
                m_transfer_tasks.erase(iter);
                rv = true;
            }
        }
        else
        {
            if (transferTask->getState() != WaitingUpload)
            {
                delete transferTask;
                m_transfer_tasks.erase(iter);
                rv = true;
            }

        }

        return rv;
    }
}

bool TransferTaskManager::deleteTransferTask(const std::string &taskId)
{
    bool rv = false;
    auto iter = m_transfer_tasks.find(taskId);

    if(iter != m_transfer_tasks.end())
    {
        delete iter->second;
        m_transfer_tasks.erase(iter);
        rv = true;
    }

    return rv;
}

