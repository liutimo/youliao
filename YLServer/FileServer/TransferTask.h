//
// Created by liuzheng on 18-5-14.
//

#ifndef LOGINSERVER_TRANSFERTASK_H
#define LOGINSERVER_TRANSFERTASK_H

#include <string>
#include <cstring>
#include <iostream>

#include "network/BaseConn.h"

using namespace youliao::network;

enum TransferTaskState {
    Invalid = 0,                //无效状态
    Ready   = 1,

    WaittingSender      = 2,    // 等待发送者
    WaittingReceiver    = 3,    // 等待接受者
    WaittingTransfer    = 4,    // 准备就绪，等待传输
    Transfering         = 5,    // 传输中
    TransferDone        = 6,    // 传输完成

    WaitingUpload   = 7,        // 等待上传
    Uploading       = 8,        // 正在上传中
    UploadEnd       = 9,        // 上传完成

    WaitingDownload     = 10,   // 等待下载
    Downloading         = 11,   // 正在下载中
    DownloadEnd         = 12,   // 下载完成

    Error = 13,                 // 传输失败
};

struct OfflineFileHeader
{
    OfflineFileHeader()
    {
        m_task_id[0] = '\0';
        m_file_name[0] = '\0';


        m_from_user_id = 0;
        uint32_t m_to_user_id = 0;
        uint32_t m_create_time = 0;
        uint32_t m_file_size = 0;
    }

    void setTaskId(std::string &taskId)
    {
        strncpy(m_task_id, taskId.c_str(), 128 < taskId.length() ? 128 : taskId.length());
    }

    void setFromUserID(uint32_t fromId)
    {
        m_from_user_id = fromId;
    }

    void setToUserID(uint32_t toId)
    {
        m_to_user_id = toId;
    }

    void setCreateTime(time_t t)
    {
        m_create_time = (uint32_t)t;
    }

    void setFileName(const std::string &fileName)
    {
        sprintf(m_file_name, fileName.c_str(), 512 < fileName.length() ? 512 : fileName.length());
    }

    std::string getTaskId() const {
        return m_task_id;
    }

    uint32_t getFromUseId() const {
        return m_from_user_id;
    }

    uint32_t getToUserId() const {
        return m_to_user_id;
    }

    uint32_t getCreatTime() const {
        return m_create_time;
    }

    std::string getFileName() const {
        return m_file_name;
    }

    uint32_t getFileSize() const {
        return m_file_size;
    }

    char    m_task_id[128];
    char m_file_name[512];

    uint32_t m_from_user_id;
    uint32_t m_to_user_id;
    uint32_t m_create_time;
    uint32_t m_file_size;
};

class BaseTransferTask {
public:
    BaseTransferTask(const std::string &taskId, uint32_t fromUserId, uint32_t toUserId,
                     const std::string &fileName, uint32_t fileSize);

    virtual ~BaseTransferTask() {};

    virtual uint32_t getTransferMode() const = 0;   //纯虚函数

    inline const std::string &getTaskId() const { return m_task_id; }
    inline uint32_t getFromUserId() const { return m_from_user_id; }
    inline uint32_t getToUserId() const { return m_to_user_id; }
    inline uint32_t getFileSize() const { return m_file_size; }
    inline const std::string &getFileName() const { return m_file_name; }
    inline time_t getCreateTime() const { return m_create_time; }
    inline void setState(int state) { m_state = state; }
    inline int getState() const { return m_state; }

    //获取对方ID
    uint32_t getOpponent(uint32_t userId) const
    {
        return userId == m_from_user_id ? m_to_user_id : m_from_user_id;
    }

    BaseConn* getOpponentConn(uint32_t userId) const
    {
        return userId == m_from_user_id ? m_to_conn : m_from_conn;
    }

    BaseConn *getFromConn() const
    {
        return m_from_conn;
    }

    BaseConn* getToConn() const
    {
        return m_to_conn;
    }

    BaseConn* getConnByUserId(uint32_t userId) const
    {
        if (m_from_user_id == userId)
            return m_from_conn;
        else if (m_to_user_id == userId)
            return m_to_conn;
        else
            return nullptr;
    }

    void setConnByUserID(uint32_t user_id, BaseConn* conn)
    {
        if (m_from_user_id == user_id)
        {
            m_from_conn = conn;
        }
        else if (m_to_user_id == user_id)
        {
            m_to_conn = conn;
        }
    }

    inline bool checkFromUserID(uint32_t user_id) const
    {
        return m_from_user_id == user_id;
    }

    inline bool checkToUserID(uint32_t user_id) const
    {
        return m_to_user_id == user_id;
    }

    inline bool checkUserID(uint32_t user_id) const
    {
        return user_id == m_from_user_id || user_id == m_to_user_id;
    }

    bool isWaitTranfering() const
    {
        bool rv = false;
        if (m_state == WaittingTransfer || m_state == WaitingUpload || m_state == WaitingDownload)
        {
            rv = true;
        }
        return rv;
    }

    void setLastUpdateTime();

    // int StatesNotify(int state, const std::string& task_id, uint32_t user_id);

    // 检查状态
    virtual bool changePullState(uint32_t user_id, int file_role) {
        return false;
    }

    // 检查输入是否合法
    virtual bool checkByUserIDAndFileRole(uint32_t user_id, int file_role) const { return false; }

    virtual int doRecvData(uint32_t user_id, uint32_t offset, const char* data, uint32_t data_size) { return -1; }

    virtual int doPullFileRequest(uint32_t user_id, uint32_t offset, uint32_t data_size, std::string* data) { return -1; }


protected:
    std::string     m_task_id;
    uint32_t        m_from_user_id;
    uint32_t        m_to_user_id;
    std::string     m_file_name;
    uint32_t        m_file_size;
    time_t          m_create_time;

    int             m_state;        //传输状态

    BaseConn        *m_from_conn;
    BaseConn        *m_to_conn;
};


class OnlineTransferTask : public BaseTransferTask
{
public:
    OnlineTransferTask(const std::string& taskId, uint32_t fromUserId, uint32_t toUserId, const std::string& fileName, uint32_t fileSize)
            : BaseTransferTask(taskId, fromUserId, toUserId, fileName, fileSize) {

    }

    virtual ~OnlineTransferTask() {}

    virtual uint32_t getTransferMode() const override;

    virtual bool changePullState(uint32_t userId, int fileRole) override;
    virtual bool checkByUserIDAndFileRole(uint32_t userId, int fileRole) const;

    virtual int doRecvData(uint32_t userId, uint32_t offset, const char* data, uint32_t dataSize) ;
    virtual int doPullFileRequest(uint32_t userId, uint32_t offset, uint32_t dataSize, std::string* data);

};

typedef std::map<std::string, BaseTransferTask*> TransferTaskMap;
typedef std::map<BaseConn *, BaseTransferTask*> TransferTaskConnMap;



std::string generateUUID();
#endif //LOGINSERVER_TRANSFERTASK_H
