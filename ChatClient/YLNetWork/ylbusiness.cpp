#include "ylbusiness.h"
#include "base/BasePdu.h"
#include "pdusender.h"

#include "protobuf/youliao.login.pb.h"
#include "protobuf/youliao.friendlist.pb.h"

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
