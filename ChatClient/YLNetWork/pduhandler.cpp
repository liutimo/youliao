#include "pduhandler.h"
#include <list>
#include <iostream>

#include <QMap>
#include <QVector>
#include <QDebug>
#include <QDateTime>

#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.login.pb.h"
#include "protobuf/youliao.friendlist.pb.h"
#include "protobuf/youliao.message.pb.h"
#include "protobuf/youliao.session.pb.h"
#include "protobuf/youliao.group.pb.h"
#include "protobuf/youliao.file.pb.h"
#include "YLDataBase/yldatabase.h"
#include "globaldata.h"
#include "YLFileTransfer/yltransferfile.h"
#include "YLFileTransfer/ylfiletransfermanager.h"
#include "YLTray/ylmaintray.h"
#include "ylbusiness.h"
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
    qRegisterMetaType<QVector<YLFriend>>("QVector<YLFriend>");
    qRegisterMetaType<YLGroup>("YLGroup");
    qRegisterMetaType<QVector<YLGroup>>("QVector<YLGroup>");
    qRegisterMetaType<base::UserInfo>("base::UserInfo");
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
    case base::CID_LOGIN_REGISTER_RESPONE:
        _HandleRegisterRespone(pdu);
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
    case base::CID_MESSAGE_GET_OFFLINE_MESSAGE_RESPONE:
        _HandleOfflineMessageData(pdu);
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
    case base::CID_FRIENDLIST_SEARCH_FRIEND_RESPONE:
        _HandleSearchFriendRespone(pdu);
        break;
    case base::CID_MESSAGE_GET_LATEST_MSG_ID_RESPONE:
        _HandleGetLatestMsgIdRespone(pdu);
        break;
    case base::CID_FRIENDLIST_ADD_FRIEND_REQUEST:
        _HandleAddFriendRequest(pdu);
        break;
    case base::CID_FRIENDLIST_GET_REQUEST_HISTORY_RESPONE:
        _HandleGetAddRequestHistoryRespone(pdu);
        break;
    case base::CID_GROUP_CREATE_RESPONE:
        _HandleCreatGroupRespone(pdu);
        break;
    case base::CID_GROUP_GET_LIST_RESPONE:
        _HandleGetGroupListRespone(pdu);
        break;
    case base::CID_GROUP_GET_MEMBER_RESPONE:
        _HandleGetGroupMemberRespone(pdu);
        break;
    case base::CID_GROUP_SEARCH_GROUP_RESPONE:
        _HandleSearchGroupRespone(pdu);
        break;
    case base::CID_GROUP_ADD_GROUP_RESPONE:
        _HandleAddGroupRespone(pdu);
        break;
    case base::CID_GROUP_VERIFY_NOTIFY:
        _HandleVerifyNotify(pdu);
        break;
    case base::CID_FILE_RESPONE:
        _handleSendFileRespone(pdu);
        break;
    case base::CID_FILE_NOTIFY:
        _HandleFileNotify(pdu);
        break;
    case base::CID_OTHER_MODIFY_USER_HEADER_RESPONE:
        _HandleModifyUserIconRespone(pdu);
        break;
    case base::CID_GROUP_GET_LATEST_MSG_ID_RESPONE:
        _HandleGetLatestGroupMsgIdRespone(pdu);
        break;
    case base::CID_GROUP_EXIT_GROUP_RESPONE:
        _HandleExitGroupRespone(pdu);
        break;
    case base::CID_GROUP_MODIFY_HEADER_RESPONE:
        _HandleModifyGroupIconRespone(pdu);
        break;
    case base::CID_GROUP_SET_MANAGER_RESPONE:
        _HandleSetGroupManagerRespone(pdu);
        break;
    case base::CID_GROUP_KICK_OUT_RESPONE:
        _HandleKickOutGroupMemberRespone(pdu);
        break;
    case base::CID_GROUP_ADD_REQUEST_HANDLE_RESULT:
        _HandleGroupAddRequestHandleRespone(pdu);
        break;
    case base::CID_FRIENDLIST_DELETE_FRIEND_RESPONE:
        _HandleDeleteFriendRespone(pdu);
        break;
    case base::CID_OTHER_GFT_FRIEND_INFORMATION_RESPONE:
        _HandleFriendInfomation(pdu);
        break;
    case base::CID_FRIENDLIST_ADD_FRIEND_RESPONE:
        _HandleAddFriendRespone(pdu);
        break;
    case base::CID_OTHER_FRIEND_INFORMATION_CHANGE_NOTIFY:
        _HandleUserInformationChange(pdu);
        break;
    case base::CID_GROUP_UPDATE_GROUP_LIST:
        _HandleUpdateGroupListRespone(pdu);
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


