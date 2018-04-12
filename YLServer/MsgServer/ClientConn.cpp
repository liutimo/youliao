/*================================================================
*   
*   文件名称: ClientConn.cpp
*   创 建 者: 刘正
*   邮   箱: 779564531@qq.com
*   创建日期: 2018年02月09日　 下午8:45
*
================================================================*/


#include "ClientConn.h"
#include "network/netlib.h"
#include "DBServConn.h"
#include "RouteConn.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.login.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"
#include "pdu/protobuf/youliao.message.pb.h"
#include "User.h"
#include <sys/time.h>
using namespace youliao::util;

static ClientConnMap_t g_client_conn_map;

static uint32_t g_msg_serv_idx = 0;

void setMsgServIdx(uint32_t msg_serv_idx)
{
    g_msg_serv_idx = msg_serv_idx;
}

uint32_t  getMsgServIdx()
{
    return g_msg_serv_idx;
}


uint64_t get_tick_count()
{

    struct timeval tval;
    uint64_t ret_tick;

    gettimeofday(&tval, NULL);

    ret_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
    return ret_tick;
}

void msg_conn_loop_callback(callback_data callback_data, uint8_t type, int handle, void *pParam)
{
    if (type == NETWORK_LOOP)
    {
        uint64_t current_tick = get_tick_count();
        for (auto  item : g_client_conn_map)
        {
            auto conn = item.second;
            if (current_tick - conn->m_last_heart_beat_tick > 1000)
            {
                //超时
                UserManager::instance()->removerUser(conn->getUserId());
                conn->onClose();
            }

        }
    }
}

template <class T>
void set_attach_data(T &t, net_handle_t data)
{
    SimpleBuffer simpleBuffer;
    simpleBuffer.writeUInt32(data);
    t.set_attach_data(simpleBuffer.getBuffer(), simpleBuffer.getWriteOffest());
}

ClientConn *findConn(uint32_t handle)
{
    auto iter = g_client_conn_map.find(handle);
    if (iter != g_client_conn_map.end())
        return iter->second;
    return nullptr;
}

//////////////////////////////////////

ClientConn::ClientConn() : BaseConn()
{
    m_last_heart_beat_tick = get_tick_count();
}

ClientConn::~ClientConn()
{

}

void ClientConn::onConnect(net_handle_t handle)
{
    m_handle = handle;

    g_client_conn_map.insert(std::make_pair(m_handle, this));

    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK, (void*)baseconn_callback);
    netlib_option(m_handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)&g_client_conn_map);
//    netlib_add_loop(msg_conn_loop_callback, nullptr);
}

void ClientConn::onClose()
{
    auto iter = g_client_conn_map.find(m_handle);

    if (iter != g_client_conn_map.end())
    {
        g_client_conn_map.erase(iter);
        netlib_close(m_handle);
    }

}


void ClientConn::handlePdu(BasePdu *pdu)
{
    switch (pdu->getCID())
    {
        case base::CID_LOGIN_REQUEST_USERLOGIN:
            _HandleClientLoginRequest(pdu);
            break;
        case ::base::CID_LOGIN_REQUEST_USERLOGINOUT:
            _HandleClientLoginOutRequest(pdu);
            break;
        case base::CID_OTHER_HEARTBEAT:
            _HandleHeartBeat(pdu);
            break;
        case base::CID_FRIENDLIST_GET_GROUPS_REQUEST:
            _HandleGroupsRequest(pdu);
            break;
        case base::CID_FRIENDLIST_GET_REQUEST:
            _HandleFriendListGetRequest(pdu);
            break;
        case base::CID_MESSAGE_DATA:
            _HandleMessageDataRequest(pdu);
            break;
        case base::CID_FRIENDLIST_SIGNATURE_CHANGED_REQUEST:
            _HandleSignatureChangeRequest(pdu);
            break;
        case base::CID_FRIENDLIST_ADD_FRIEND_GROUP_REQUEST:
            _HandleAddFriendGroupRequest(pdu);
            break;
        default:
            break;
    }
}

void ClientConn::_HandleClientLoginRequest(BasePdu *pdu)
{

    login::UserLoginRequest request;
    request.ParseFromString(pdu->getMessage());
    log("登录请求! 登录名: %s, 登录密码:%s", request.user_name().c_str(), request.user_password().c_str());

    server::ValidateRequest validateRequest;
    validateRequest.set_user_name(request.user_name());
    validateRequest.set_user_pwd(request.user_password());
    validateRequest.set_msg_serv_id(getMsgServIdx());
    set_attach_data(validateRequest, m_handle);

    DBServConn *pDbServConn = get_db_server_conn();
    BasePdu *basePdu = new BasePdu;
    basePdu->setSID(base::SID_OTHER);
    basePdu->setCID(base::CID_SERVER_VALIDATE_REQUEST);
    basePdu->writeMessage(&validateRequest);
    pDbServConn->sendBasePdu(basePdu);
    delete basePdu;

}

void ClientConn::_HandleHeartBeat(BasePdu *pdu)
{
    log("received heartbeat!");
    m_last_heart_beat_tick = get_tick_count();
    sendBasePdu(pdu);
}


