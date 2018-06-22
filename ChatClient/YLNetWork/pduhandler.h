#ifndef PDUHANDLER_H
#define PDUHANDLER_H
#include <QThread>
#include "base/BasePdu.h"
#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.file.pb.h"
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
    void sessions();
    void newSession();
    void searchResult(const QVector<YLFriend> friends);
    void unReadMessage(uint32_t friendId, const QString &message, uint32_t type);
    void newAddRequest();
    void receiveNewMsg(uint32_t friendId, const QString &message, uint32_t time, uint32_t type);
    void newGroup(YLGroup group);
    void groupList();
    void groupMembers();
    void searchGroupResult(const QVector<YLGroup> friends);
    void regiserStatus(uint32_t resultCode, QString account);
    void userHeaderIconChanged();
    void exitGroupResult(uint32_t groupId, uint32_t resultCode);
    void modifyGroupHeader(uint32_t groupId, const QString &url);
    void deleteFriend(uint32_t friendId);
    void friendInformation(const base::UserInfo &);
    void addFriendSuccess();
    void offlineFiles(file::GetOfflineFileRespone);
    void updateMemberList(uint32_t groupId);

private:
    void _HandleBasePdu(BasePdu *pdu);
    void _HandleUserLoginRespone(BasePdu *pdu);
    void _HandleRegisterRespone(BasePdu *pdu);
    void _HandleHeartBeat();
    void _HandleFriendGroupGetRespone(BasePdu *pdu);
    void _HandleFriendListGetRespone(BasePdu *pdu);
    void _HandleMessageData(BasePdu *pdu);
    void _HandleOfflineMessageData(BasePdu *pdu);
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
    void _handleSendFileRespone(BasePdu *pdu);
    void _HandleFileNotify(BasePdu *pdu);
    void _HandleModifyUserIconRespone(BasePdu *pdu);

    //group
    void _HandleGetLatestGroupMsgIdRespone(BasePdu *pdu);
    void _HandleExitGroupRespone(BasePdu *pdu);
    void _HandleModifyGroupIconRespone(BasePdu *pdu);
    void _HandleSetGroupManagerRespone(BasePdu *pdu);
    void _HandleKickOutGroupMemberRespone(BasePdu *pdu);
    void _HandleGroupAddRequestHandleRespone(BasePdu *pdu);
    void _HandleUpdateGroupListRespone(BasePdu *pdu);
    void _HandleGroupOfflineMessageRespone(BasePdu *pdu);
    void _HandleUngroupNotify(BasePdu *pdu);

    //验证信息
    //[1]群组验证
    void _HandleGroupVerifyNotify(BasePdu *pdu);

    //好友列表
    void _HandleDeleteFriendRespone(BasePdu *pdu);
    void _HandleAddFriendRespone(BasePdu *pdu);

    //好友信息
    void _HandleFriendInfomation(BasePdu *pdu);

    //好友信息更改
    void _HandleUserInformationChange(BasePdu *pdu);

    //个性签名修改通知
    void _HandleUserSignalChangeRespone(BasePdu *pdu);

    void _HandleGetOfflineFileRespone(BasePdu *pdu);
private:
    explicit PduHandler(QObject *parent = nullptr);

    static PduHandler *m_pdu_handler;
};

#endif // PDUHANDLER_H
