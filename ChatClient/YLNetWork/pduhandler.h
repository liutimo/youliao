#ifndef PDUHANDLER_H
#define PDUHANDLER_H
#include <QThread>
#include "base/BasePdu.h"
#include "protobuf/youliao.base.pb.h"
#include "YLEntityObject/ylfriend.h"
#include "YLEntityObject/ylgroup.h"
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
    void friendlist(const friend_map &);
    void friendStatusChange(uint32_t friend_id, uint32_t status);
    void friendSignatureChange(uint32_t friend_id, const QString &signature);
    void signleMessage(uint32_t senderId, const QString &content);
    void friendgroups(const group_map&);
    void friendGroup(uint32_t group_id, const QString &group_name);
    void sessions(const QList<base::SessionInfo>&);
    void newSession(uint32_t otherId, uint32_t sessionId);
    void searchResult(const QVector<YLFriend> friends);
    void unReadMessage(uint32_t friendId, const QString &message);
    void newAddRequest();
    void receiveNewMsg(uint32_t msgType, uint32_t fromId = 0);
    void newGroup(YLGroup group);
    void groupList();
    void groupMembers();
    void searchGroupResult(const QVector<YLGroup> friends);

private:
    void _HandleBasePdu(BasePdu *pdu);
    void _HandleUserLoginRespone(BasePdu *pdu);
    void _HandleHeartBeat();
    void _HandleFriendGroupGetRespone(BasePdu *pdu);
    void _HandleFriendListGetRespone(BasePdu *pdu);
    void _HandleMessageData(BasePdu *pdu);
    void _HandleFriendStatusChangeMessage(BasePdu *pdu);
    void _HandleFriendSignatureChanged(BasePdu *pdu);
    void _HandleAddFriendGroupRespone(BasePdu *pdu);
    void _HandleGetSessionsRespone(BasePdu *pdu);
    void _HandleAddSessionRespone(BasePdu *pdu);
    void _HandleSearchFriendRespone(BasePdu *pdu);
    void _HandleGetLatestMsgIdRespone(BasePdu *pdu);
    void _HandleAddFriendRequest(BasePdu *pdu);
    void _HandleGetAddRequestHistoryRespone(BasePdu *pdu);
    void _HandleCreatGroupRespone(BasePdu *pdu);
    void _HandleGetGroupListRespone(BasePdu *pdu);
    void _HandleGetGroupMemberRespone(BasePdu *pdu);
    void _HandleSearchGroupRespone(BasePdu *pdu);
    void _HandleAddGroupRespone(BasePdu *pdu);
    void _HandleVerifyNotify(BasePdu *pdu);
private:
    explicit PduHandler(QObject *parent = nullptr);

    static PduHandler *m_pdu_handler;
};

#endif // PDUHANDLER_H
