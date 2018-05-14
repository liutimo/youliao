//
// Created by liuzheng on 18-4-9.
//

//
// Created by liuzheng on 18-3-21.
//

#include <network/ServerInfo.h>
#include <pdu/protobuf/youliao.friendlist.pb.h>
#include "DBServConn.h"
#include "network/netlib.h"
#include "pdu/protobuf/youliao.login.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "RouteConn.h"

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

    return (DBServConn*)(g_db_server_list->server_conn);
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
        case base::CID_SERVER_GET_ONLINE_FRIENDS_RESPONE:
            _HandleGetOnlineFriendsRespone(pdu);
            break;
        case base::CID_SERVER_GET_FRIEND_ONLINE_STATUS:
            _HandleRouteToMessage(pdu);
            break;
        default:
            break;
    }
}

void DBServConn::_HandleGetOnlineFriendsRespone(BasePdu *basePdu)
{
//
//              message RouteGetOnlineFriendRespone
//              {
//                  uint32 user_id = 1;
//                  //在线好友ID : 消息服务器ID
//                  map<uint32, uint32> online_firends = 2;
//                  bytes attach_data = 20;
//              }
//
////[4] routeServer广播消息
//              message RouteBroadcast
//              {
//                  uint32 user_id = 1;
//                  repeated uint32 friends = 2;
//                  bytes route_data = 20;
//              }

    server::RouteGetOnlineFriendRespone routeGetOnlineFriendRespone;
    routeGetOnlineFriendRespone.ParseFromString(basePdu->getMessage());

    uint32_t  change_user_id = routeGetOnlineFriendRespone.user_id();
    auto onlineFriendsMap = routeGetOnlineFriendRespone.online_firends();

    log("收到用户%d的在线好友列表,在线好友人数=%d", change_user_id, onlineFriendsMap.size());

    // 消息服务器IDX : 该消息服务器的在线好友
    std::map<uint32_t, server::RouteBroadcastStatusChange> broadcastMap;

    for (auto elem : onlineFriendsMap)
    {
        broadcastMap[elem.second].add_friends(elem.first);
    }

    BasePdu basePdu1;
    basePdu1.setSID(base::SID_SERVER);
    basePdu1.setCID(base::CID_SERVER_ROUTE_BROADCAST);

    for (auto elem : broadcastMap)
    {
        elem.second.set_user_id(change_user_id);
        elem.second.set_route_status_type(routeGetOnlineFriendRespone.route_status_type());
        elem.second.set_attach_data(routeGetOnlineFriendRespone.attach_data());

        //开始发送到对应的服务器
        auto routeConn = getRouteConn(elem.first);

        if (!routeConn || elem.second.friends_size() == 0)
            continue;

        basePdu1.writeMessage(&elem.second);
        routeConn->sendBasePdu(&basePdu1);
    }
}

void DBServConn::_HandleRouteToMessage(BasePdu *basePdu)
{
    server::RouteGetFriendOnlineStatus routeGetFriendOnlineStatus;
    routeGetFriendOnlineStatus.ParseFromString(basePdu->getMessage());


    int msgIdx = routeGetFriendOnlineStatus.msg_idx();


    RouteConn *routeConn = getRouteConn(msgIdx);

    if (!routeConn)
        return;

    server::RouteMessage routeMessage;
    routeMessage.set_user_id(routeGetFriendOnlineStatus.user_id());
    routeMessage.set_friend_id(routeGetFriendOnlineStatus.friend_id());
    routeMessage.set_msg_id(routeGetFriendOnlineStatus.msg_idx());
    routeMessage.set_create_time(routeGetFriendOnlineStatus.create_time());
    routeMessage.set_message_type(routeGetFriendOnlineStatus.message_type());
    routeMessage.set_message_data(routeGetFriendOnlineStatus.message_data());

    BasePdu basePdu1;
    basePdu1.setSID(base::SID_SERVER);
    basePdu1.setCID(base::CID_SERVER_ROUTE_TO_MESSAGE);
    basePdu1.writeMessage(&routeMessage);

    routeConn->sendBasePdu(&basePdu1);
}