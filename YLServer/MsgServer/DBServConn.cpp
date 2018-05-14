//
// Created by liuzheng on 18-3-21.
//

#include <network/ServerInfo.h>
#include <pdu/protobuf/youliao.message.pb.h>
#include "DBServConn.h"
#include "RouteConn.h"
#include "ClientConn.h"
#include "network/netlib.h"

#include "pdu/protobuf/youliao.login.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"
#include "pdu/protobuf/youliao.session.pb.h"
#include "pdu/protobuf/youliao.group.pb.h"
#include "User.h"

using namespace youliao::pdu;

static BaseConnMap_t g_db_server_conn_map;

serv_info_t*  g_db_server_list = nullptr;
uint32_t      g_db_server_count = 0;
uint32_t      g_db_server_login_count = 0;



void init_db_serv_conn(serv_info_t* server_list, uint32_t server_count, uint32_t curr_conn_cnt) {
    g_db_server_list = server_list;
    g_db_server_count = server_count;

    uint32_t total_db_instance = server_count / curr_conn_cnt;
    g_db_server_login_count = (total_db_instance / 2) * curr_conn_cnt;

    serv_init<DBServConn>(g_db_server_list, g_db_server_count);
}

template <class T>
void set_attach_data(T &t, net_handle_t data)
{
    SimpleBuffer simpleBuffer;
    simpleBuffer.writeUInt32(data);
    t.set_attach_data(simpleBuffer.getBuffer(), simpleBuffer.getWriteOffest());
}


template <class T>
uint32_t get_attach_data(T &t)
{
    SimpleBuffer simpleBuffer;
    simpleBuffer.write((void*)t.attach_data().c_str(), t.attach_data().length());
    return simpleBuffer.readUInt32();
}

DBServConn* get_db_server_conn()
{
    uint32_t i = 0;
    DBServConn* pDbConn = NULL;

    // determine if there is a valid DB server connection
    for (i = 0; i < g_db_server_count; i++) {
        pDbConn = (DBServConn*)g_db_server_list[i].server_conn;
        if (pDbConn && pDbConn->isOpen()) {
            break;
        }
    }

    if (i == g_db_server_count) {
        return NULL;
    }

    while (true) {
        int i = rand() % g_db_server_count;
        pDbConn = (DBServConn*)(g_db_server_list[i].server_conn);
        if (pDbConn && pDbConn->isOpen()) {
            break;
        }
    }

    return pDbConn;
}



DBServConn::DBServConn()
{
    m_open = false;
}

DBServConn::~DBServConn()
{

}

void DBServConn::connect(const std::string &server_ip, uint16_t server_port, uint32_t serv_idx)
{
    m_server_index = serv_idx;
    m_handle = netlib_connect(server_ip, server_port, baseconn_callback, (void*)&g_db_server_conn_map);

    if (m_handle != NETWORK_ERROR)
    {
        g_db_server_conn_map.insert(std::make_pair(m_handle, this));
    }

    m_open = true;
}

void DBServConn::close()
{
    if (m_handle != -1)
    {
        netlib_close(m_handle);
        g_db_server_conn_map.erase(m_handle);
        m_open = false;
    }
}

void DBServConn::onClose()
{
    close();

    delete this;
}

void DBServConn::handlePdu(BasePdu *pdu)
{
    switch (pdu->getCID())
    {
        case base::CID_SERVER_VALIDATE_RESPONE:
            _HandleValidateRespone(pdu);
            break;
        case base::CID_FRIENDLIST_GET_GROUPS_REPSONE:
            _HandleFriendGroupsRespone(pdu);
            break;
        case base::CID_FRIENDLIST_GET_RESPONE:
            _HandleFriendListRespone(pdu);
            break;
        case base::CID_FRIENDLIST_SIGNATURE_CHANGED_RESPONE:
            _HandleSignatureChangedRespone(pdu);
            break;
        case base::CID_FRIENDLIST_ADD_FRIEND_GROUP_RESPONE:
            _HandleAddNewFriendGroupRespone(pdu);
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
        case base::CID_FRIENDLIST_GET_REQUEST_HISTORY_RESPONE:
            _HandleGetAddRequestHistoryRespone(pdu);
            break;
        case base::CID_GROUP_CREATE_RESPONE:
            _HandleCreateGroupRespone(pdu);
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
        default:
            break;
    }

}


