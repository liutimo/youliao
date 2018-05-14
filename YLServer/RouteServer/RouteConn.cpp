//
// Created by liuzheng on 18-4-9.
//

#include <pdu/protobuf/youliao.base.pb.h>
#include <pdu/protobuf/youliao.server.pb.h>
#include "RouteConn.h"
#include "util/util.h"
#include "network/netlib.h"
#include "DBServConn.h"
static BaseConnMap_t g_route_conn_map;
static std::map<uint32_t, RouteConn*> g_msg_conn_idx_map;



void addRouteConn(uint32_t index, RouteConn *routeConn)
{
    g_msg_conn_idx_map.insert(std::make_pair(index, routeConn));
}


RouteConn *getRouteConn(uint32_t index)
{
    auto iter = g_msg_conn_idx_map.find(index);
    if (iter == g_msg_conn_idx_map.end())
        return nullptr;

    return iter->second;
}

template <class T>
void set_attach_data(T &t, net_handle_t data)
{
    SimpleBuffer simpleBuffer;
    simpleBuffer.writeUInt32(data);
    t.set_attach_data(simpleBuffer.getBuffer(), simpleBuffer.getWriteOffest());
}


RouteConn::RouteConn() : BaseConn()
{

}

RouteConn::~RouteConn()
{

}

void RouteConn::close()
{

}

void RouteConn::onClose()
{
//    log("close");
    close();
}

void RouteConn::onConnect(net_handle_t handle)
{
    m_handle = handle;

    g_route_conn_map.insert(std::make_pair(handle, this));
    netlib_option(handle, NETLIB_OPT_SET_CALLBACK, (void*)baseconn_callback);
    netlib_option(handle, NETLIB_OPT_SET_CALLBACK_DATA, (void*)&g_route_conn_map);
}

void RouteConn::handlePdu(BasePdu *basePdu)
{
    switch (basePdu->getCID())
    {
        case base::CID_SERVER_ROUTE_BROADCAST:
            _HandleBroadcastMsg(basePdu);
            break;
        case base::CID_SERVER_GET_ONLINE_FRIENDS_RESPONE:
            _HandleMessageServerIndex(basePdu);
            break;
        case base::CID_SERVER_ROUTE_MESSAGE:
            _HandleRouteMessage(basePdu);
            break;
        default:
            break;
    }

}


void RouteConn::_HandleRouteMessage(BasePdu *basePdu)
{
    server::RouteMessageForward routeMessageForward;
    routeMessageForward.ParseFromString(basePdu->getMessage());

    server::RouteGetFriendOnlineStatus request;
    request.set_user_id(routeMessageForward.user_id());
    request.set_friend_id(routeMessageForward.friend_id());
    request.set_msg_id(routeMessageForward.msg_id());
    request.set_create_time(routeMessageForward.create_time());
    request.set_message_type(routeMessageForward.message_type());
    request.set_message_data(routeMessageForward.message_data());

    DBServConn *conn = get_db_server_conn();

    if (!conn)
        return;

    BasePdu basePdu1;
    basePdu1.setSID(base::SID_SERVER);
    basePdu1.setCID(base::CID_SERVER_GET_FRIEND_ONLINE_STATUS);
    basePdu1.writeMessage(&request);

    conn->sendBasePdu(&basePdu1);

}

void RouteConn::_HandleMessageServerIndex(BasePdu *basePdu)
{
    server::GetServerIndexRespone getServerIndexRespone;
    getServerIndexRespone.ParseFromString(basePdu->getMessage());

    uint32_t index= getServerIndexRespone.index();

    addRouteConn(index, this);
}


void RouteConn::_HandleBroadcastMsg(BasePdu *basePdu)
{
    auto dbServConn = get_db_server_conn();
    if (!dbServConn)
        return;

    log("处理来自MsgServer的广播请求");

    server::RouteBroadcastStatusChange routeBroadcastStatusChange;
    routeBroadcastStatusChange.ParseFromString(basePdu->getMessage());

    uint32_t  userID = routeBroadcastStatusChange.user_id();

    server::RouteGetOnlineFirendRequest routeGetOnlineFirendRequest;
    routeGetOnlineFirendRequest.set_user_id(userID);
    routeGetOnlineFirendRequest.set_route_status_type(routeBroadcastStatusChange.route_status_type());
    routeGetOnlineFirendRequest.set_attach_data(routeBroadcastStatusChange.attach_data());

    BasePdu pdu;
    pdu.setSID(base::SID_SERVER);
    pdu.setCID(base::CID_SERVER_GET_ONLINE_FRIENDS_REQUEST);
    pdu.writeMessage(&routeGetOnlineFirendRequest);
    log("发送用户%d在线好友列表请求到DBServer", userID);
    dbServConn->sendBasePdu(&pdu);
}