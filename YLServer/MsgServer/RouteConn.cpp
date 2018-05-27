//
// Created by liuzheng on 18-4-9.
//

#include "RouteConn.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"
#include "pdu/protobuf/youliao.message.pb.h"
#include "network/netlib.h"
#include "pdu/protobuf/youliao.login.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"

#include "ClientConn.h"
#include "User.h"
using namespace youliao::pdu;

static BaseConnMap_t g_route_server_conn_map;

serv_info_t*  g_route_server_list = nullptr;
uint32_t      g_route_server_count = 0;
uint32_t      g_route_server_login_count = 0;



void init_route_serv_conn(serv_info_t* server_list, uint32_t server_count, uint32_t curr_conn_cnt) {
    g_route_server_list = server_list;
    g_route_server_count = server_count;

    uint32_t total_route_instance = server_count / curr_conn_cnt;
    g_route_server_login_count = (total_route_instance / 2) * curr_conn_cnt;

//    serv_init<RouteConn>(g_route_server_list, g_route_server_count);
    RouteConn *routeConn = new RouteConn;
    routeConn->connect(server_list->server_ip, server_list->server_port, g_route_server_count);
    g_route_server_list[0].server_conn = routeConn;
}

template <class T>
uint32_t get_attach_data(T &t)
{
    SimpleBuffer simpleBuffer;
    simpleBuffer.write((void*)t.attach_data().c_str(), t.attach_data().length());
    return simpleBuffer.readUInt32();
}

RouteConn* get_route_server_conn()
{
    uint32_t i = 0;
    RouteConn* pRouteConn = NULL;

    // determine if there is a valid Route server connection
    for (i = 0; i < g_route_server_count; i++) {
        pRouteConn = (RouteConn*)g_route_server_list[i].server_conn;
        if (pRouteConn && pRouteConn->isOpen()) {
            break;
        }
    }

    if (i == g_route_server_count) {
        return NULL;
    }

    while (true) {
        int i = rand() % g_route_server_count;
        pRouteConn = (RouteConn*)(g_route_server_list[i].server_conn);
        if (pRouteConn && pRouteConn->isOpen()) {
            break;
        }
    }

    return (RouteConn*)(g_route_server_list[0].server_conn);
}



RouteConn::RouteConn() : BaseConn()
{
    m_open = false;
}

RouteConn::~RouteConn()
{

}

void RouteConn::connect(const std::string &server_ip, uint16_t server_port, uint32_t serv_idx)
{
    m_server_index = serv_idx;
    m_handle = netlib_connect(server_ip, server_port, baseconn_callback, (void*)&g_route_server_conn_map);

    if (m_handle != NETWORK_ERROR)
    {
        g_route_server_conn_map.insert(std::make_pair(m_handle, this));

        m_open = true;
    }


}

void RouteConn::close()
{
    if (m_handle != -1)
    {
        netlib_close(m_handle);
        g_route_server_conn_map.erase(m_handle);
        m_open = false;
    }
}

void RouteConn::onClose()
{
    close();
}

void RouteConn::onConfirm()
{
    server::GetServerIndexRespone respone;
    respone.set_index(getMsgServIdx());

    sendMessage(this, respone, base::SID_SERVER, base::CID_SERVER_GET_SERVER_INDEX_RESPONE);
}


void RouteConn::handlePdu(BasePdu *pdu)
{
    switch (pdu->getCID())
    {
        case base::CID_SERVER_ROUTE_BROADCAST:
            _HandleRouteBroadcast(pdu);
            break;
        case base::CID_SERVER_GET_FRIENDS_STATUS_RESPONE:
            _HandleGetFriendsStatusRespone(pdu);
            break;
        case base::CID_FRIENDLIST_FRIEND_STATUS_CHANGE:
            _HandleHandleStatusChange(pdu);
            break;
        case base::CID_SERVER_FORWARD_GROUP_MESSAGE:
            _HandleForwardGroupMessage(pdu);
            break;
        default:
            break;
    }

}