void DBServConn::_HandleValidateRespone(BasePdu *pdu)
{
    server::ValidateRespone validateRespone;
    validateRespone.ParseFromString(pdu->getMessage());

    uint32_t handle = get_attach_data(validateRespone);

    ClientConn *clientConn = findConn(handle);

    log("收到服务器登录校验用户%d响应", clientConn->getUserId());

    if (clientConn)
    {
        base::UserInfo *userInfo = new base::UserInfo(validateRespone.user_info());

        if (UserManager::instance()->isLogin(userInfo->user_id()))
        {
            //重复登录
            return;
        }

        login::UserLoginRespone userLoginRespone;
        if (validateRespone.result_code() == 1)
            userLoginRespone.set_result_code(base::MSG_SERVER_FULL);
        else
        {
            userLoginRespone.set_result_code(base::NONE);
            //  登录成功
            UserManager::instance()->addUser(userInfo->user_id(), clientConn);
        }

        userLoginRespone.set_allocated_user_info(userInfo);

        log("发送登录结果到用户%d", clientConn->getUserId());

        BasePdu *basePdu = new BasePdu;
        basePdu->setCID(base::CID_LOGIN_RESPONE_USERLOGIN);
        basePdu->setSID(base::SID_OTHER);
        basePdu->writeMessage(&userLoginRespone);
        clientConn->sendBasePdu(basePdu);
        delete basePdu;
    }
}

void DBServConn::_HandleFriendGroupsRespone(BasePdu *pdu)
{
    friendlist::GroupsRespone groupsRespone;
    groupsRespone.ParseFromString(pdu->getMessage());
    uint32_t userId = groupsRespone.user_id();

    log("发送好友分组到用户%d", userId);

    auto clientConn = UserManager::instance()->getUser(userId)->getConn();

    if (clientConn)
    {
        BasePdu basePdu;
        basePdu.setSID(base::SID_FRIEND_LIST);
        basePdu.setCID(base::CID_FRIENDLIST_GET_GROUPS_REPSONE);
        basePdu.writeMessage(&groupsRespone);
        clientConn->sendBasePdu(&basePdu);
    }
}

void DBServConn::_HandleFriendListRespone(BasePdu *pdu)
{
    friendlist::FriendListRespone friendListRespone;
    friendListRespone.ParseFromString(pdu->getMessage());

    uint32_t handle = get_attach_data(friendListRespone);

    ClientConn *clientConn = findConn(handle);

    if (!clientConn)
        return;

    log("发送好友列表到用户%d", clientConn->getUserId());

    //发送好友列表给客户端
    BasePdu basePdu;
    basePdu.setSID(base::SID_FRIEND_LIST);
    basePdu.setCID(base::CID_FRIENDLIST_GET_RESPONE);
    basePdu.writeMessage(&friendListRespone);
    clientConn->sendBasePdu(&basePdu);

    RouteConn *routeConn = get_route_server_conn();
    if (!routeConn)
        return;

    //发送好友上线通知
    //之所以在这里发送，是因为DBServer是在获取好友列表时更新 在线好友列表
    server::RouteStatusChange routeMessage;
    routeMessage.set_user_id(clientConn->getUserId());
    routeMessage.set_route_status_type(base::ROUTE_MESSAGE_FRIEND_STATUS_CHANGE);
    set_attach_data(routeMessage, base::USER_STATUS_ONLINE);

    BasePdu basePdu1;
    basePdu1.setSID(base::SID_SERVER);
    basePdu1.setCID(base::CID_SERVER_ROUTE_BROADCAST);
    basePdu1.writeMessage(&routeMessage);

    routeConn->sendBasePdu(&basePdu1);
}

