#include "ylbusiness.h"
#include "base/BasePdu.h"
#include "pdusender.h"

#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.login.pb.h"
#include "protobuf/youliao.friendlist.pb.h"
#include "protobuf/youliao.message.pb.h"
#include <time.h>
using namespace youliao::pdu;

YLBusiness::YLBusiness(QObject *parent) : QObject(parent)
{

}


void YLBusiness::login(const QString &account, const QString &password, UserStatusType type)
{
    login::UserLoginRequest request;
    request.set_user_name(account.toStdString());
    request.set_user_password(password.toStdString());
    request.set_user_status(type);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(base::SID_LOGIN);
    basePdu->setCID(base::CID_LOGIN_REQUEST_USERLOGIN);
    basePdu->writeMessage(&request);

    PduSender::instance()->addMessage(basePdu);
}


void  YLBusiness::loginOut(const uint32_t userId)
{
    login::UserLoginOutRequest request;
    request.set_user_id(userId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_LOGIN);
    basePdu->setCID(CID_LOGIN_REQUEST_USERLOGINOUT);
    basePdu->writeMessage(&request);

    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::getFriendGroupsRequest(uint32_t userId)
{
    friendlist::GroupsRequest groupRequest;
    groupRequest.set_user_id(userId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(base::SID_FRIEND_LIST);
    basePdu->setCID(base::CID_FRIENDLIST_GET_GROUPS_REQUEST);
    basePdu->writeMessage(&groupRequest);

    PduSender::instance()->addMessage(basePdu);
}


void YLBusiness::getFriendListRequest(uint32_t userId)
{
    friendlist::FriendListRequest request;
    request.set_user_id(userId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(base::SID_FRIEND_LIST);
    basePdu->setCID(base::CID_FRIENDLIST_GET_REQUEST);
    basePdu->writeMessage(&request);

    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::heartBeat()
{
    base::HeartBeat heartBeat;
    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_OTHER);
    basePdu->setCID(CID_OTHER_HEARTBEAT);
    basePdu->writeMessage(&heartBeat);

    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::sendMessage(uint32_t senderId, uint32_t receiverId, const QString &message)
{
    message::MessageData messageData;
    messageData.set_from_user_id(senderId);
    messageData.set_to_user_id(receiverId);
    messageData.set_create_time(time(NULL));
    messageData.set_message_type(base::MESSAGE_TYPE_SINGLE_TEXT);
    messageData.set_message_data(message.toStdString());

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_MESSAGE);
    basePdu->setCID(CID_MESSAGE_DATA);
    basePdu->writeMessage(&messageData);

    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::modifySignature(uint32_t userId, const QString &signature)
{
    friendlist::SignatureChangeResquest signatureChangeResquest;
    signatureChangeResquest.set_user_id(userId);
    signatureChangeResquest.set_user_signature(signature.toStdString());

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_SIGNATURE_CHANGED_REQUEST);
    basePdu->writeMessage(&signatureChangeResquest);

    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::addNewFriendGroup(uint32_t userId, const QString &groupName)
{
    friendlist::AddNewFriendGroupRequest request;
    request.set_user_id(userId);
    request.set_new_group_name(groupName.toStdString());

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_ADD_FRIEND_GROUP_REQUEST);
    basePdu->writeMessage(&request);

    PduSender::instance()->addMessage(basePdu);
}


void YLBusiness::renameFriendGroup(uint32_t userId, uint32_t groupId, const QString &groupNewName)
{
   friendlist::RenameFriendGroupRequest request;
   request.set_user_id(userId);
   request.set_group_id(groupId);
   request.set_group_new_name(groupNewName.toStdString());

   BasePdu *basePdu = new BasePdu;
   basePdu->setSID(SID_FRIEND_LIST);
   basePdu->setCID(CID_FRIENDLIST_RENAME_FRIEND_GROUP_REQUEST);
   basePdu->writeMessage(&request);

   PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::deleteFriendGroup(uint32_t userId, uint32_t groupId)
{
    friendlist::DeleteFriendGroupRequest request;
    request.set_user_id(userId);
    request.set_group_id(groupId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_DELETE_FRIEND_GROUP_REQUEST);
    basePdu->writeMessage(&request);

    PduSender::instance()->addMessage(basePdu);
}


void YLBusiness::moveFriendToGroup(uint32_t userId, uint32_t friendId, uint32_t groupId)
{
    friendlist::MoveFriendToGroupRequest request;
    request.set_user_id(userId);
    request.set_friend_id(friendId);
    request.set_group_id(groupId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_MOVE_FRIEND_TO_GROUP_REQUEST);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::deleteFriend(uint32_t userId, uint32_t friendId)
{
    friendlist::DeleteFriendRequest request;
    request.set_user_id(userId);
    request.set_friend_id(friendId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_DELETE_FRIEND_REQUEST);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}


void YLBusiness::modifyFriendRemark(uint32_t userId, uint32_t friendId, const QString &friendRemark)
{
    friendlist::ModifyFriendRemarkRequest request;
    request.set_user_id(userId);
    request.set_friend_id(friendId);
    request.set_friend_remark(friendRemark.toStdString());

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_MODIFY_FRIEND_REMARK_RQUEST);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}
