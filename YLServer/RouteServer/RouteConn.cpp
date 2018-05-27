//
// Created by liuzheng on 18-4-9.
//

#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "pdu/protobuf/youliao.group.pb.h"
#include "pdu/protobuf/youliao.message.pb.h"
#include "RouteConn.h"
#include "util/util.h"
#include "network/netlib.h"
#include "CachePool.h"
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

    return static_cast<RouteConn *>(iter->second);
}


RouteConn::RouteConn() : BaseConn()
{
    m_index = 0;
}

RouteConn::~RouteConn()
{

}

void RouteConn::close()
{
    if (m_handle != NETWORK_ERROR)
    {
        netlib_close(m_handle);
    }

    auto iter = g_route_conn_map.find(m_handle);

    if (iter != g_route_conn_map.end())
    {
        g_route_conn_map.erase(iter);
    }

    auto iter1 = g_msg_conn_idx_map.find(m_index);

    if (iter1 != g_msg_conn_idx_map.end())
    {
        g_msg_conn_idx_map.erase(iter1);
    }

}

void RouteConn::onClose()
{
//    log("close");
    close();
}

void RouteConn::onConfirm()
{
    server::GetServerIndexRequest request;

    auto c = this;
    sendMessage(c, request, base::SID_SERVER, base::CID_SERVER_GET_SERVER_INDEX_REQUEST);
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
        case base::CID_SERVER_GET_SERVER_INDEX_RESPONE:
            _HandleMessageServerIndex(basePdu);
            break;
        case base::CID_SERVER_ROUTE_MESSAGE:
            _HandleRouteMessage(basePdu);
            break;
        case base::CID_SERVER_USER_GO_ONLINE:
            _HandleUserGoOnline(basePdu);
            break;
        case base::CID_SERVER_USER_GO_OFFLINE:
            _HandleUserGoOffline(basePdu);
            break;
        case base::CID_SERVER_GET_FRIENDS_STATUS_REQUEST:
            _HandleGetFriendsStatusRequest(basePdu);
            break;
        case base::CID_SERVER_GET_ONLINE_GROUP_MEMBER:
            _HandleGetGroupOnlineMember(basePdu);
            break;
        case base::CID_SERVER_FORWARD_GROUP_MESSAGE:
            _HandleForwardGroupMessage(basePdu);
            break;
        default:
            break;
    }

}


void RouteConn::_HandleUserGoOnline(BasePdu *basePdu)
{
    server::UserGoOnline userGoOnline;
    userGoOnline.ParseFromString(basePdu->getMessage());

    uint32_t userId = userGoOnline.user_id();
    uint32_t msdIdx = userGoOnline.msg_index();
    base::UserStatusType statusType = userGoOnline.user_state();

    log("用户%d在消息服务器%d上以状态%d登录", userId, msdIdx, statusType);

    //保存入redis
    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");

    if (conn)
    {
        //user_map 是 用户ID 和 用户在线状态的 key : value 组合
        conn->hset("user_map", std::to_string(userId), std::to_string(statusType));

        //user_msg_idx 是 用户ID 和 用户所登录的消息服务器idx 的 key ： value 组合
        conn->hset("user_msg_idx", std::to_string(userId), std::to_string(msdIdx));
    }

    CacheManager::instance()->releaseCacheConn(conn);
}


void RouteConn::_HandleUserGoOffline(BasePdu *basePdu)
{
    server::UserGoOffline userGoOffline;
    userGoOffline.ParseFromString(basePdu->getMessage());
    uint32_t userId = userGoOffline.user_id();


    log("用户%d注销", userId);

    //保存入redis
    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");

    std::string setName = "user_online_friends_" + std::to_string(userId);
    if (conn)
    {
        //删除其在线信息
        conn->hdel("user_map", std::to_string(userId));
        conn->hdel("user_msg_idx", std::to_string(userId));

        //通知好友其在线，并且从好友的在线好友列表中移除

        //[1] 获取在线好友
        std::list<uint32_t> members = conn->sMembers(setName);

        friendlist::FriendStatusChangeMessage msg;
        msg.set_friend_id(userId);
        msg.set_user_status_type(base::USER_STATUS_OFFLINE);

        //[2] 通知好友下线消息
        for(uint32_t friId : members)
        {
            msg.set_user_id(friId);
            std::string msgIdx = conn->hget("user_msg_idx", std::to_string(friId));
            RouteConn* msgConn = getRouteConn((uint32_t)atoi(msgIdx.c_str()));
            if (msgConn)
                sendMessage(msgConn, msg, base::SID_SERVER, base::CID_FRIENDLIST_FRIEND_STATUS_CHANGE);
        }

        setName = "user_groups_" + std::to_string(userId);
        //删除群组在线信息
        std::list<uint32_t> groups = conn->sMembers(setName);

        for (uint32_t groupId : groups)
        {
            setName = "group_online_members_" + std::to_string(groupId);
            conn->sRem(setName, std::to_string(userId));
        }
    }

    CacheManager::instance()->releaseCacheConn(conn);
}