void DBServConn::_HandleSignatureChangedRespone(BasePdu *pdu)
{
    friendlist::SignatureChangeRespone signatureChangeRespone;
    signatureChangeRespone.ParseFromString(pdu->getMessage());

    uint32_t userId = signatureChangeRespone.user_id();
    base::ResultType resultType = signatureChangeRespone.result_type();
    bool modifySuccess = false;

    if (resultType == base::NONE)
        modifySuccess = true;
    else if (resultType == base::SIGNATURE_MODIFY_FAILED)
        modifySuccess = false;

    log("发送个性签名修改响应到用户%d", userId);

    BasePdu basePdu;
    basePdu.setSID(base::SID_FRIEND_LIST);
    basePdu.setCID(base::CID_FRIENDLIST_SIGNATURE_CHANGED_RESPONE);
    basePdu.writeMessage(&signatureChangeRespone);

    //发送到client
    UserManager::instance()->getUser(userId)->getConn()->sendBasePdu(&basePdu);

    if (modifySuccess)
    {
        log("广播用户%d的个性签名修改状态到所有在线好友", userId);
        //修改成功。发送到路由服务器广播修改后的个性签名到好友
        server::RouteStatusChange routeMessage;
        routeMessage.set_user_id(userId);
        routeMessage.set_route_status_type(base::ROUTE_MESSAGE_FRIEND_SIGNATURE_CHANGE);
        routeMessage.set_attach_data(signatureChangeRespone.user_signature());

        auto routeConn = get_route_server_conn();
        if (routeConn)
        {
            basePdu.setSID(base::SID_SERVER);
            basePdu.setCID(base::CID_SERVER_ROUTE_BROADCAST);
            basePdu.writeMessage(&routeMessage);

            routeConn->sendBasePdu(&basePdu);
        }
    }
}


void DBServConn::_HandleAddNewFriendGroupRespone(BasePdu *pdu)
{
    friendlist::AddNewFriendGroupRespone addNewFriendGroupRespone;
    addNewFriendGroupRespone.ParseFromString(pdu->getMessage());

    uint32_t userId = addNewFriendGroupRespone.user_id();
    std::string groupName = addNewFriendGroupRespone.group_name();

    BasePdu basePdu1;
    basePdu1.setSID(base::SID_FRIEND_LIST);
    basePdu1.setCID(base::CID_FRIENDLIST_ADD_FRIEND_GROUP_RESPONE);
    basePdu1.writeMessage(&addNewFriendGroupRespone);

    log("收到用户%d添加好友分组成功响应", userId);

    auto  user = UserManager::instance()->getUser(userId);

    if (user)
    {
        auto conn = user->getConn();
        if (conn)
            conn->sendBasePdu(&basePdu1);
    }
}

void DBServConn::_HandleGetSessionsRespone(BasePdu *basePdu)
{
    session::GetSessionReponse reponse;
    reponse.ParseFromString(basePdu->getMessage());

    uint32_t userId = reponse.userid();

    auto user = UserManager::instance()->getUser(userId);

    if (user)
    {
        auto conn = user->getConn();

        if(conn)
        {
            sendMessage(conn, reponse, base::SID_SESSION, base::CID_SESSIONLIST_GET_SESSIONS_RESPONE);
        }
    }
}



void DBServConn::_HandleAddSessionRespone(BasePdu *basePdu)
{
    session::NewSessionRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t userId = respone.user_id();

    auto user = UserManager::instance()->getUser(userId);

    if (user)
    {
        auto conn = user->getConn();

        if (conn)
        {
            sendMessage(conn, respone, base::SID_SESSION, base::CID_SESSIONLIST_ADD_SESSION);
            return;
        }
    }

    //请求路由服务器转发

}

void DBServConn::_HandleSearchFriendRespone(BasePdu *basePdu)
{
    friendlist::SearchFriendRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t userId = respone.user_id();
    auto user = UserManager::instance()->getUser(userId);

    if (user)
    {
        auto conn = user->getConn();
        if (conn)
        {
            sendMessage(conn, respone, base::SID_FRIEND_LIST, base::CID_FRIENDLIST_SEARCH_FRIEND_RESPONE);
        }

    }
}


