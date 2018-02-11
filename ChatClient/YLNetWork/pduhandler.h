#ifndef PDUHANDLER_H
#define PDUHANDLER_H
#include <QThread>
#include "BasePdu.h"
#include "protobuf/youliao.base.pb.h"
using namespace youliao::pdu;

class PduHandler : public QThread
{
    Q_OBJECT
public:
    void run() override;
    static PduHandler* instance();
    static uint32_t m_heartbeat_received_times = 0;
signals:
    void loginStatus(bool successed, base::UserInfo *userInfo = nullptr);

private:
    void _HandleBasePdu(BasePdu *pdu);
    void _HandleUserLoginRespone(BasePdu *pdu);
    void _HandleHeartBeat();

private:
    explicit PduHandler(QObject *parent = nullptr);

    static PduHandler *m_pdu_handler;
};

#endif // PDUHANDLER_H