void RouteConn::_HandleGetFriendsStatusRequest(BasePdu *basePdu)
{
    friendlist::FriendListRespone friendListRespone;
    friendListRespone.ParseFromString(basePdu->getMessage());

    uint32_t userId = friendListRespone.user_id();

    //获取好友在线状态
    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");

    if (!conn)
        return;

    std::list<uint32_t> onlineFriends;

    //::google::protobuf::Map< ::google::protobuf::uint32, ::youliao::pdu::friendlist::Group_Friend >
    auto& friendInfos = *(friendListRespone.mutable_friend_list());
    for (auto &pair : friendInfos)
    {
        auto &group = pair.second;
        for (int i = 0; i < group.friend__size(); ++i) {
            base::FriendInfo &friendInfo = *(group.mutable_friend_(i));

            uint32_t friendId = friendInfo.friend_id();
            std::string rv = conn->hget("user_map", std::to_string(friendId));

            if (rv.empty())
            {
                friendInfo.set_friend_is_online(false);
            }
            else
            {
                onlineFriends.push_back(friendId);
                friendInfo.set_friend_is_online(true);
            }
        }
    }


    sendMessage(this, friendListRespone, base::SID_SERVER, base::CID_SERVER_GET_FRIENDS_STATUS_RESPONE);


    //2. 通知其在线好友 用户上线
    friendlist::FriendStatusChangeMessage msg;
    msg.set_friend_id(userId);
    msg.set_user_status_type(base::USER_STATUS_ONLINE);


    //3. 发送通知，并且构建当前用户的在线好友redis set
    std::string setName = "user_online_friends_" + std::to_string(userId);
    for (uint32_t friId : onlineFriends)
    {
        msg.set_user_id(friId);
        std::string msgIdx = conn->hget("user_msg_idx", std::to_string(friId));
        auto msgConn = getRouteConn((uint32_t)atoi(msgIdx.c_str()));
        if (msgConn)
            sendMessage(msgConn, msg, base::SID_SERVER, base::CID_FRIENDLIST_FRIEND_STATUS_CHANGE);

        conn->sAdd(setName, std::to_string(friId));
    }


    CacheManager::instance()->releaseCacheConn(conn);
}


void RouteConn::_HandleGetGroupOnlineMember(BasePdu *basePdu)
{
    group::GetGroupListRespone msg;
    msg.ParseFromString(basePdu->getMessage());

    uint32_t userId = msg.user_id();


    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");
    if (conn)
    {

        std::string setName2 = "user_groups_" + std::to_string(userId);
        for (int i = 0; i < msg.group_info_size(); ++i)
        {
            uint32_t groupId = msg.group_info(i).group_id();
            std::string setName1 = "group_online_members_" + std::to_string(groupId);
            conn->sAdd(setName1, std::to_string(userId));
            conn->sAdd(setName2, std::to_string(groupId));
        }
    }
    CacheManager::instance()->releaseCacheConn(conn);
}


void RouteConn::_HandleForwardGroupMessage(BasePdu *basePdu)
{
    message::MessageData msg;
    msg.ParseFromString(basePdu->getMessage());

//    base::MessageType  msgType = msg.message_type();
//    if (msgType != base::MESSAGE_TYPE_GROUP_AUDIO || msgType != base::MESSAGE_TYPE_GROUP_TEXT)
//        return;

    uint32_t groupId = msg.to_id();
    std::string setName = "group_online_members_" + std::to_string(groupId);

    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");
    if (conn)
    {
        //获取群组在线成员
        auto onlineMembers = conn->sMembers(setName);
        for (uint32_t memberId : onlineMembers)
        {
            //获取群成员所在消息服务器ID
            std::string msgServIdx = conn->hget("user_msg_idx", std::to_string(memberId));
            auto msgConn = getRouteConn((uint32_t)atoi(msgServIdx.c_str()));
            msg.set_to_user_id(memberId);
            if (msgConn)
                sendMessage(msgConn, msg, base::SID_SERVER, base::CID_SERVER_FORWARD_GROUP_MESSAGE);
        }
    }

    CacheManager::instance()->releaseCacheConn(conn);

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


}

void RouteConn::_HandleMessageServerIndex(BasePdu *basePdu)
{
    server::GetServerIndexRespone getServerIndexRespone;
    getServerIndexRespone.ParseFromString(basePdu->getMessage());

    uint32_t index= getServerIndexRespone.index();

    m_index = index;

    addRouteConn(index, this);
}


void RouteConn::_HandleBroadcastMsg(BasePdu *basePdu)
{

}