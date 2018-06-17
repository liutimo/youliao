#ifndef YLBUSINESS_H
#define YLBUSINESS_H

#include <QObject>
#include <protobuf/youliao.base.pb.h>
#include "protobuf/youliao.other.pb.h"

using namespace youliao::pdu::base;

class YLBusiness : public QObject
{
    Q_OBJECT
public:
    explicit YLBusiness(QObject *parent = nullptr);
    static void heartBeat();
    static void login(const QString &account, const QString &password, UserStatusType type = USER_STATUS_ONLINE);
    static void registerAccount(const QString &nickName, const QString &password, const QString &header);

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
    static void sendAudioMessage(uint32_t senderId, uint32_t receiverId, const QString &filename, uint32_t time);
    static void getLatestMsgId(uint32_t friendId);
    static void sendGroupTextMessage(uint32_t groupId, uint32_t userId, const QString &message);
    static void sendMessageAck(uint32_t senderId, uint32_t receiverId, uint32_t msg_id);
    static void getOfflineMessage();

    //session
    static void getSessions(uint32_t userId);
    static void deleteSession(uint32_t userId, uint32_t sessionId);
    static void topSession(uint32_t userId, uint32_t sessionId);
    static void createNewSession(uint32_t otherId, SessionType type);


    //group
    static void createGroupRequest(const QString &groupName, uint32_t groupMaxMembers, youliao::pdu::base::GroupVerifyType verifyType, const QVector<uint32_t> &members);
    static void getGroupList();
    static void getGroupMembersInfo(uint32_t groupId);
    static void modifyGroupCard(uint32_t groupId, const QString &card);
    static void searchGroup(const QString &searchData, youliao::pdu::base::SearchType searchType);
    static void addGroup(uint32_t groupId, const QString &verifyData = QString());
    static void getLatestGroupMsgId(uint32_t groupId);
    static void exitGroup(uint32_t groupId);
    static void modifyGroupHeader(uint32_t groupId, const QString &url);
    static void setGroupManager(uint32_t groupId, uint32_t memberId);
    static void kickOutGroupMember(uint32_t groupId, uint32_t memberId);


    //file
    static void sendFileRequest(uint32_t friId, const QString &fileName, uint32_t fileSize, bool isOnline);

    //other
    static void modifyInformation(const UserInfo &userInfo, bool flag);
    static void modifyUserIcon(const QString &url);
    static void getFriendInformation(uint32_t friendId);

    //群验证消息
    static void sendGroupVerifyResult(uint32_t groupId, uint32_t requestUserId, GroupVerifyResult result);
};

#endif // YLBUSINESS_H
