#ifndef YLFILETRANSFERRECEIVER_H
#define YLFILETRANSFERRECEIVER_H

#include <QThread>
#include "YLNetWork/base/BasePdu.h"
using namespace youliao::pdu;

class YLFileTransferReceiver : public QThread
{
    Q_OBJECT
public:
    void run() override;
    static YLFileTransferReceiver* instance();
signals:
    void addSendFileItem(uint32_t userId, const QString &taskId);        //添加发送文件的item
    void addRecvFileItem(uint32_t userId, const QString &taskId);        //添加接收文件的item
    void updateProgressBar(uint32_t userId, const QString &taskId ,uint32_t currentProgress);
    void transferComplete(uint32_t userId, const QString &taskId);

private:
    static YLFileTransferReceiver *m_instance;
    YLFileTransferReceiver(QObject *parent = nullptr);
    void _HandleBasePdu(BasePdu *pdu);


    void _HandleLoginFileServerRespone(BasePdu*);
    void _HandleFileState(BasePdu*);
    void _HandleGetFileBlockRequest(BasePdu *);
    void _HandleGetFileBlockRespone(BasePdu *);

    int m_current_handle;
};

#endif // YLFILETRANSFERRECEIVER_H
