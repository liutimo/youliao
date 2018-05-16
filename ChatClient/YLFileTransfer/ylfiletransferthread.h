#ifndef YLFILETRANSFERTHREAD_H
#define YLFILETRANSFERTHREAD_H

#include "YLNetWork/base/Thread.h"
#include "YLNetWork/base/Lock.h"
#include "YLNetWork/login/ylfiletransferconn.h"
#include <list>
#include <map>
using namespace youliao::thread;

class YLFileTransferThread : public Thread
{
public:
    YLFileTransferThread();

    virtual ~YLFileTransferThread();

    virtual void run();

public:
    void shutDown();
    void openFileSocketByTaskId(std::string &taskId);

    void closeFileSocketByTaskId(std::string &taskId);

    bool acceptFileTransfer(const std::string& taskId);
    bool rejectFileTransfer(const std::string& taskId);
    bool cancelFileTransfer(const std::string& taskId);

private:
    void closeAllFileSockets();
    YLFileTransferConn* findFileTransferConnByTaskId(const std::string &taskId);

public:
    std::map<std::string, YLFileTransferConn*> m_file_transfer_conn_map;
    Mutex       m_mutex;

};

#endif // YLFILETRANSFERTHREAD_H
