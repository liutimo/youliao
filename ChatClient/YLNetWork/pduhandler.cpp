#include "pduhandler.h"
#include <list>
#include <iostream>

#include <QMap>
#include <QVector>
#include <QDebug>
#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.login.pb.h"
#include "protobuf/youliao.friendlist.pb.h"
#include "protobuf/youliao.message.pb.h"
#include "protobuf/youliao.session.pb.h"
//全局PDU list
//主线程产生的所有pdu都会放入这个list中
//子线程循环冲list读数据发送到消息服务器
//如果list为空,则子线程休眠
std::list<BasePdu*> g_pdu_list;
Condition           g_condition;

PduHandler* PduHandler::m_pdu_handler = nullptr;

uint32_t PduHandler::m_heartbeat_received_times = 0;

PduHandler::PduHandler(QObject *parent) : QThread(parent)
{
    qRegisterMetaType<group_map>("group_map");
    qRegisterMetaType<friend_map>("friend_map");
    qRegisterMetaType<uint32_t>("uint32_t");
    qRegisterMetaType<QList<base::SessionInfo>>("QList<base::SessionInfo>");
}

PduHandler* PduHandler::instance()
{
    if (m_pdu_handler == nullptr)
    {
        m_pdu_handler = new PduHandler;
        m_pdu_handler->start();
    }

    return m_pdu_handler;
}

void PduHandler::run()
{
    for(;;)
    {
        g_condition.lock();

        if (g_pdu_list.empty())
            g_condition.wait();

        BasePdu *basePdu = g_pdu_list.front();
        g_pdu_list.pop_front();
        g_condition.unlock();

        _HandleBasePdu(basePdu);
        delete basePdu;
    }
}

void PduHandler::_HandleBasePdu(BasePdu *pdu)
{
    switch (pdu->getCID()) {
    case base::CID_LOGIN_RESPONE_USERLOGIN:
        _HandleUserLoginRespone(pdu);
        break;
    case base::CID_OTHER_HEARTBEAT:
        _HandleHeartBeat();
        break;
    case base::CID_FRIENDLIST_GET_GROUPS_REPSONE:
        _HandleFriendGroupGetRespone(pdu);
        break;
    case base::CID_FRIENDLIST_GET_RESPONE:
        _HandleFriendListGetRespone(pdu);
        break;
    case base::CID_MESSAGE_DATA:
        _HandleMessageData(pdu);
        break;
    case base::CID_FRIENDLIST_FRIEND_STATUS_CHANGE:
        _HandleFriendStatusChangeMessage(pdu);
        break;
    case base::CID_FRIENDLIST_FRIEND_SIGNATURE_CHANGED:
        _HandleFriendSignatureChanged(pdu);
        break;
    case base::CID_FRIENDLIST_ADD_FRIEND_GROUP_RESPONE:
        _HandleAddFriendGroupRespone(pdu);
        break;
    case base::CID_SESSIONLIST_GET_SESSIONS_RESPONE:
        _HandleGetSessionsRespone(pdu);
        break;
    case base::CID_SESSIONLIST_ADD_SESSION:
        _HandleAddSessionRespone(pdu);
        break;
    default:
        std::cout << "CID" << pdu->getCID() << "  SID:" << pdu->getSID();
        break;
    }
}

void PduHandler::_HandleUserLoginRespone(BasePdu *pdu)
{
    login::UserLoginRespone respone;
    respone.ParseFromString(pdu->getMessage());
    if (respone.result_code() == base::NONE)
    {
        base::UserInfo *userInfo = new base::UserInfo(respone.user_info());
        emit loginStatus(true, userInfo);
    }
    else
        emit loginStatus(false);
}

void PduHandler::_HandleHeartBeat()
{
    ++m_heartbeat_received_times;
}

void PduHandler::_HandleFriendGroupGetRespone(BasePdu *pdu)
{
    friendlist::GroupsRespone groupsRespone;
    groupsRespone.ParseFromString(pdu->getMessage());

    group_map groupsMap;

    auto groups = groupsRespone.user_groups();
    for (auto elem : groups)
    {
        groupsMap[elem.first] = QString(elem.second.c_str());
    }

    emit friendgroups(groupsMap);
}

void PduHandler::_HandleFriendListGetRespone(BasePdu *pdu)
{
    friendlist::FriendListRespone friendlistRespone;
    friendlistRespone.ParseFromString(pdu->getMessage());

    friend_map friends;
    auto friendList = friendlistRespone.friend_list();
    for (auto elem : friendList)
    {
        auto c = elem.second;
        int groupId = elem.first;
        for (int i = 0; i < c.friend__size(); ++i)
        {
            auto fri = c.friend_(i);
            YLFriend ylFriend;
            ylFriend.setFriendId(fri.friend_id());
            ylFriend.setFriendAccount(QString::number(fri.friend_account()));
            ylFriend.setFriendImagePath(fri.friend_header_url().c_str());
            ylFriend.setFriendNickName(fri.friend_nick().c_str());
            ylFriend.setFriendSigature(fri.friend_sign_info().c_str());
            ylFriend.setFriendOnline(fri.friend_is_online());
            ylFriend.setFriendRemark(fri.friend_remark().c_str());
            friends[groupId].push_back(ylFriend);
        }
    }

    emit friendlist(friends);
}

void PduHandler::_HandleMessageData(BasePdu *pdu)
{
    message::MessageData messageData;
    messageData.ParseFromString(pdu->getMessage());

    emit signleMessage(messageData.from_user_id(), QString(messageData.message_data().c_str()));
}


void PduHandler::_HandleFriendStatusChangeMessage(BasePdu *pdu)
{
    friendlist::FriendStatusChangeMessage friendStatusChangeMessage;
    friendStatusChangeMessage.ParseFromString(pdu->getMessage());

    uint32_t changedUserId = friendStatusChangeMessage.user_id();
    uint32_t status = friendStatusChangeMessage.user_status_type();

    emit friendStatusChange(changedUserId, status);
}

void PduHandler::_HandleFriendSignatureChanged(BasePdu *pdu)
{
    friendlist::FriendSignatureChangedNotify friendSignatureChangedNotify;
    friendSignatureChangedNotify.ParseFromString(pdu->getMessage());

    uint32_t friendId = friendSignatureChangedNotify.friend_id();
    std::string  signature = friendSignatureChangedNotify.friend_signatrue();

    emit friendSignatureChange(friendId, QString(signature.c_str()));
}


void PduHandler::_HandleAddFriendGroupRespone(BasePdu *pdu)
{
    friendlist::AddNewFriendGroupRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t groupId = respone.group_id();
    QString groupName = QString(respone.group_name().c_str());

    emit friendGroup(groupId, groupName);
}


void PduHandler::_HandleGetSessionsRespone(BasePdu *pdu)
{
    session::GetSessionReponse respone;
    respone.ParseFromString(pdu->getMessage());

    QList<base::SessionInfo> sessionList;

    for(int i = 0; i < respone.sessions_size(); ++i)
    {
        base::SessionInfo si;
        si = respone.sessions(i);
        sessionList.push_back(si);
    }

    emit sessions(sessionList);
}


void PduHandler::_HandleAddSessionRespone(BasePdu *pdu)
{
    session::NewSessionRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t otherId = respone.other_id();
    uint32_t sessionId = respone.session_id();

    emit newSession(otherId, sessionId);
}
