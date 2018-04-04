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
    case base::CID_FRIENDLIST_GET_RESPONE:
        _HandleFriendListGetRespone(pdu);
        break;
    case base::CID_MESSAGE_DATA:
        _HandleMessageData(pdu);
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


void PduHandler::_HandleFriendListGetRespone(BasePdu *pdu)
{
    friendlist::FriendListRespone friendlistRespone;
    friendlistRespone.ParseFromString(pdu->getMessage());

    friend_map friends;
    group_map  groups;

    auto friendList = friendlistRespone.friend_list();
    for (auto elem : friendList)
    {
        auto c = elem.second;
        int groupId = elem.first;
        QString groupName(c.group_name().c_str());
        groups[groupId] = groupName;
        for (int i = 0; i < c.friend__size(); ++i)
        {
            auto fri = c.friend_(i);
            YLFriend ylFriend;
            ylFriend.setFriendId(fri.user_id());
            ylFriend.setFriendAccount(QString::number(fri.user_account()));
            ylFriend.setFriendImagePath(fri.user_header_url().c_str());
            ylFriend.setFriendNickName(fri.user_nick().c_str());
            ylFriend.setFriendSigature(fri.user_sign_info().c_str());

            friends[groupId].push_back(ylFriend);
        }
    }

    emit friendlist(friends, groups);
}

void PduHandler::_HandleMessageData(BasePdu *pdu)
{
    message::MessageData messageData;
    messageData.ParseFromString(pdu->getMessage());

    emit signleMessage(messageData.from_user_id(), QString(messageData.message_data().c_str()));
}

