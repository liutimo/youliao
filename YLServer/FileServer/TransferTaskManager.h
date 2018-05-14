//
// Created by liuzheng on 18-5-14.
//

#ifndef LOGINSERVER_TRANSFERTASKMANAGER_H
#define LOGINSERVER_TRANSFERTASKMANAGER_H

#include "TransferTask.h"

class TransferTaskManager {
public:
    ~TransferTaskManager();
    TransferTaskManager(const TransferTaskManager&) = delete;
    TransferTaskManager&operator=(const TransferTaskManager&) = delete;
    static TransferTaskManager* instance();
    void onTimer(uint64_t tick);

    BaseTransferTask* newTransferTask(uint32_t transMode, const std::string& taskId, uint32_t fromUserId, uint32_t toUserId, const std::string& fileName, uint32_t fileSize);

    bool deleteTransferTask(const std::string &taskId);
    bool deleteTransferTaskByConnClose(const std::string &taskId);

    BaseTransferTask* findByTaskId(const std::string & taskId)
    {
        BaseTransferTask *transferTask = nullptr;
        auto iter = m_transfer_tasks.find(taskId);
        if (iter != m_transfer_tasks.end())
            transferTask = iter->second;
        return transferTask;
    }

private:
    TransferTaskManager();

    static TransferTaskManager *m_instance;

    TransferTaskMap m_transfer_tasks;
};


#endif //LOGINSERVER_TRANSFERTASKMANAGER_H
