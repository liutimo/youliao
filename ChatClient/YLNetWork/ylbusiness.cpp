#include "ylbusiness.h"
#include "base/BasePdu.h"
#include "globaldata.h"
#include "pdusender.h"

#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.login.pb.h"
#include "protobuf/youliao.friendlist.pb.h"
#include "protobuf/youliao.message.pb.h"
#include "protobuf/youliao.session.pb.h"
#include "protobuf/youliao.group.pb.h"
#include "YLDataBase/yldatabase.h"

#include <QDateTime>
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

//    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::sendMessage(uint32_t senderId, uint32_t receiverId, const QString &message)
{
    message::MessageData messageData;
    messageData.set_from_user_id(senderId);
    messageData.set_to_user_id(receiverId);
    messageData.set_msg_id(GlobalData::getLatestMsgId(receiverId));
    messageData.set_create_time(QDateTime::currentDateTime().toTime_t());
    messageData.set_message_type(base::MESSAGE_TYPE_SINGLE_TEXT);
    messageData.set_message_data(message.toStdString());
    YLDataBase::instance()->saveMessage(messageData, true);
    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_MESSAGE);
    basePdu->setCID(CID_MESSAGE_DATA);
    basePdu->writeMessage(&messageData);

    PduSender::instance()->addMessage(basePdu);

    GlobalData::setLatestMsgId(receiverId, messageData.msg_id() + 1);
}

void YLBusiness::getLatestMsgId(uint32_t friendId)
{
    message::LatestMsgIdRequest request;
    request.set_user_id(GlobalData::getCurrLoginUserId());
    request.set_friend_id(friendId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_MESSAGE);
    basePdu->setCID(CID_MESSAGE_GET_LATEST_MSG_ID_REQUEST);
    basePdu->writeMessage(&request);

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

void YLBusiness::searchFriend(uint32_t userId, const QString& searchData, youliao::pdu::base::SearchType searchType)
{
    friendlist::SearchFriendRequest request;
    request.set_user_id(userId);
    request.set_search_data(searchData.toStdString().c_str());
    request.set_search_type(searchType);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_SEARCH_FRIEND_REQUEST);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::addFriend(uint32_t friendId, const QString &validateData, const QString remark, uint32_t groupId)
{
    friendlist::AddFriendRequest request;
    request.set_user_id(GlobalData::getCurrLoginUserId());
    request.set_user_head_url(GlobalData::getCurrLoginUserHeadUrl().toStdString());
    request.set_user_nick(GlobalData::getCurrLoginUserNick().toStdString());
    request.set_friend_id(friendId);
    request.set_validatedata(validateData.toStdString());
    request.set_friend_remark(remark.toStdString());
    request.set_group_id(groupId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_ADD_FRIEND_REQUEST);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::addFriendRespone(uint32_t friendId, uint32_t result, uint32_t groupId, const QString &remark)
{
    friendlist::AddFriendRespone respone;
    respone.set_user_id(GlobalData::getCurrLoginUserId());
    respone.set_friend_id(friendId);
    respone.set_result_id(result);
    respone.set_group_id(groupId);
    respone.set_remark(remark.toStdString());

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_ADD_FRIEND_RESPONE);
    basePdu->writeMessage(&respone);
    PduSender::instance()->addMessage(basePdu);
}

/******************SESSION*********************/
void YLBusiness::getSessions(uint32_t userId)
{
    session::GetSessionsRequest request;
    request.set_userid(userId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_SESSION);
    basePdu->setCID(CID_SESSIONLIST_GET_SESSIONS_REQUEST);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}


void YLBusiness::deleteSession(uint32_t userId, uint32_t sessionId)
{
    session::DeleteSessionRequest request;
    request.set_user_id(userId);
    request.set_session_id(sessionId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_SESSION);
    basePdu->setCID(CID_SESSIONLIST_DEL_SESSION);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::topSession(uint32_t userId, uint32_t sessionId)
{
    session::TopSessionRequest request;
    request.set_user_id(userId);
    request.set_session_id(sessionId);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_SESSION);
    basePdu->setCID(CID_SESSIONLIST_TOP_SESSION);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::getAllAddRequests()
{
    friendlist::GetAddRequestHistoryRequest request;
    request.set_user_id(GlobalData::getCurrLoginUserId());

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_FRIEND_LIST);
    basePdu->setCID(CID_FRIENDLIST_GET_REQUEST_HISTORY_REQUEST);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::createGroupRequest(const QString &groupName, uint32_t groupMaxMembers,
                               youliao::pdu::base::GroupVerifyType verifyType, const QVector<uint32_t> &members)
{
    group::GroupCreateRequest request;
    request.set_group_name(groupName.toStdString());
    request.set_group_type(base::GROUP_TYPE_NORMAL);
    request.set_user_id(GlobalData::getCurrLoginUserId());
    request.set_group_verify_type(verifyType);
    request.set_group_max_members(groupMaxMembers);

    for (uint32_t id : members)
    {
        request.add_member_ids(id);
    }


    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_GROUP);
    basePdu->setCID(CID_GROUP_CREATE_REQUEST);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::getGroupList()
{
    group::GetGroupListRequest request;
    request.set_user_id(GlobalData::getCurrLoginUserId());


    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_GROUP);
    basePdu->setCID(CID_GROUP_GET_LIST_REQUEST);
    basePdu->writeMessage(&request);
    PduSender::instance()->addMessage(basePdu);
}
