#include "ylfiletransfermanager.h"
#include "yltransferfile.h"
#include "ylfiletransferthread.h"

YLTransferFileEntity::YLTransferFileEntity()
: m_file_size(0)
, m_client_role(0)
, m_progress(0)
, m_file_object(nullptr)
{
    m_save_path = "";
}


YLTransferFileEntity& YLTransferFileEntity::operator=(const YLTransferFileEntity& entity)
{
    m_port          = entity.m_port;
    m_file_size     = entity.m_file_size;
    m_client_role   = entity.m_client_role;			//CLIENT_REALTIME_SENDER = 1,CLIENT_REALTIME_RECVER,CLIENT_OFFLINE_UPLOAD,CLIENT_OFFLINE_DOWNLOAD
    m_progress      = entity.m_progress;
    m_file_object   = entity.m_file_object;
    m_from_id       = entity.m_from_id;
    m_task_id       = entity.m_task_id;
    m_to_id         = entity.m_to_id;
    m_file_name     = entity.m_file_name;
    m_ip            = entity.m_ip;
    m_time          = entity.m_time;
    m_save_path     = entity.m_save_path;
    m_path_offline_file_on_sever = entity.m_path_offline_file_on_sever;
    return *this;
}

std::string YLTransferFileEntity::getSaveFilePath()//完整的保存文件路径
{
    if (m_save_path.empty())
    {
        return "/home/liuzheng/Documents/youliao/FileRecv";
    }
    else
        return m_save_path;
}
std::string YLTransferFileEntity::getSaveFloderFilePath()//保存的文件夹位置
{
    std::string strFloderPath = "";

    return strFloderPath;
}
void YLTransferFileEntity::setSaveFilePath(const std::string& sPath)
{
    m_save_path = sPath;
}

std::string YLTransferFileEntity::getRealFileName()
{
    int pos = m_file_name.find_last_of('/');

    std::string strName = m_file_name.substr(pos + 1);

    return strName;
}

/////////////////////////////

YLTransferFileEntityManager::YLTransferFileEntityManager()
:m_file_transfer_thread(0)
{
    startup();
}

YLTransferFileEntityManager::~YLTransferFileEntityManager()
{

}

YLTransferFileEntityManager* YLTransferFileEntityManager::instance()
{
    static YLTransferFileEntityManager manager;
    return &manager;
}

bool YLTransferFileEntityManager::getFileInfoByTaskId(const std::string& taskId, YLTransferFileEntity& entity)
{
    AutoLock lock(m_lock);
    auto iter = m_file_map.find(taskId);
    if (iter != m_file_map.end())
    {
        entity = iter->second;
        return true;
    }
    return false;
}
bool YLTransferFileEntityManager::deleteFileInfoByTaskId(const std::string& taskId)
{
    AutoLock lock(m_lock);

    return false;
}
bool YLTransferFileEntityManager::kickMapFileItemToVecFile(std::string& sfId)
{
    AutoLock lock(m_lock);

    return false;
}



bool YLTransferFileEntityManager::openFileByFileID(const std::string& taskId)
{
    std::vector<YLTransferFileEntity>::iterator it = m_VecFinishedFile.begin();//已经传输完的文件,任何操作过的文件都会被扔到这里


    return false;
}

bool YLTransferFileEntityManager::openFileFolderByTaskID(const std::string& taskId)//打开文件夹，并同时选中指定文件
{

    return false;
}

bool YLTransferFileEntityManager::checkIfIsSending(std::string sFilePath)
{

    AutoLock lock(m_lock);

    return false;
}

bool YLTransferFileEntityManager::pushYLTransferFileEntity(YLTransferFileEntity& entity)
{
    AutoLock lock(m_lock);

    auto iter = m_file_map.find(entity.m_task_id);
    if (iter != m_file_map.end())
        return false;
    m_file_map.insert(std::make_pair(entity.m_task_id, entity));
    return true;
}

bool YLTransferFileEntityManager::updateFileInfoBysTaskID(const YLTransferFileEntity& entity)
{
    AutoLock lock(m_lock);

    auto iter = m_file_map.find(entity.m_task_id);

    if (iter != m_file_map.end())
    {
        iter->second = entity;
        return true;
    }

    return false;
}


void YLTransferFileEntityManager::getAllYLTransferFileEntityFileID(std::list<std::string>& fileIdList)
{
    for (auto item : m_file_map)
    {
        fileIdList.push_back(item.first);
    }
}


bool YLTransferFileEntityManager::startup()
{
    m_file_transfer_thread = new YLFileTransferThread;
    if (!m_file_transfer_thread)
        return false;
    return true;
}

void YLTransferFileEntityManager::shutdown()
{
    if (m_file_transfer_thread)
        m_file_transfer_thread->shutDown();

    delete m_file_transfer_thread;
    m_file_transfer_thread = nullptr;

    for (YLTransferFileEntity &entity : m_VecFinishedFile)
    {
        delete entity.m_file_object;
        entity.m_file_object = nullptr;
    }
    m_VecFinishedFile.clear();

    for (auto &kv : m_file_map)
    {
        auto &entity = kv.second;
        delete entity.m_file_object;
        entity.m_file_object = nullptr;
    }
    m_file_map.clear();
}

void YLTransferFileEntityManager::openFileSocketByTaskId(std::string& taskId)
{
    m_file_transfer_thread->openFileSocketByTaskId(taskId);
}

bool YLTransferFileEntityManager::acceptFileTransfer(const std::string& taskId)
{
    return m_file_transfer_thread->acceptFileTransfer(taskId);
}

bool YLTransferFileEntityManager::rejectFileTransfer(const std::string& taskId)
{
    return m_file_transfer_thread->rejectFileTransfer(taskId);
}

YLFileTransferThread* YLTransferFileEntityManager::getFileTransferThread()
{
    return m_file_transfer_thread;
}

bool YLTransferFileEntityManager::cancelFileTransfer(const std::string& taskId)
{
    return m_file_transfer_thread->cancelFileTransfer(taskId);
}

void YLTransferFileEntityManager::closeFileSocketByTaskId(std::string& taskId)
{
    m_file_transfer_thread->closeFileSocketByTaskId(taskId);
}

void YLTransferFileEntityManager::pushYLTransferFileEntityToVec(YLTransferFileEntity& entity)
{
    AutoLock lock(m_lock);
    m_VecFinishedFile.push_back(entity);
}