void PduHandler::_HandleRegisterRespone(BasePdu *pdu)
{
    login::UserRegisterRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t resultCode = respone.result_code();
    std::string account = respone.user_account();

    emit regiserStatus(resultCode, account.c_str());
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

    //保存到树数据库
    {
        YLDataBase db;
        db.addSomeFriendGroup(groupsMap);
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
            ylFriend.setFriendGroupId(groupId);
            ylFriend.setRelateId(fri.related_id());
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

    //保存到树数据库
    {
        YLDataBase db;
        db.setFriends(friends);

    }
    emit friendlist(friends);
}

void PduHandler::_HandleMessageData(BasePdu *pdu)
{
    message::MessageData messageData;
    messageData.ParseFromString(pdu->getMessage());

    if (messageData.from_user_id() == GlobalData::getCurrLoginUserId())
        return;
    uint32_t senderId = messageData.from_user_id();
    QString msgContent = messageData.message_data().c_str();

    base::MessageType msgType = messageData.message_type();
    if (msgType == base::MESSAGE_TYPE_SINGLE_TEXT)
    {
        GlobalData::setLatestMsgId(senderId, messageData.msg_id() + 1);

        auto singleChatWidget = GlobalData::getSingleChatWidget(senderId);
        if (singleChatWidget)
        {
            //保存到数据库
            {
                YLDataBase db;
                db.saveMessage(messageData);
            }
            singleChatWidget->receiveMessage(senderId, msgContent);
            //此情况标记为已读
            YLBusiness::sendMessageAck(messageData.from_user_id(), messageData.to_id(), messageData.msg_id());
        }
        else
        {
            YLMainTray::instance()->receiveMessage(messageData);
            emit unReadMessage(senderId, msgContent, 1);
        }
    }
    else if (msgType == base::MESSAGE_TYPE_GROUP_TEXT)
    {
        //创建session
        YLSession session = GlobalData::getSessionByGroupId(messageData.to_id());
        if (session.getOtherId() != messageData.to_id())
        {
            //Session不存在,创建session
            YLBusiness::createNewSession(messageData.to_id(), base::SESSION_TYPE_GROUP);
        }

        GlobalData::setGroupLatestMsgId(messageData.to_id(), messageData.msg_id() + 1);
        auto groupChatWidget = GlobalData::getGroupChatWidget(messageData.to_id());
        if (groupChatWidget)
        {
            groupChatWidget->receiveMessage(senderId, msgContent);
            //数据库操作
            {
                YLDataBase db;
                db.addOneGroupMessage(messageData.to_id(), messageData.from_user_id(), messageData.msg_id(), messageData.message_data().c_str(), messageData.create_time());
            }
        }
        else
        {
            YLMainTray::instance()->receiveMessage(messageData);
            emit unReadMessage(messageData.to_id(), msgContent, 2);
        }  
    }
    else if (msgType == base::MESSAGE_TYPE_SINGLE_AUDIO)
    {
        GlobalData::setLatestMsgId(senderId, messageData.msg_id() + 1);
        //保存文件
        uint32_t time = QDateTime::currentDateTime().toTime_t();
        QString fileName = QString::number(time) + ".amr";
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        file.write(messageData.message_data().c_str(), messageData.message_data().length());
        file.close();

        GlobalData::addAudio(QString::number(senderId) + "_" + QString::number(messageData.msg_id()), fileName);

        auto singleChatWidget = GlobalData::getSingleChatWidget(senderId);
        if (singleChatWidget)
            singleChatWidget->receiveAudioMessage(senderId, msgContent, messageData.msg_id(), messageData.audio_time());
        else
        {
            YLMainTray::instance()->receiveMessage(messageData);
            emit unReadMessage(senderId, msgContent, 1);
        }
    }

    switch (msgType) {
    case base::MESSAGE_TYPE_GROUP_TEXT:
    case base::MESSAGE_TYPE_GROUP_AUDIO:
        emit receiveNewMsg(YLSession::GROUP, messageData.from_user_id());
        break;
    case base::MESSAGE_TYPE_SINGLE_TEXT:
    case base::MESSAGE_TYPE_SINGLE_AUDIO:
        emit receiveNewMsg(YLSession::FRIEND, messageData.from_user_id());
        break;
    case base::MESSAGE_TYPE_VALIDATE_MSG:
        emit receiveNewMsg(YLSession::REQUEST);
    default:
        break;
    }
}


void PduHandler::_HandleOfflineMessageData(BasePdu *pdu)
{
    message::GetOfflineMessageRespone respone;
    respone.ParseFromString(pdu->getMessage());

    for (int i = 0; i < respone.msg_data_size(); ++i)
    {
        auto messageData = respone.msg_data(i);

        if (messageData.from_user_id() == GlobalData::getCurrLoginUserId())
            return;

        uint32_t senderId = messageData.from_user_id();
        QString msgContent = messageData.message_data().c_str();

        base::MessageType msgType = messageData.message_type();
        if (msgType == base::MESSAGE_TYPE_SINGLE_TEXT)
        {
            auto singleChatWidget = GlobalData::getSingleChatWidget(senderId);
            if (singleChatWidget)
            {
                singleChatWidget->receiveMessage(senderId, msgContent);
                //此情况标记为已读
                YLBusiness::sendMessageAck(messageData.from_user_id(), messageData.to_id(), messageData.msg_id());
            }
            else
            {
                YLMainTray::instance()->receiveMessage(messageData);
                emit unReadMessage(senderId, msgContent, 1);
            }
        }
        else if (msgType == base::MESSAGE_TYPE_SINGLE_AUDIO)
        {
            //保存文件
            uint32_t time = QDateTime::currentDateTime().toTime_t();
            QString fileName = QString::number(time) + ".amr";
            QFile file(fileName);
            file.open(QIODevice::WriteOnly);
            file.write(messageData.message_data().c_str(), messageData.message_data().length());
            file.close();

            GlobalData::addAudio(QString::number(senderId) + "_" + QString::number(messageData.msg_id()), fileName);

            auto singleChatWidget = GlobalData::getSingleChatWidget(senderId);
            if (singleChatWidget)
                singleChatWidget->receiveAudioMessage(senderId, msgContent, messageData.msg_id(), messageData.audio_time());
            else
            {
                YLMainTray::instance()->receiveMessage(messageData);
                emit unReadMessage(senderId, msgContent, 1);
            }
        }
        emit receiveNewMsg(YLSession::FRIEND, messageData.from_user_id());
    }
}

void PduHandler::_HandleFriendStatusChangeMessage(BasePdu *pdu)
{
    friendlist::FriendStatusChangeMessage friendStatusChangeMessage;
    friendStatusChangeMessage.ParseFromString(pdu->getMessage());

    uint32_t changedUserId = friendStatusChangeMessage.friend_id();
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


    QList<YLSession> list;
    QList<YLSession> topSessionList;

    for(int i = 0; i < respone.sessions_size(); ++i)
    {
        base::SessionInfo si;
        si = respone.sessions(i);

        YLSession s;
        s.setSessionId(si.session_id());
        s.setOtherId(si.other_id());
        s.setSessionLastChatMessage(si.last_message_data().c_str());
        s.setSessionTop(si.session_top());
        s.setSessionType(si.session_type());
        s.setSessionLastChatTime(si.latest_msg_time());
        list.push_back(s);

        //对于好友类型,需要设置最新的消息ID
        if (s.getSessionType() == base::SESSION_TYPE_SINGLE)
            GlobalData::setLatestMsgId(si.other_id(), si.latest_msg_id());

        if (s.sessionTop())
            topSessionList.push_back(s);

    }

    GlobalData::setSessions(list);
    GlobalData::setTopSessions(topSessionList);

    emit sessions();

    YLBusiness::getOfflineMessage();
}


void PduHandler::_HandleAddSessionRespone(BasePdu *pdu)
{
    session::NewSessionRespone respone;
    respone.ParseFromString(pdu->getMessage());

    const base::SessionInfo &s = respone.session();

    YLSession session;
    session.setSessionId(s.session_id());
    session.setOtherId(s.other_id());
    session.setSessionType(s.session_type());
    session.setSessionLastChatTime(s.latest_msg_time());
    session.setSessionLastChatMessage(s.last_message_data().c_str());
    session.addUnReadMsgCount();

    GlobalData::getSessions().push_front(session);

    emit newSession();
}


void PduHandler::_HandleSearchFriendRespone(BasePdu *pdu)
{
    friendlist::SearchFriendRespone respone;
    respone.ParseFromString(pdu->getMessage());

    QVector<YLFriend> friends;

    for (int i = 0; i < respone.friends_size(); ++i)
    {
        base::FriendInfo friendInfo = respone.friends(i);
        YLFriend fri;
        fri.setFriendId(friendInfo.friend_id());
        fri.setFriendAccount(QString::number(friendInfo.friend_account()));
        fri.setFriendImagePath(friendInfo.friend_header_url().c_str());
        fri.setFriendNickName(friendInfo.friend_nick().c_str());
        friends.push_back(fri);
    }

    emit searchResult(friends);
}


void PduHandler::_HandleGetLatestMsgIdRespone(BasePdu *pdu)
{
    message::LatestMsgIdRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t friId = respone.friend_id();
    uint32_t latestMsgId = respone.latest_msg_id();

    GlobalData::setLatestMsgId(friId, latestMsgId + 1);
}

void PduHandler::_HandleAddFriendRequest(BasePdu *pdu)
{
    friendlist::AddFriendRequest request;
    request.ParseFromString(pdu->getMessage());

    YLAddRequest addRequest;
    addRequest.setOtherId(request.user_id());
    addRequest.setOtherNick(request.user_nick().c_str());
    addRequest.setOtherHeadUrl(request.user_head_url().c_str());
    addRequest.setValidateData(request.validatedata().c_str());
    GlobalData::setRequest(addRequest);
    emit newAddRequest();

    QString msg =  QString(request.user_nick().c_str()) + QString("请求加好友");

    emit unReadMessage(3, msg, 3);
}


void PduHandler::_HandleGetAddRequestHistoryRespone(BasePdu *pdu)
{
    friendlist::GetAddRequestHistoryRespone respone;
    respone.ParseFromString(pdu->getMessage());

    int size = respone.history_size();
    QVector<YLAddRequest> history;
    for (int i = 0; i < size; ++i)
    {
        base::AddRequestInfo info = respone.history(i);
        YLAddRequest request;
        request.setId(info.id());
        request.setOtherId(info.other_id());
        request.setOtherNick(info.other_nick().c_str());
        request.setOtherHeadUrl(info.other_head_url().c_str());
        request.setValidateData(info.validate_data().c_str());
        request.setHandleTime(info.handle_time());
        request.setResultId(info.result_id());
        history.push_back(request);
    }

    GlobalData::setRequestHistory(history);
}


void PduHandler::_HandleCreatGroupRespone(BasePdu *pdu)
{
    group::GroupCreateRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t resultCode = respone.result_code();

    base::GroupInfo groupInfo =  respone.group_info();

    YLGroup group;
    group.setGroupId(groupInfo.group_id());
    group.setGroupName(groupInfo.group_name().c_str());
    group.setGroupCapacity(groupInfo.group_capacity());
    group.setGroupCreator(groupInfo.group_creator());
    group.setGroupImage(groupInfo.group_head().c_str());
    group.setCreateTime(groupInfo.group_created());
    group.setVerifyType(groupInfo.group_verify_type());

    for (int i = 0; i < groupInfo.members_size(); ++i)
        group.addMember(groupInfo.members(i));

    for (int i = 0; i < groupInfo.managers_size(); ++i)
        group.addManager(groupInfo.members(i));

    GlobalData::addToGroups(group);

    {
        YLDataBase db;
        uint32_t idx = db.getGroupIdx(group.getGroupId());
        if (idx != 0)
            db.remOneGroup(idx);
        db.addOneGroup(group);
    }

    emit newGroup(group);
}


void PduHandler::_HandleGetGroupListRespone(BasePdu *pdu)
{
    group::GetGroupListRespone respone;
    respone.ParseFromString(pdu->getMessage());

    for (int i = 0; i < respone.group_info_size(); ++i)
    {
        base::GroupInfo groupInfo = respone.group_info(i);
        YLGroup group;
        group.setGroupId(groupInfo.group_id());
        group.setGroupName(groupInfo.group_name().c_str());
        group.setGroupCapacity(groupInfo.group_capacity());
        group.setGroupCreator(groupInfo.group_creator());
        group.setGroupImage(groupInfo.group_head().c_str());
        group.setCreateTime(groupInfo.group_created());
        group.setVerifyType(groupInfo.group_verify_type());
        group.setLatestMsgId(groupInfo.group_latest_msg_id());

        GlobalData::setGroupLatestMsgId(groupInfo.group_id(), groupInfo.group_latest_msg_id() + 1);

        for (int i = 0; i < groupInfo.members_size(); ++i)
            group.addMember(groupInfo.members(i));

        for (int i = 0; i < groupInfo.managers_size(); ++i)
            group.addManager(groupInfo.managers(i));

        GlobalData::addToGroups(group);

        {
            YLDataBase db;
            uint32_t idx = db.getGroupIdx(group.getGroupId());
            if (idx != 0)
                db.remOneGroup(idx);
            db.addOneGroup(group);
        }

    }
    emit groupList();
}


void PduHandler::_HandleGetGroupMemberRespone(BasePdu *pdu)
{
    group::GetGroupMemberInfoRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t groupId = respone.group_id();
    QVector<base::MemberInfo> members;
    for (int i = 0; i < respone.member_infos_size(); ++i)
    {
        int memberId = respone.member_infos(i).user_id();
        members.push_back(respone.member_infos(i));
        {
            YLDataBase db;
            uint32_t idx = db.getMemberIdx(groupId, memberId);
            if (idx != 0)
                db.remOneMember(idx);

            uint32_t type = 0;

            YLGroup group = GlobalData::getGroupByGroupId(groupId);

            if (group.getGroupCreator() == memberId)
                type = 2;
            else if (group.getManagers().contains(memberId))
                type = 1;

            db.addOneMember(groupId, respone.member_infos(i), type);
        }
    }

    GlobalData::setGroupMember(groupId, members);



    emit groupMembers();
}


void PduHandler::_HandleSearchGroupRespone(BasePdu *pdu)
{
    group::SearchGroupRespone respone;
    respone.ParseFromString(pdu->getMessage());

    QVector<YLGroup> groups;

    for (int i = 0; i < respone.groups_size(); ++i)
    {
        base::GroupInfo groupInfo = respone.groups(i);
        YLGroup group;
        group.setGroupId(groupInfo.group_id());
        group.setGroupName(groupInfo.group_name().c_str());
        group.setGroupCapacity(groupInfo.group_capacity());
        group.setGroupCreator(groupInfo.group_creator());
        group.setGroupImage(groupInfo.group_head().c_str());
        group.setCreateTime(groupInfo.group_created());
        group.setVerifyType(groupInfo.group_verify_type());
        for (int i = 0; i < groupInfo.members_size(); ++i)
            group.addMember(groupInfo.members(i));

        for (int i = 0; i < groupInfo.managers_size(); ++i)
            group.addManager(groupInfo.managers(i));
        groups.push_back(group);
    }

    emit searchGroupResult(groups);
}

void PduHandler::_HandleAddGroupRespone(BasePdu *pdu)
{
    group::AddGroupRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t userId  = respone.user_id();
    uint32_t resCode = respone.result_coid();
    if (resCode == 0)
    {
        base::GroupInfo groupInfo = respone.group_info();

        YLGroup group;
        group.setGroupId(groupInfo.group_id());
        group.setGroupName(groupInfo.group_name().c_str());
        group.setGroupCapacity(groupInfo.group_capacity());
        group.setGroupCreator(groupInfo.group_creator());
        group.setGroupImage(groupInfo.group_head().c_str());
        group.setCreateTime(groupInfo.group_created());
        group.setVerifyType(groupInfo.group_verify_type());
        for (int i = 0; i < groupInfo.members_size(); ++i)
            group.addMember(groupInfo.members(i));
        for (int i = 0; i < groupInfo.managers_size(); ++i)
            group.addManager(groupInfo.members(i));

        GlobalData::addToGroups(group);

        emit newGroup(group);
    }
}

//群组
void PduHandler::_HandleVerifyNotify(BasePdu *pdu)
{
    group::GroupVerifyNotify notify;
    notify.ParseFromString(pdu->getMessage());
    uint32_t requestId = notify.user_id();
    uint32_t groupId = notify.group_id();
    base::UserInfo requestUserInfo = notify.user_info();

    YLAddRequest addRequest;
    addRequest.setOtherId(requestId);
    addRequest.setOtherNick(requestUserInfo.user_nick().c_str());
    addRequest.setOtherHeadUrl(requestUserInfo.user_header_url().c_str());
    addRequest.setValidateData(notify.verify_data().c_str());
    addRequest.setGroupId(groupId);

    GlobalData::addOneGroupRequest(addRequest);
    emit newAddRequest();

    QString msg = addRequest.getOtherNick() + QString("申请加入群") + GlobalData::getGroupByGroupId(groupId).getGroupName();
    emit unReadMessage(3, msg, 3);
}

void PduHandler::_handleSendFileRespone(BasePdu *pdu)
{
    file::SendFileRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t resultCode = respone.result_code();

    if (resultCode != 0)
    {
        //任务创建失败！更新ＵＩ
        return;
    }
    //保存任务信息
    YLTransferFileEntity fileEntity;
    fileEntity.m_task_id    = respone.task_id();
    fileEntity.m_from_id    = respone.from_user_id();
    fileEntity.m_to_id      = respone.to_user_id();
    fileEntity.m_file_name  = respone.file_name();
    fileEntity.setSaveFilePath(respone.file_name());    //?
    fileEntity.m_time       = (uint32_t)time(nullptr);
    uint32_t transMode      = respone.trans_mode();
    if (base::FILE_TYPE_ONLINE == transMode)
        fileEntity.m_client_role = base::CLIENT_REALTIME_SENDER;
    else if (base::FILE_TYPE_OFFLINE == transMode)
        fileEntity.m_client_role = base::CLIENT_OFFLINE_UPLOAD;

    fileEntity.m_file_object = new YLTransferFile(respone.file_name(), false);

    if (fileEntity.m_file_object)
    {
        fileEntity.m_file_size = fileEntity.m_file_object->length();
    }

    //连接到文件服务器
    const base::IpAddress &ipAddress = respone.ip_addr_list(0);
    fileEntity.m_ip = ipAddress.ip();
    fileEntity.m_port = ipAddress.port();

    if (!YLTransferFileEntityManager::instance()->pushYLTransferFileEntity(fileEntity))
    {
        YLTransferFileEntityManager::instance()->updateFileInfoBysTaskID(fileEntity);
    }

    //连接到文件服务器
    YLTransferFileEntityManager::instance()->openFileSocketByTaskId(fileEntity.m_task_id);
}


void PduHandler::_HandleFileNotify(BasePdu *pdu)
{
    file::FileNotify fileNotify;
    fileNotify.ParseFromString(pdu->getMessage());

    YLTransferFileEntity entity;
    entity.m_from_id    = fileNotify.from_user_id();
    entity.m_to_id      = fileNotify.to_user_id();
    entity.m_task_id    = fileNotify.task_id();
    entity.m_file_size  = fileNotify.file_size();

    //设置文件名
    std::string fileName = fileNotify.file_name();
    int pos = fileName.find_last_of('/');
    fileName = fileName.substr(pos + 1);
    entity.m_file_name  = fileName;

    //设置文件保存目录
    entity.setSaveFilePath(GlobalData::filePath.toStdString());

    entity.m_file_object = new YLTransferFile(entity.getSaveFilePath() + fileName , true);

    base::IpAddress ipAddress = fileNotify.ip_addr_list(0);
    entity.m_ip = ipAddress.ip();
    entity.m_port = ipAddress.port();

    base::TransferFileType mode =  fileNotify.trans_mode();
    if (mode == base::FILE_TYPE_ONLINE)
    {
        entity.m_client_role = base::CLIENT_REALTIME_RECVER;
    }
    else if (mode == base::FILE_TYPE_OFFLINE)
    {
        entity.m_client_role = base::CLIENT_OFFLINE_DOWNLOAD;
    }
    entity.m_time = (uint32_t)time(nullptr);

    YLTransferFileEntityManager::instance()->pushYLTransferFileEntity(entity);

    if (1 == fileNotify.offline_ready())
    {
        //离线文件传输结束
    }

    //连接服务器
    YLTransferFileEntityManager::instance()->openFileSocketByTaskId(entity.m_task_id);
}

void PduHandler::_HandleModifyUserIconRespone(BasePdu *pdu)
{
    other::ModifyUserImageRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t resultCode = respone.result_code();

    if (resultCode == 0)
    {
        //成功上传

        //[1] 修改全局变量中头像url
        GlobalData::setCurrLoginUserHeaderIcon(respone.icon_url());

        //[2] 通知主界面修改资料
        emit userHeaderIconChanged();
    }

}

void PduHandler::_HandleModifyGroupIconRespone(BasePdu *pdu)
{
    group::ModifyGroupHeaderRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t resCode = respone.result_code();
    uint32_t groupId = respone.group_id();
    QString url = respone.header_url().c_str();

    if (resCode == 0)
        emit modifyGroupHeader(groupId, url);
}

void PduHandler::_HandleSetGroupManagerRespone(BasePdu *pdu)
{
    group::SetGroupManagerRespone respone;

}

void PduHandler::_HandleKickOutGroupMemberRespone(BasePdu *pdu)
{

}

void PduHandler::_HandleGetLatestGroupMsgIdRespone(BasePdu *pdu)
{
    group::GetLatestGroupMsgIdRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t groupId = respone.group_id();
    uint32_t latestMsgId = respone.latest_msg_id();

    GlobalData::setGroupLatestMsgId(groupId, latestMsgId + 1);
}

void PduHandler::_HandleExitGroupRespone(BasePdu *pdu)
{
    group::ExitGroupRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t groupId = respone.group_id();
    uint32_t resultCode = respone.result_code();

    emit exitGroupResult(groupId, resultCode);
}

void PduHandler::_HandleGroupVerifyNotify(BasePdu *pdu)
{
    group::GroupVerifyNotify notify;
    notify.ParseFromString(pdu->getMessage());

    uint32_t requestUserId = notify.user_id();
    uint32_t groupId = notify.group_id();
    const base::UserInfo &userInfo = notify.user_info();
}

void PduHandler::_HandleGroupAddRequestHandleRespone(BasePdu *pdu)
{
    group::GroupAddRequestHandleResult result;
    result.ParseFromString(pdu->getMessage());

    YLBusiness::getGroupList();
//    result
}


void PduHandler::_HandleDeleteFriendRespone(BasePdu *pdu)
{
    friendlist::DeleteFriendRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t friendId = respone.friend_id();

    emit deleteFriend(friendId);
}


void PduHandler::_HandleFriendInfomation(BasePdu *pdu)
{
    other::GetFriendInformationRespone respone;
    respone.ParseFromString(pdu->getMessage());

    const base::UserInfo &userInfo = respone.user_info();

    emit friendInformation(userInfo);
}


void PduHandler::_HandleAddFriendRespone(BasePdu *pdu)
{
   friendlist::AddFriendRespone respone;
   respone.ParseFromString(pdu->getMessage());

   uint32_t resultId = respone.result_id();
   if (resultId == 1)
   {
       //同意添加好友
       emit addFriendSuccess();
   }
   else if (resultId == 2)
   {
       //拒绝添加好友
   }
   else if (resultId == 3)
   {
       //忽略
   }
}

void PduHandler::_HandleUserInformationChange(BasePdu *pdu)
{
    YLBusiness::getFriendGroupsRequest(GlobalData::getCurrLoginUserId());
    YLBusiness::getFriendListRequest(GlobalData::getCurrLoginUserId());
}

void PduHandler::_HandleUpdateGroupListRespone(BasePdu *pdu)
{
    YLBusiness::getGroupList();
}
