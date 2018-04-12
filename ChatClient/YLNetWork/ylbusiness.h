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
    static void getFriendGroupsRequest(uint32_t userId);
    static void getFriendListRequest(uint32_t userId);
    static void loginOut(const uint32_t user_id);
    static void sendMessage(uint32_t senderId, uint32_t receiverId, const QString &message);
    static void modifySignature(uint32_t userId, const QString &signature);
    static void addNewFriendGroup(uint32_t userId, const QString &groupName);
    static void renameFriendGroup(uint32_t userId, uint32_t groupId, const QString &groupNewName);
    static void deleteFriendGroup(uint32_t userId, uint32_t groupId);
};

#endif // YLBUSINESS_H
