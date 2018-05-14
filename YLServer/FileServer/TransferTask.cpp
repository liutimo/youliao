//
// Created by liuzheng on 18-5-14.
//

#include "TransferTask.h"
#include <uuid/uuid.h>
#include "pdu/protobuf/youliao.base.pb.h"
using namespace youliao::pdu;



std::string generateUUID()
{
    std::string rv;

    uuid_t uid = {0};
    uuid_generate(uid);

    if (!uuid_is_null(uid))
    {
        char str_uuid[64] = {0};
        uuid_unparse(uid, str_uuid);
        rv = str_uuid;
    }
    return rv;
}


/**********************************************/
BaseTransferTask::BaseTransferTask(const std::string &taskId, uint32_t fromUserId, uint32_t toUserId, const std::string &fileName, uint32_t fileSize)
{
    m_task_id = taskId;
    m_from_user_id = fromUserId;
    m_to_user_id = toUserId;
    m_file_name = fileName;
    m_file_size = fileSize;
    m_state = Ready;

    m_create_time = time(nullptr);
    m_from_conn = nullptr;
    m_to_conn = nullptr;
}



void BaseTransferTask::setLastUpdateTime()
{
    m_create_time = time(nullptr);
}

/*******************************************************************/
uint32_t OnlineTransferTask::getTransferMode() const
{
    return base::FILE_TYPE_ONLINE;
}

bool OnlineTransferTask::changePullState(uint32_t userId, int fileRole)
{
    bool rv = false;
    do
    {
        rv = checkByUserIDAndFileRole(userId, fileRole);
        if (!rv)
            break;

        if (m_state != Ready && m_state != WaittingSender && m_state != WaittingReceiver)
            break;

        //第一个用户进入
        if (m_state == Ready)
        {
            if (fileRole == base::CLIENT_REALTIME_SENDER)
                m_state = WaittingReceiver;
            else
                m_state = WaittingSender;
        }
        else
        {
            if (m_state == WaittingReceiver)
            {
                if (fileRole != base::CLIENT_REALTIME_RECVER)
                    break;
            }
            else if (m_state == WaittingSender)
            {
                if (fileRole != base::CLIENT_REALTIME_SENDER)
                    break;
            }

            m_state = WaittingTransfer;
        }

        setLastUpdateTime();
        rv = true;
    }while (0);

    return rv;
}

bool OnlineTransferTask::checkByUserIDAndFileRole(uint32_t userId, int fileRole) const
{
    bool rv = false;

    if (fileRole == base::CLIENT_REALTIME_SENDER)
    {
        if (checkFromUserID(userId))
            rv = true;
    }
    else if(fileRole == base::CLIENT_REALTIME_RECVER)
    {
        if (checkToUserID(userId))
            rv = true;
    }
    return rv;
}

int OnlineTransferTask::doRecvData(uint32_t userId, uint32_t offset, const char *data, uint32_t dataSize)
{
    int rv = -1;
    do
    {
        //检查是否时发送者
        if (!checkFromUserID(userId))
            break;

        //检查状态
        if (m_state != WaittingTransfer && m_state != Transfering)
            break;

        if (m_state == WaittingTransfer)
            m_state = Transfering;

        setLastUpdateTime();
        rv = 0;
    }while (0);

    return rv;
}

int OnlineTransferTask::doPullFileRequest(uint32_t userId, uint32_t offset, uint32_t dataSize, std::string *data)
{
    int rv = -1;
    do
    {
        //检查状态
        if (m_state != WaittingTransfer && m_state != Transfering)
            break;

        if (m_state == WaittingTransfer)
            m_state = Transfering;

        setLastUpdateTime();
        rv = 0;
    }while (0);

    return rv;
}