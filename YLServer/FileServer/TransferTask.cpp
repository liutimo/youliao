//
// Created by liuzheng on 18-5-14.
//

#include "TransferTask.h"
#include <uuid/uuid.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include "util/util.h"
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

const char *getCurrnetOfflinePath()
{
    static const char *g_current_save_path = nullptr;

    if (g_current_save_path == nullptr)
    {
        static char tmp[1024];
        char workPath[1024];
        if (!getcwd(workPath, 1024))
        {
            log("getcwd %s failed\", work_path");
        }
        else
        {
            snprintf(tmp, 1024, "%s/offline_file", workPath);
        }

        log("离线文件保存在%s", tmp);


        int ret = mkdir(tmp, 0755);
        if ((ret != 0) && (errno != EEXIST))
            log("创建离线文件夹%s失败！！", tmp);
        g_current_save_path = tmp;
    }

    return g_current_save_path;
}

static FILE* openByRead(const std::string &taskId, uint32_t userId)
{
    FILE *fp = nullptr;
    if (taskId.length() > 2)
    {
        char savePath[1024];
        snprintf(savePath, 1024, "%s/%s/%s", getCurrnetOfflinePath(), taskId.substr(0, 2).c_str(), taskId.c_str());
        fp = fopen(savePath, "rb");
        if (!fp)
            log("打开文件%s失败", savePath);
    }
    return fp;
}

