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


void  YLBusiness::loginOut(const uint32_t user_id)
{
    login::UserLoginOutRequest request;
    request.set_user_id(user_id);

    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(SID_LOGIN);
    basePdu->setCID(CID_LOGIN_REQUEST_USERLOGINOUT);
    basePdu->writeMessage(&request);

    PduSender::instance()->addMessage(basePdu);
}

void YLBusiness::getFriendListRequest(uint32_t user_id)
{
    friendlist::FriendListRequest request;
    request.set_user_id(user_id);

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