void RouteConn::_HandleRouteBroadcast(BasePdu *basePdu)
{
    server::RouteBroadcastStatusChange routeBroadcast;
    routeBroadcast.ParseFromString(basePdu->getMessage());

    int i = routeBroadcast.friends_size();


    log("开始广播用户%d的消息, 接收者个数=%d", routeBroadcast.user_id(), routeBroadcast.friends_size());

    BasePdu pdu;
    pdu.setSID(base::SID_FRIEND_LIST);
    switch (routeBroadcast.route_status_type())
    {
        case base::ROUTE_MESSAGE_FRIEND_STATUS_CHANGE:
            //状态更改
        {
            pdu.setCID(base::CID_FRIENDLIST_FRIEND_STATUS_CHANGE);

            friendlist::FriendStatusChangeMessage friendStatusChangeMessage;
            friendStatusChangeMessage.set_user_id(routeBroadcast.user_id());
            friendStatusChangeMessage.set_user_status_type((base::UserStatusType)get_attach_data(routeBroadcast));
            pdu.writeMessage(&friendStatusChangeMessage);
        }
            break;
        case base::ROUTE_MESSAGE_FRIEND_SIGNATURE_CHANGE:
        {
            pdu.setCID(base::CID_FRIENDLIST_FRIEND_SIGNATURE_CHANGED);

            friendlist::FriendSignatureChangedNotify friendSignatureChangedNotify;
            friendSignatureChangedNotify.set_friend_id(routeBroadcast.user_id());
            friendSignatureChangedNotify.set_friend_signatrue(routeBroadcast.attach_data());
            pdu.writeMessage(&friendSignatureChangedNotify);
        }
            break;
        default:
            break;

    }


    for (int j = 0; j < i; ++j)
    {
        uint32_t userId = routeBroadcast.friends(j);
        log("%d. 通知用户%d", j, userId);

        auto user = UserManager::instance()->getUser(userId);

        if (!user)
            continue;

        user->getConn()->sendBasePdu(&pdu);
    }
}


void RouteConn::_HandleHandleStatusChange(BasePdu *basePdu)
{
    friendlist::FriendStatusChangeMessage msg;
    msg.ParseFromString(basePdu->getMessage());

    uint32_t userId = msg.user_id();

    auto user = UserManager::instance()->getUser(userId);
    if (user)
    {
        auto conn = user->getConn();

        if (conn)
            sendMessage(conn, msg, base::SID_FRIEND_LIST, base::CID_FRIENDLIST_FRIEND_STATUS_CHANGE);
    }

}
//
//void RouteConn::_HandleRouteToMessage(BasePdu *basePdu)
//{
//    server::RouteMessage routeMessage;
//    routeMessage.ParseFromString(basePdu->getMessage());
//
//    auto user = UserManager::instance()->getUser(routeMessage.friend_id());
//
//    if (!user)
//        return;;
//
//    message::MessageData messageData;
//    messageData.set_from_user_id(routeMessage.user_id());
//    messageData.set_to_user_id(routeMessage.friend_id());
//    messageData.set_message_data(routeMessage.message_data());
//    messageData.set_message_type(routeMessage.message_type());
//    messageData.set_create_time(routeMessage.create_time());
//    messageData.set_msg_id(routeMessage.msg_id());
//
//    BasePdu basePdu1;
//    basePdu1.setSID(base::SID_MESSAGE);
//    basePdu1.setCID(base::CID_MESSAGE_DATA);
//    basePdu1.writeMessage(&messageData);
//
//    user->getConn()->sendBasePdu(&basePdu1);
//}

void RouteConn::_HandleGetFriendsStatusRespone(BasePdu *basePdu)
{
    friendlist::FriendListRespone friendListRespone;
    friendListRespone.ParseFromString(basePdu->getMessage());

    uint32_t userId = friendListRespone.user_id();

    auto user = UserManager::instance()->getUser(userId);

    if (!user)
        return;

    ClientConn *clientConn = user->getConn();

    if (!clientConn)
        return;

    log("发送好友列表到用户%d", clientConn->getUserId());

    //发送好友列表给客户端
    sendMessage(clientConn, friendListRespone, base::SID_FRIEND_LIST, base::CID_FRIENDLIST_GET_RESPONE);
}


void RouteConn::_HandleForwardGroupMessage(BasePdu *basePdu)
{
    message::MessageData msg;
    msg.ParseFromString(basePdu->getMessage());

    uint32_t toUserId = msg.to_user_id();

    auto user = UserManager::instance()->getUser(toUserId);
    if (user)
    {
        auto conn = user->getConn();
        if (conn)
            sendMessage(conn, msg, base::SID_MESSAGE, base::CID_MESSAGE_DATA);
    }


}
