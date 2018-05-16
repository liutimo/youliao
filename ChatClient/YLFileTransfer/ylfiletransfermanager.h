#ifndef YLFILETRANSFERMANAGER_H
#define YLFILETRANSFERMANAGER_H

#include <list>
#include <map>
#include <vector>
#include "YLNetWork/base/Lock.h"
using namespace youliao::thread;
class YLTransferFile;
class YLFileTransferThread;

class YLTransferFileEntity
{
public:
   YLTransferFileEntity();
   YLTransferFileEntity& operator=(const YLTransferFileEntity& entity);
public:
   uint32_t             m_port;
   uint32_t				m_file_size;
   uint32_t				m_client_role;			//CLIENT_REALTIME_SENDER = 1,CLIENT_REALTIME_RECVER,CLIENT_OFFLINE_UPLOAD,CLIENT_OFFLINE_DOWNLOAD
   uint32_t				m_progress;
   uint32_t      		m_from_id;
   uint32_t             m_to_id;
   YLTransferFile*		m_file_object;
   std::string          m_task_id;
   std::string          m_file_name;
   std::string			m_ip;
   std::string          m_path_offline_file_on_sever;

   uint32_t		        m_time;
private:
   std::string          m_save_path;

public:
   std::string getSaveFilePath();
   std::string getSaveFloderFilePath();
   void setSaveFilePath(const std::string& sPath);

   std::string getRealFileName();
};

typedef std::map<std::string, YLTransferFileEntity>     TransferFileMap;

class YLTransferFileEntityManager
{
public:
   ~YLTransferFileEntityManager();
   static YLTransferFileEntityManager* instance();
   bool pushYLTransferFileEntity(YLTransferFileEntity& FileInfo);
   bool getFileInfoByTaskId(const std::string& sID, YLTransferFileEntity& FileInfo);
   bool deleteFileInfoByTaskId(const std::string& sID);
   void getAllYLTransferFileEntityFileID(std::list<std::string>& fileIdList);
   bool updateFileInfoBysTaskID(const YLTransferFileEntity& info);
   bool openFileByFileID(const std::string& sID);
   bool openFileFolderByTaskID(const std::string& sID);
   bool kickMapFileItemToVecFile(std::string& sfId);
   void pushYLTransferFileEntityToVec(YLTransferFileEntity& FileInfo);
   bool checkIfIsSending(std::string sFilePath);

public:
   bool startup();
   void shutdown();

   void openFileSocketByTaskId(std::string& taskId);

   void closeFileSocketByTaskId(std::string& taskId);

   bool acceptFileTransfer(const std::string& taskId);
   bool rejectFileTransfer(const std::string& taskId);
   bool cancelFileTransfer(const std::string& taskId);
   YLFileTransferThread* getFileTransferThread();


private:
   YLTransferFileEntityManager();

private:
   Mutex                                m_lock;
   TransferFileMap						m_file_map;
   std::vector<YLTransferFileEntity>	m_VecFinishedFile;
   YLFileTransferThread*				m_file_transfer_thread;
};
#endif // YLFILETRANSFERMANAGER_H