void DBServConn::_HandleGetLatestMsgIdRespone(BasePdu *basePdu)
{
    message::LatestMsgIdRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t  userId = respone.user_id();

    auto user = UserManager::instance()->getUser(userId);

    if (user)
    {
        auto conn = user->getConn();
        if (conn)
        {
            sendMessage(conn, respone, base::SID_MESSAGE, base::CID_MESSAGE_GET_LATEST_MSG_ID_RESPONE);
        }
    }
}


void DBServConn::_HandleGetAddRequestHistoryRespone(BasePdu *pdu)
{
    friendlist::GetAddRequestHistoryRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t userId = respone.user_id();

    auto user = UserManager::instance()->getUser(userId);

    if (user)
    {
        auto conn = user->getConn();
        if (conn)
        {
            sendMessage(conn, respone, base::SID_FRIEND_LIST, base::CID_FRIENDLIST_GET_REQUEST_HISTORY_RESPONE);
        }
    }
}


void DBServConn::_HandleCreateGroupRespone(BasePdu *pdu)
{
    group::GroupCreateRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t userId = respone.user_id();

    auto user = UserManager::instance()->getUser(userId);
    if (user)
    {
        auto conn = user->getConn();
        if (conn)
        {
            sendMessage(conn, respone, base::SID_GROUP, base::CID_GROUP_CREATE_RESPONE);
        }
    }
}


void DBServConn::_HandleGetGroupListRespone(BasePdu *basePdu)
{
    group::GetGroupListRespone respone;
    respone.ParsePartialFromString(basePdu->getMessage());

    uint32_t userId = respone.user_id();
    auto user = UserManager::instance()->getUser(userId);
    if (user)
    {
        auto conn = user->getConn();
        if (conn)
            sendMessage(conn, respone, base::SID_GROUP, base::CID_GROUP_GET_LIST_RESPONE);
    }
}

void DBServConn::_HandleGetGroupMemberRespone(BasePdu *basePdu)
{
    group::GetGroupMemberInfoRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t userId = respone.user_id();
    auto user = UserManager::instance()->getUser(userId);
    if (user)
    {
        auto conn = user->getConn();
        if (conn)
            sendMessage(conn, respone, base::SID_GROUP, base::CID_GROUP_GET_MEMBER_RESPONE);
    }
}

void DBServConn::_HandleSearchGroupRespone(BasePdu *basePdu)
{
    group::SearchGroupRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t userId = respone.user_id();
    auto user = UserManager::instance()->getUser(userId);
    if (user)
    {
        auto conn = user->getConn();
        if (conn)
            sendMessage(conn, respone, base::SID_GROUP, base::CID_GROUP_SEARCH_GROUP_RESPONE);
    }
}


void DBServConn::_HandleAddGroupRespone(BasePdu *basePdu)
{
    group::AddGroupRespone respone;
    respone.ParseFromString(basePdu->getMessage());

    uint32_t userId = respone.user_id();
    auto user = UserManager::instance()->getUser(userId);
    if (user)
    {
        auto conn = user->getConn();
        if (conn)
            sendMessage(conn, respone, base::SID_GROUP, base::CID_GROUP_ADD_GROUP_RESPONE);
    }
}


void DBServConn::_HandleVerifyNotify(BasePdu *basePdu)
{
    group::GroupVerifyNotifyUsers groupVerifyNotifyUsers;
    groupVerifyNotifyUsers.ParseFromString(basePdu->getMessage());

    group::GroupVerifyNotify groupVerifyNotify = groupVerifyNotifyUsers.verify_notify();

    std::list<uint32_t> routeUser; //需要转发到路由服务器  可能是没在线也可能时未在当前服务器登录
    for (int i = 0; i < groupVerifyNotifyUsers.notify_users_size(); ++i) {
        uint32_t userId = groupVerifyNotifyUsers.notify_users(i);
        auto user = UserManager::instance()->getUser(userId);
        if (!user)
        {
            routeUser.push_back(userId);
            continue;
        }

        auto conn = user->getConn();
        if (!conn)
        {
            routeUser.push_back(userId);
            continue;
        }

        //直接发送
        sendMessage(conn, groupVerifyNotify, base::SID_GROUP, base::CID_GROUP_VERIFY_NOTIFY);
    }
}