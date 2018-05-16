#ifndef YLFILETRANSFERCONN_H
#define YLFILETRANSFERCONN_H

#include "../base/BaseConn.h"
#include "../base/BasePdu.h"
#include <list>
using namespace youliao::pdu;
using namespace youliao::network;

class YLFileTransferConn : public BaseConn
{
public:
    explicit YLFileTransferConn(std::string &taskId);

public:
    bool startFileTransfer();
    void stopFileTransfer();

private:
    void connect(const std::string &server_ip, uint16_t port);
    void handlePdu(BasePdu*) override;
    virtual void onConfirm() override;

    void shutdown();
    //心跳包
    void startHeartBeat();
    void stopHeartBeat();

    void onClose();
    //在BaseConn中, handlePdu后,pdu被delete.
    //但是在这个类中,pdu会被放入静态链表中.pdu需要在其余地方释放
    void onRead() override;

private:
    //解析数据

public:
    std::string     m_task_id;

private:
    uint32_t        m_progress;
};

YLFileTransferConn *findFileTransferConnByHandle(int handle);

extern std::list<std::pair<int, BasePdu*>> g_file_pdu_list;
extern Condition           g_file_condition;

#endif // YLFILETRANSFERCONN_H
