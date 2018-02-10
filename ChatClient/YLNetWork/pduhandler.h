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
signals:
    void loginStatus(bool successed, base::UserInfo *userInfo = nullptr);
private:
    explicit PduHandler(QObject *parent = nullptr);
    void _HandleBasePdu(BasePdu *pdu);

    static PduHandler *m_pdu_handler;
};

#endif // PDUHANDLER_H
