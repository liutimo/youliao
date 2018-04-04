#ifndef PDUHANDLER_H
#define PDUHANDLER_H
#include <QThread>
#include "base/BasePdu.h"
#include "protobuf/youliao.base.pb.h"
#include "YLEntityObject/ylfriend.h"
using namespace youliao::pdu;

typedef QMap<int, QVector<YLFriend>> friend_map;
typedef QMap<int, QString> group_map;
class PduHandler : public QThread
{
    Q_OBJECT
public:
    void run() override;
    static PduHandler* instance();
    static uint32_t m_heartbeat_received_times;

signals:
    void loginStatus(bool successed,  base::UserInfo *userInfo = nullptr);
    void friendlist(const friend_map &, const group_map&);
    void signleMessage(uint32_t senderId, const QString &content);

private:
    void _HandleBasePdu(BasePdu *pdu);
    void _HandleUserLoginRespone(BasePdu *pdu);
    void _HandleHeartBeat();
    void _HandleFriendListGetRespone(BasePdu *pdu);
    void _HandleMessageData(BasePdu *pdu);

private:
    explicit PduHandler(QObject *parent = nullptr);

    static PduHandler *m_pdu_handler;
};

#endif // PDUHANDLER_H