static FILE* openByWrite(const std::string &taskId, uint32_t userId)
{
    FILE *fp = nullptr;
    if (taskId.length() > 2)
    {
        char savePath[1024];
        snprintf(savePath, 1024, "%s/%s", getCurrnetOfflinePath(), taskId.substr(0, 2).c_str());
        int ret = mkdir(savePath, 0755);
        if ((ret != 0) && (errno != EEXIST))
            log("创建文件夹%s失败", savePath);
        else
        {
            strncat(savePath, "/", 1024);
            strncat(savePath, taskId.c_str(), 1024);
            fp = fopen(savePath, "ab+");
            if (!fp)
                log("打开文件失败");
        }
    }
    return  fp;
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

//////////////////////////////////////////////////
OfflineTransferTask* OfflineTransferTask::loadFromDisk(const std::string &taskId, uint32_t userId)
{
    OfflineTransferTask *offlineTransferTask = nullptr;
    FILE *fp = openByRead(taskId, userId);
    if (fp)
    {
        OfflineFileHeader fileHeader;
        size_t size = fread(&fileHeader, 1, sizeof(fileHeader), fp);
        if (size == sizeof(fileHeader))
        {
            fseek(fp, 0L, SEEK_END);
            size_t  fileSize = static_cast<size_t>(ftell(fp)) - size;
            if (fileSize == fileHeader.getFileSize())
            {
                offlineTransferTask = new OfflineTransferTask(  fileHeader.getTaskId(),
                                                                fileHeader.getFromUseId(),

                                                                fileHeader.getToUserId(),
                                                                fileHeader.getFileName(),
                                                                fileHeader.getFileSize());
                if (offlineTransferTask)
                {
                    offlineTransferTask->setState(WaitingDownload);
                }
            }
        }
        else
            log("读取离线文件头失败");

        fclose(fp);
    }
    return offlineTransferTask;
}

uint32_t OfflineTransferTask::getTransferMode() const
{
    return base::FILE_TYPE_OFFLINE;
}

bool OfflineTransferTask::changePullState(uint32_t userId, int fileRole)
{
    bool rv = false;

    do{
        rv = checkByUserIDAndFileRole(userId, fileRole);
        if (!rv)
            break;

        if (m_state != Ready && m_state != UploadEnd && m_state != WaitingDownload)
            break;

        if (m_state == Ready)
        {
            if (base::CLIENT_OFFLINE_UPLOAD == fileRole)
            {
                //进来的第一个用户必须是CLIENT_OFFLINE_UPLOAD
                m_state = WaitingUpload;
            }
            else
                break;
        }
        else
        {
            if (fileRole == base::CLIENT_OFFLINE_DOWNLOAD)
                m_state = WaitingDownload;
            else
                break;
        }

        setLastUpdateTime();
        rv = true;
    }while (0);

    return rv;
}

bool OfflineTransferTask::checkByUserIDAndFileRole(uint32_t userId, int fileRole) const
{
    // 离线文件传输
    // 1. fileRole必须是CLIENT_OFFLINE_UPLOAD或CLIENT_OFFLINE_DOWNLOAD
    // 2. CLIENT_OFFLINE_UPLOAD则user_id==from_user_id_
    // 3. CLIENT_OFFLINE_DOWNLOAD则user_id==to_user_id_
    bool rv = false;

    if (fileRole == base::CLIENT_OFFLINE_UPLOAD){
        if (checkFromUserID(userId)) {
            rv = true;
        }
    } else if (fileRole == base::CLIENT_OFFLINE_DOWNLOAD) {
        if (checkToUserID(userId)) {
            rv = true;
        }
    }

    return rv;
}

int OfflineTransferTask::doRecvData(uint32_t userId, uint32_t offest, const char *data, uint32_t size)
{
    int rv = -1;
    do
    {
        //检查是否是发送者
        if (!checkFromUserID(userId))
            break;

        //检查状态
        if (m_state != WaitingUpload && m_state != Uploading)
            break;

        //检查偏移是否有效
        if (offest != m_transfered_index * SEGMENT_SIZE)
            break;

        size = getNextSegmentBlockSize();

        if (m_state == WaitingUpload)
        {
            if (m_fp == nullptr)
            {
                m_fp = openByWrite(m_task_id, userId);
                if (!m_fp)
                    break;
            }

            //写文件头
            OfflineFileHeader fileHeader;
            memset(&fileHeader, 0, sizeof(fileHeader));
            fileHeader.setCreateTime(time(nullptr));
            fileHeader.setTaskId(m_task_id);
            fileHeader.setFromUserID(m_from_user_id);
            fileHeader.setToUserID(m_to_user_id);
            fileHeader.setFileName("");
            fileHeader.setFileSize(m_file_size);
            fwrite(&fileHeader, 1, sizeof(fileHeader), m_fp);
            fflush(m_fp);
            m_state = Uploading;
        }

        if (m_fp == nullptr)
            break;

        fwrite(data, 1, size, m_fp);
        fflush(m_fp);

        ++m_transfered_index;
        setLastUpdateTime();
        if (m_transfered_index == m_segment_size)
        {
            m_state = UploadEnd;
            fclose(m_fp);
            m_fp = nullptr;
            rv = 1;
        } else
            rv= 0;

    }while (0);
    return  rv;
}

int OfflineTransferTask::doPullFileRequest(uint32_t userId, uint32_t offest, uint32_t dataSize,
                                           std::string &data)
{
    int rv = -1;
    do
    {
        //1 检查状态， 必须为WaittingDownload 或者 Downloading
        if (m_state != WaitingDownload && m_state != Downloading)
            break;

        if (m_state == WaitingDownload)
        {
            if (m_transfered_index != 0)
                m_transfered_index = 0;

            if (m_fp != nullptr)
            {
                fclose(m_fp);
                m_fp = nullptr;
            }

            m_fp = openByRead(m_task_id, userId);
            if (m_fp == nullptr)
                break;

            OfflineFileHeader fileHeader;
            size_t size = fread(&fileHeader, 1, sizeof(fileHeader), m_fp);
            if (sizeof(fileHeader) != size)
            {
                log("读取文件头失败");
                fclose(m_fp);
                m_fp = nullptr;
                break;
            }

            m_state = Downloading;
        }
        else
        {
            if (m_fp == nullptr)
                break;

            //检查位移是否有效
            if (offest != m_transfered_index * SEGMENT_SIZE)
                break;

            dataSize = (uint32_t )getNextSegmentBlockSize();

            auto tmpBuf = new char[dataSize];
            if (tmpBuf == nullptr)
                break;

            memset(tmpBuf, 0, dataSize);

            size_t  size = fread(tmpBuf, 1, dataSize, m_fp);
            if (size != dataSize)
            {
                delete []tmpBuf;
                break;
            }

            &data.append(tmpBuf, size);


            delete []tmpBuf;

            ++m_transfered_index;

            setLastUpdateTime();
            if(m_transfered_index == m_segment_size)
            {
                m_state = DownloadEnd;
                fclose(m_fp);
                m_fp = nullptr;
                rv = 1;
            } else
                rv = 0;
        }

    }while (0);
    return  rv;
}