void ClientConn::_HandleGroupsRequest(BasePdu *pdu)
{
    friendlist::GroupsRequest groupsRequest;
    groupsRequest.ParseFromString(pdu->getMessage());

    log("获取用户 %d 的好友分组信息", groupsRequest.user_id());

    BasePdu basePdu;
    basePdu.setSID(base::SID_SERVER);
    basePdu.setCID(base::CID_FRIENDLIST_GET_GROUPS_REQUEST);
    basePdu.writeMessage(&groupsRequest);

    auto dbServConn = get_db_server_conn();

    if (dbServConn)
        dbServConn->sendBasePdu(&basePdu);
}

void ClientConn::_HandleFriendListGetRequest(BasePdu *pdu)
{

    std::cout << "收到来自" << m_handle << "的好友列表请求" << std::endl;

    friendlist::FriendListRequest friendListRequest;
    friendListRequest.ParseFromString(pdu->getMessage());

    m_user_id = friendListRequest.user_id();
    log("获取用户id=%d的好友列表", m_user_id);

    //判断是否是非法请求
    if (!UserManager::instance()->isLogin(m_user_id))
    {
        //非法请求
        return;
    }

    friendListRequest.set_msg_serv_idx(getMsgServIdx());
    set_attach_data(friendListRequest, m_handle);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
    {
        BasePdu *basePdu = new BasePdu;
        basePdu->setSID(base::SID_FRIEND_LIST);
        basePdu->setCID(base::CID_FRIENDLIST_GET_REQUEST);
        basePdu->writeMessage(&friendListRequest);
        dbServConn->sendBasePdu(basePdu);
        delete basePdu;
    }

}

void ClientConn::_HandleClientLoginOutRequest(BasePdu *pdu)
{
    login::UserLoginOutRequest loginOutRequest;
    loginOutRequest.ParseFromString(pdu->getMessage());

    uint32_t userId = loginOutRequest.user_id();

    auto user = UserManager::instance()->getUser(userId);

    if (user != nullptr)
    {
        auto conn = user->getConn();
        UserManager::instance()->removerUser(userId);
        conn->onClose();
    }

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
    {
        server::UserOffline userOffline;
        userOffline.set_user_id(userId);
        BasePdu basePdu;
        basePdu.setSID(base::SID_SERVER);
        basePdu.setCID(base::CID_SERVER_USER_LOGOUT);
        basePdu.writeMessage(&userOffline);
        dbServConn->sendBasePdu(&basePdu);
    }

    //发送好友下线通知
    server::RouteMessage routeMessage;
    routeMessage.set_user_id(m_user_id);
    routeMessage.set_route_status_type(base::ROUTE_MESSAGE_FRIEND_STATUS_CHANGE);
    set_attach_data(routeMessage, base::USER_STATUS_OFFLINE);

    BasePdu basePdu1;
    basePdu1.setSID(base::SID_SERVER);
    basePdu1.setCID(base::CID_SERVER_ROUTE_BROADCAST);
    basePdu1.writeMessage(&routeMessage);

    get_route_server_conn()->sendBasePdu(&basePdu1);
}

void ClientConn::_HandleMessageDataRequest(BasePdu *pdu)
{
    message::MessageData messageData;
    messageData.ParseFromString(pdu->getMessage());

    uint32_t toUserID = messageData.to_user_id();

    User *user = UserManager::instance()->getUser(toUserID);

    if (user == nullptr)
    {
        //接受这不在当前服务器,或者未登录.
        //

    }
    else
    {
        //接受者在当前服务器登录
        BasePdu basePdu;
        basePdu.setSID(base::SID_MESSAGE);
        basePdu.setCID(base::CID_MESSAGE_DATA);
        basePdu.writeMessage(&messageData);

        user->getConn()->sendBasePdu(&basePdu);
    }
}

void ClientConn::_HandleSignatureChangeRequest(BasePdu *pdu)
{
    friendlist::SignatureChangeResquest signatureChangeResquest;
    signatureChangeResquest.ParseFromString(pdu->getMessage());

    log("user %d signature modify request: %s", signatureChangeResquest.user_id(), signatureChangeResquest.user_signature().c_str());

    DBServConn *dbServConn = get_db_server_conn();

    if (!dbServConn)
        return;

    BasePdu basePdu;
    basePdu.setSID(base::SID_SERVER);
    basePdu.setCID(base::CID_FRIENDLIST_SIGNATURE_CHANGED_REQUEST);
    basePdu.writeMessage(&signatureChangeResquest);

    dbServConn->sendBasePdu(&basePdu);
}

void ClientConn::_HandleAddFriendGroupRequest(BasePdu *pdu)
{
    friendlist::AddNewFriendGroupRequest addNewFriendGroupRequest;
    addNewFriendGroupRequest.ParseFromString(pdu->getMessage());

    BasePdu basePdu;
    basePdu.setSID(base::SID_SERVER);
    basePdu.setCID(base::CID_FRIENDLIST_ADD_FRIEND_GROUP_REQUEST);
    basePdu.writeMessage(&addNewFriendGroupRequest);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
        dbServConn->sendBasePdu(&basePdu);
}