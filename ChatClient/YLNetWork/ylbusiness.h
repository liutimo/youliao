#ifndef YLBUSINESS_H
#define YLBUSINESS_H

#include <QObject>
#include <protobuf/youliao.base.pb.h>

using namespace youliao::pdu::base;

class YLBusiness : public QObject
{
    Q_OBJECT
public:
    explicit YLBusiness(QObject *parent = nullptr);
    static void heartBeat();
    static void login(const QString &account, const QString &password, UserStatusType type = USER_STATUS_ONLINE);

    //friendlist
    static void getFriendGroupsRequest(uint32_t userId);
    static void getFriendListRequest(uint32_t userId);
    static void loginOut(const uint32_t user_id);
    static void modifySignature(uint32_t userId, const QString &signature);
    static void addNewFriendGroup(uint32_t userId, const QString &groupName);
    static void renameFriendGroup(uint32_t userId, uint32_t groupId, const QString &groupNewName);
    static void deleteFriendGroup(uint32_t userId, uint32_t groupId);
    static void moveFriendToGroup(uint32_t userId, uint32_t friendId, uint32_t groupId);
    static void deleteFriend(uint32_t userId, uint32_t friendId);
    static void modifyFriendRemark(uint32_t userId, uint32_t friendId, const QString &friendRemark);
    static void searchFriend(uint32_t userId, const QString& searchData, youliao::pdu::base::SearchType searchType);
    static void addFriend(uint32_t friendId, const QString &validateData, const QString remark, uint32_t groupId);
    static void addFriendRespone(uint32_t friendId, uint32_t result, uint32_t groupId = 0, const QString &remark = QString());
    static void getAllAddRequests();
    
    //message
    static void sendMessage(uint32_t senderId, uint32_t receiverId, const QString &message);
    static void getLatestMsgId(uint32_t friendId);


    //session
    static void getSessions(uint32_t userId);
    static void deleteSession(uint32_t userId, uint32_t sessionId);
    static void topSession(uint32_t userId, uint32_t sessionId);

    //group
    static void createGroupRequest(const QString &groupName, uint32_t groupMaxMembers, youliao::pdu::base::GroupVerifyType verifyType, const QVector<uint32_t> &members);
    static void getGroupList();
    static void getGroupMembersInfo(uint32_t groupId);
    static void modifyGroupCard(uint32_t groupId, const QString &card);
    static void searchGroup(const QString &searchData, youliao::pdu::base::SearchType searchType);
    static void addGroup(uint32_t groupId);
};

#endif // YLBUSINESS_H
