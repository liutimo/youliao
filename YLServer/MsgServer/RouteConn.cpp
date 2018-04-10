//
// Created by liuzheng on 18-4-9.
//

#include "RouteConn.h"
#include <pdu/protobuf/youliao.friendlist.pb.h>
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

    serv_init<RouteConn>(g_route_server_list, g_route_server_count);
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

    return (RouteConn*)(g_route_server_list->server_conn);
}



RouteConn::RouteConn()
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
    }

    m_open = true;
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

    delete this;
}

void RouteConn::handlePdu(BasePdu *pdu)
{
    switch (pdu->getCID())
    {
        case base::CID_SERVER_GET_SERVER_INDEX_REQUEST:
            _HandleGetServerIndexRequest(pdu);
            break;
        case base::CID_SERVER_ROUTE_BROADCAST:
            _HandleRouteBroadcast(pdu);
            break;
        default:
            break;
    }

}


void RouteConn::_HandleGetServerIndexRequest(BasePdu *basePdu)
{
    server::GetServerIndexRespone getServerIndexRespone;
    getServerIndexRespone.set_index(10);
    BasePdu basePdu1;
    basePdu1.setSID(base::SID_SERVER);
    basePdu1.setCID(base::CID_SERVER_GET_ONLINE_FRIENDS_RESPONE);
    basePdu1.writeMessage(&getServerIndexRespone);

    sendBasePdu(&basePdu1);
}


void RouteConn::_HandleRouteBroadcast(BasePdu *basePdu)
{
    server::RouteBroadcast routeBroadcast;
    routeBroadcast.ParseFromString(basePdu->getMessage());

    int i = routeBroadcast.friends_size();

    BasePdu pdu;
    pdu.setSID(base::SID_FRIEND_LIST);
    switch (routeBroadcast.route_status_type())
    {
        case base::ROUTE_MESSAGE_FRIEND_STATUS_CHANGE:
            //状态更改
        {
            pdu.setCID(base::CID_FRIENDLIST_FRIEND_STATUS_CHANGE);

            friendlist::FriendStatusChangeMessage friendStatusChangeMessage;
            friendStatusChangeMessage.set_user_status_type((base::UserStatusType)get_attach_data(routeBroadcast));
            pdu.writeMessage(&friendStatusChangeMessage);
        }
            break;
        default:
            break;

    }


    for (int j = 0; j < i; ++j)
    {
        uint32_t userId = routeBroadcast.friends(j);
        log("notify user : %d", userId);

        auto user = UserManager::instance()->getUser(userId);

        if (!user)
            continue;

        user->getConn()->sendBasePdu(&pdu);
    }
}