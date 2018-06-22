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
#include "pdu/protobuf/youliao.session.pb.h"
#include "pdu/protobuf/youliao.group.pb.h"
#include "pdu/protobuf/youliao.file.pb.h"
#include "pdu/protobuf/youliao.other.pb.h"
#include "User.h"
#include <sys/time.h>
#include "FileServerConn.h"
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
        case base::CID_LOGIN_REGISTER_REQUEST:
            _HandleUserRegisterRequest(pdu);
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
        case base::CID_MESSAGE_DATA_ACK:
            _HandleMessageDataAck(pdu);
            break;
        case base::CID_FRIENDLIST_SIGNATURE_CHANGED_REQUEST:
            _HandleSignatureChangeRequest(pdu);
            break;
        case base::CID_FRIENDLIST_ADD_FRIEND_GROUP_REQUEST:
            _HandleAddFriendGroupRequest(pdu);
            break;
        case base::CID_FRIENDLIST_RENAME_FRIEND_GROUP_REQUEST:
            _HandleRenameFriendGroupRequest(pdu);
            break;
        case base::CID_FRIENDLIST_DELETE_FRIEND_GROUP_REQUEST:
            _HandleDeleteFriendGroupRequest(pdu);
            break;
        case base::CID_FRIENDLIST_MOVE_FRIEND_TO_GROUP_REQUEST:
            _HandleMoveFriendToGroupRequest(pdu);
            break;
        case base::CID_FRIENDLIST_DELETE_FRIEND_REQUEST:
            _HandleDeleteFriendRequest(pdu);
            break;
        case base::CID_FRIENDLIST_MODIFY_FRIEND_REMARK_RQUEST:
            _HandleModifyFriendRemarkRequest(pdu);
            break;
        case base::CID_SESSIONLIST_GET_SESSIONS_REQUEST:
            _HandleGetSessionsRequest(pdu);
            break;
        case base::CID_SESSIONLIST_DEL_SESSION:
            _HandleDeleteSessionRequest(pdu);
            break;
        case base::CID_SESSIONLIST_TOP_SESSION:
            _HandleTopSessionRequest(pdu);
            break;
        case base::CID_FRIENDLIST_SEARCH_FRIEND_REQUEST:
            _HandleSearchFriendRequest(pdu);
            break;
        case base::CID_FRIENDLIST_ADD_FRIEND_REQUEST:
            _HandleAddFriendRequest(pdu);
            break;
        case base::CID_MESSAGE_GET_LATEST_MSG_ID_REQUEST:
            _HandleGetLatestMsgIdRequest(pdu);
            break;
        case base::CID_FRIENDLIST_ADD_FRIEND_RESPONE:
            _HandleGetLatestMsgIdRespone(pdu);
            break;
        case base::CID_FRIENDLIST_GET_REQUEST_HISTORY_REQUEST:
            _HandlerGetAddRequestHistoryRequest(pdu);
            break;
        case base::CID_GROUP_CREATE_REQUEST:
            _HandleCreatGroupRequest(pdu);
            break;
        case base::CID_GROUP_GET_LIST_REQUEST:
            _HandleGetGroupListRequest(pdu);
            break;
        case base::CID_GROUP_GET_MEMBER_REQUEST:
            _HandleGetGroupMemberRequest(pdu);
            break;
        case base::CID_GROUP_MODIFY_CARD_RESQUEST:
            _HandleModifyGroupCardRequest(pdu);
            break;
        case base::CID_GROUP_SEARCH_GROUP_REQUEST:
            _HandleSearchGroupRequest(pdu);
            break;
        case base::CID_GROUP_ADD_GROUP_REQUEST:
            _HandleAddGroupRequest(pdu);
            break;
        case base::CID_FILE_REQUEST:
            _HandleClientFileRequest(pdu);
            break;
        case base::CID_MESSAGE_GET_OFFLINE_MESSAGE_REQUEST:
            _HandleOfflineMessageDataRequest(pdu);
            break;
        case base::CID_OTHER_MODIFY_INFORMATION_REQUEST:
            _HandleModifyInformation(pdu);
            break;
        case base::CID_OTHER_MODIFY_USER_HEADER_REQUEST:
            _HandleModifyUserIcon(pdu);
            break;
        case base::CID_GROUP_GET_LATEST_MSG_ID_REQUEST:
            _HandleGetGroupLatestMsgIdRequest(pdu);
            break;
        case base::CID_GROUP_EXIT_GROUP_REQUEST:
            _HandleExitGroupRequest(pdu);
            break;
        case base::CID_GROUP_MODIFY_HEADER_REQUEST:
            _HandleGroupHeaderRequest(pdu);
            break;
        case base::CID_GROUP_SET_MANAGER_REQUEST:
            _HandleSetManagerRequest(pdu);
            break;
        case base::CID_GROUP_KICK_OUT_REQUEST:
            _HandleKickOutMemberRequest(pdu);
            break;
        case base::CID_SESSIONLIST_ADD_SESSION_REQUEST:
            _HandleCreateNewSessionRequest(pdu);
            break;
        case base::CID_GROUP_VERIFY_RESULT:
            _HandleGroupVerifyResult(pdu);
            break;
        case base::CID_OTHER_GET_FRIEND_INFORMATION_REQUEST:
            _HandleGetFriendInformationRequest(pdu);
            break;
        case base::CID_GROUP_GET_OFFLINE_MESSAGE_REQUEST:
            _HandleGetGroupOfflineMessageRequest(pdu);
            break;
        case base::CID_FILE_GET_OFFLINE_FILE_REQUEST:
            _HandleGetOfflineFileRequest(pdu);
            break;
        default:
            std::cout << pdu->getCID() << std::endl;
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
//    log("received heartbeat!");
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

    log("用户%d注销请求", userId);

    if (user != nullptr)
    {
        auto conn = user->getConn();
        UserManager::instance()->removerUser(userId);
        conn->onClose();
    }

    //发送到路由服务器
    server::UserGoOffline userGoOffline;
    userGoOffline.set_user_id(userId);

    RouteConn *routeConn = get_route_server_conn();
    if (routeConn)
        sendMessage(routeConn, userGoOffline, base::SID_SERVER, base::CID_SERVER_USER_GO_OFFLINE);

//    DBServConn *dbServConn = get_db_server_conn();
//
//    if (dbServConn)
//    {
//        server::UserOffline userOffline;
//        userOffline.set_user_id(userId);
//        BasePdu basePdu;
//        basePdu.setSID(base::SID_SERVER);
//        basePdu.setCID(base::CID_SERVER_USER_LOGOUT);
//        basePdu.writeMessage(&userOffline);
//        dbServConn->sendBasePdu(&basePdu);
//    }
//
//    //发送好友下线通知
//    server::RouteStatusChange routeMessage;
//    routeMessage.set_user_id(m_user_id);
//    routeMessage.set_route_status_type(base::ROUTE_MESSAGE_FRIEND_STATUS_CHANGE);
//    set_attach_data(routeMessage, base::USER_STATUS_OFFLINE);
//
//    BasePdu basePdu1;
//    basePdu1.setSID(base::SID_SERVER);
//    basePdu1.setCID(base::CID_SERVER_ROUTE_BROADCAST);
//    basePdu1.writeMessage(&routeMessage);
//
//    auto routeConn = get_route_server_conn();
//
//    if (routeConn)
//        routeConn->sendBasePdu(&basePdu1);


}


void ClientConn::_HandleUserRegisterRequest(BasePdu *pdu)
{
    login::UserRegisterRequest request;
    request.ParseFromString(pdu->getMessage());

    std::string nickName = request.nick_name();
    std::string password = request.password();
    std::string image    = request.header();

    request.set_handle(m_handle);

    DBServConn *conn = get_db_server_conn();
    if (conn)
    {
        sendMessage(conn, request, base::SID_SERVER, base::CID_LOGIN_REGISTER_REQUEST);
    }
}

void ClientConn::_HandleMessageDataRequest(BasePdu *pdu)
{
    message::MessageData messageData;
    messageData.ParseFromString(pdu->getMessage());

    uint32_t toUserID = messageData.to_id();

    base::MessageType messageType = messageData.message_type();

    log("用户%d发送消息到用户%d", messageData.from_user_id(), toUserID);

    //将消息发送到数据库服务器。 消息状态记为未读
    DBServConn *dbServConn = get_db_server_conn();
    if (!dbServConn)
        return;
    sendMessage(dbServConn, messageData, base::SID_SERVER, base::CID_MESSAGE_SAVE);

    if (messageType == base::MESSAGE_TYPE_SINGLE_TEXT || messageType == base::MESSAGE_TYPE_SINGLE_AUDIO)
    {
        User *user = UserManager::instance()->getUser(toUserID);
        //路由转发
        if (user == nullptr)
        {
            //接收者不在当前服务器,或者未登录.
            //将消息转发到路由服务器。
            server::RouteMessageForward routeMessageForward;
            routeMessageForward.set_user_id(getUserId());
            routeMessageForward.set_friend_id(toUserID);
            routeMessageForward.set_create_time(messageData.create_time());
            routeMessageForward.set_msg_id(messageData.msg_id());
            routeMessageForward.set_message_type(messageData.message_type());
            routeMessageForward.set_message_data(messageData.message_data());

            RouteConn *routeConn = get_route_server_conn();

            if (!routeConn)
                return;
            sendMessage(routeConn, routeMessageForward, base::SID_SERVER, base::CID_SERVER_ROUTE_MESSAGE);
        }
        else
        {
            //接受者在当前服务器登录
            //将消息转发到客户端，收到客户端已读请求后将消息状态改为已读
            auto conn = user->getConn();
            if (conn)
                sendMessage(conn, messageData, base::SID_MESSAGE, base::CID_MESSAGE_DATA);
        }
    }
    else if (messageType == base::MESSAGE_TYPE_GROUP_TEXT || messageType == base::MESSAGE_TYPE_GROUP_AUDIO)
    {
        //群组消息
        //直接转发路由
        RouteConn *routeConn = get_route_server_conn();

        if (!routeConn)
            return;
        sendMessage(routeConn, messageData, base::SID_SERVER, base::CID_SERVER_FORWARD_GROUP_MESSAGE);
    }


}


void ClientConn::_HandleMessageDataAck(BasePdu *pdu)
{
    message::MessageDataAck ack;
    ack.ParseFromString(pdu->getMessage());

    log("收到消息已读确认请求");

    DBServConn *conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, ack, base::SID_MESSAGE, base::CID_MESSAGE_DATA_ACK);
}


void ClientConn::_HandleOfflineMessageDataRequest(BasePdu *basePdu)
{
    message::GetOfflineMessageRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId = request.user_id();
    log("用户%d请求离线消息", userId);

    DBServConn *conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_MESSAGE, base::CID_MESSAGE_GET_OFFLINE_MESSAGE_REQUEST);
}


void ClientConn::_HandleSignatureChangeRequest(BasePdu *pdu)
{
    friendlist::SignatureChangeResquest signatureChangeResquest;
    signatureChangeResquest.ParseFromString(pdu->getMessage());

    log("用户%d修改个性签名为: %s", signatureChangeResquest.user_id(), signatureChangeResquest.user_signature().c_str());

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


void ClientConn::_HandleRenameFriendGroupRequest(BasePdu *pdu)
{
    friendlist::RenameFriendGroupRequest renameFriendGroupRequest;
    renameFriendGroupRequest.ParseFromString(pdu->getMessage());

    log("用户%d请求重命名好友分组", renameFriendGroupRequest.user_id());

    BasePdu basePdu;
    basePdu.setSID(base::SID_SERVER);
    basePdu.setCID(base::CID_FRIENDLIST_RENAME_FRIEND_GROUP_REQUEST);
    basePdu.writeMessage(&renameFriendGroupRequest);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
        dbServConn->sendBasePdu(&basePdu);
}


void ClientConn::_HandleDeleteFriendGroupRequest(BasePdu *pdu)
{
    friendlist::DeleteFriendGroupRequest deleteFriendGroupRequest;
    deleteFriendGroupRequest.ParseFromString(pdu->getMessage());

    log("用户%d请求删除好友分组", deleteFriendGroupRequest.user_id());

    BasePdu basePdu;
    basePdu.setSID(base::SID_SERVER);
    basePdu.setCID(base::CID_FRIENDLIST_DELETE_FRIEND_GROUP_REQUEST);
    basePdu.writeMessage(&deleteFriendGroupRequest);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
        dbServConn->sendBasePdu(&basePdu);
}


void ClientConn::_HandleMoveFriendToGroupRequest(BasePdu *pdu)
{
    friendlist::MoveFriendToGroupRequest moveFriendToGroupRequest;
    moveFriendToGroupRequest.ParseFromString(pdu->getMessage());

    log("用户%d请求将好友%d移动到分组%d", moveFriendToGroupRequest.user_id(), moveFriendToGroupRequest.friend_id(), moveFriendToGroupRequest.group_id());

    BasePdu basePdu;
    basePdu.setSID(base::SID_SERVER);
    basePdu.setCID(base::CID_FRIENDLIST_MOVE_FRIEND_TO_GROUP_REQUEST);
    basePdu.writeMessage(&moveFriendToGroupRequest);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
        dbServConn->sendBasePdu(&basePdu);
}


void ClientConn::_HandleDeleteFriendRequest(BasePdu *pdu)
{
    friendlist::DeleteFriendRequest deleteFriendRequest;
    deleteFriendRequest.ParseFromString(pdu->getMessage());

    log("用户%d请求删除好友%d", deleteFriendRequest.user_id(), deleteFriendRequest.friend_id());

    BasePdu basePdu;
    basePdu.setSID(base::SID_SERVER);
    basePdu.setCID(base::CID_FRIENDLIST_DELETE_FRIEND_REQUEST);
    basePdu.writeMessage(&deleteFriendRequest);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
        dbServConn->sendBasePdu(&basePdu);
}

void ClientConn::_HandleModifyFriendRemarkRequest(BasePdu *pdu)
{
    friendlist::ModifyFriendRemarkRequest request;
    request.ParseFromString(pdu->getMessage());

    log("用户%d请求修改好友%d的备注名为%s", request.user_id(), request.friend_id(), request.friend_remark().c_str());

    BasePdu basePdu;
    basePdu.setSID(base::SID_SERVER);
    basePdu.setCID(base::CID_FRIENDLIST_MODIFY_FRIEND_REMARK_RQUEST);
    basePdu.writeMessage(&request);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
        dbServConn->sendBasePdu(&basePdu);
}

void ClientConn::_HandleGetSessionsRequest(BasePdu *pdu)
{
    session::GetSessionsRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.userid();
    log("用户%d请求session列表", userId);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
        sendMessage(dbServConn, request, base::SID_SERVER, base::CID_SESSIONLIST_GET_SESSIONS_REQUEST);
}

void ClientConn::_HandleDeleteSessionRequest(BasePdu *pdu)
{
    session::DeleteSessionRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t sessionId = request.session_id();
    log("用户%d请求删除session %d", userId, sessionId);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
        sendMessage(dbServConn, request, base::SID_SERVER, base::CID_SESSIONLIST_DEL_SESSION);
}

void ClientConn::_HandleTopSessionRequest(BasePdu *pdu)
{
    session::TopSessionRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t sessionId = request.session_id();
    log("用户%d请求(取消)置顶session %d", userId, sessionId);

    DBServConn *dbServConn = get_db_server_conn();

    if (dbServConn)
        sendMessage(dbServConn, request, base::SID_SERVER, base::CID_SESSIONLIST_TOP_SESSION);
}


void ClientConn::_HandleCreateNewSessionRequest(BasePdu *pdu)
{
    session::CreateNewSession request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();

    log("用户%d请求创建新的Session");

    DBServConn *dbServConn = get_db_server_conn();
    if (dbServConn)
        sendMessage(dbServConn, request, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION_REQUEST);
}


void ClientConn::_HandleSearchFriendRequest(BasePdu *pdu)
{
    friendlist::SearchFriendRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();
    std::string searchData = request.search_data();
    base::SearchType searchType = request.search_type();

    log("用户%d请求搜索：%s，搜索类型为%d", userId, searchData, searchType);

    DBServConn *dbServConn = get_db_server_conn();
    if (dbServConn)
        sendMessage(dbServConn, request, base::SID_SERVER, base::CID_FRIENDLIST_SEARCH_FRIEND_REQUEST);
}


void ClientConn::_HandleAddFriendRequest(BasePdu *pdu)
{
    friendlist::AddFriendRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t friendId = request.friend_id();
    uint32_t groupId = request.group_id();
    std::string reamark = request.friend_remark();
    std::string validateData = request.validatedata();

    //send to dbServer
    auto dbConn = get_db_server_conn();
    if (!dbConn)
        return;
    sendMessage(dbConn, request, base::SID_SERVER, base::CID_FRIENDLIST_ADD_FRIEND_REQUEST);

    //if friend not in this msgServer then send to routeServer
    auto user = UserManager::instance()->getUser(friendId);
    if (user)
    {
        auto conn = user->getConn();
        if (conn)
        {
            sendMessage(conn, request, base::SID_FRIEND_LIST, base::CID_FRIENDLIST_ADD_FRIEND_REQUEST);
            return;
        }
    }

    //send to routeServer

}


void ClientConn::_HandleGetLatestMsgIdRequest(BasePdu *pdu)
{
    message::LatestMsgIdRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t friendId = request.friend_id();

    log("用户%d请求获取与好友%d的最新消息ID", userId, friendId);

    //send to dbServer
    auto dbConn = get_db_server_conn();
    if (!dbConn)
        return;
    sendMessage(dbConn, request, base::SID_SERVER, base::CID_MESSAGE_GET_LATEST_MSG_ID_REQUEST);
}


void ClientConn::_HandleGetLatestMsgIdRespone(BasePdu *pdu)
{
    friendlist::AddFriendRespone respone;
    respone.ParseFromString(pdu->getMessage());

    uint32_t userId = respone.user_id();
    uint32_t friendId = respone.friend_id();
    uint32_t resultId = respone.result_id();
    uint32_t groupId = respone.group_id();
    std::string remark = respone.remark();

    std::string result;
    if (resultId == 1)
        result = "同意";
    else if (resultId == 2)
        result = "拒绝";
    else if (resultId == 3)
        result = "忽略";

    log("用户%d %s 了用户%d的好友申请", userId, result.c_str(), friendId);

    //通知用户
    if (resultId != 3)
    {
        auto user = UserManager::instance()->getUser(friendId);
        if (user)
        {
            auto conn = user->getConn();
            if (conn)
            {
                sendMessage(conn, respone, base::SID_FRIEND_LIST, base::CID_FRIENDLIST_ADD_FRIEND_RESPONE);
            }
        }
        else
        {
            //查询路由服务器
        }
    }

    //处理结果保存到数据库
    auto dbConn = get_db_server_conn();
    if (dbConn)
    {
        sendMessage(dbConn, respone, base::SID_SERVER, base::CID_FRIENDLIST_ADD_FRIEND_RESPONE);
    }
}


void ClientConn::_HandlerGetAddRequestHistoryRequest(BasePdu *pdu)
{
    friendlist::GetAddRequestHistoryRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();
    log("用户%d请求获取历史好友申请记录", userId);

    auto dbConn = get_db_server_conn();
    if (dbConn)
    {
        sendMessage(dbConn, request, base::SID_SERVER, base::CID_FRIENDLIST_GET_REQUEST_HISTORY_REQUEST);
    }
}


void ClientConn::_HandleGroupVerifyResult(BasePdu *pdu)
{
    group::VerifyHandlerResult result;
    result.ParseFromString(pdu->getMessage());

    uint32_t userId = result.handle_user_id();
    uint32_t requestId = result.request_user_id();
    log("用户%d处理了用户%d的入群申请", userId, requestId);

    auto dbConn = get_db_server_conn();
    if (dbConn)
    {
        sendMessage(dbConn, result, base::SID_SERVER, base::CID_GROUP_VERIFY_RESULT);
    }
}


void ClientConn::_HandleCreatGroupRequest(BasePdu *basePdu)
{
    group::GroupCreateRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId = request.user_id();
    std::string groupName = request.group_name();
    uint32_t groupMaxMembers = request.group_max_members();

    log("用户%d请求创建群组，群名：%s 最大成员数为%d", userId, groupName.c_str(), groupMaxMembers);

    auto conn = get_db_server_conn();
    if (conn)
    {
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_CREATE_REQUEST);
    }
}


void ClientConn::_HandleGetGroupListRequest(BasePdu *pdu)
{
    group::GetGroupListRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();

    log("用户%d请求群组list", userId);

    auto conn = get_db_server_conn();
    if (conn)
    {
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_GET_LIST_REQUEST);
    }
}


void ClientConn::_HandleGetGroupMemberRequest(BasePdu *basePdu)
{
    group::GetGroupMemberInfoRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t groupId = request.group_id();
    log("用户%d请求获取群%d的成员信息", userId, groupId);

    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_GET_MEMBER_REQUEST);
}

void ClientConn::_HandleModifyGroupCardRequest(BasePdu *basePdu)
{
    group::ModifyGroupCard request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t groupId = request.group_id();
    std::string groupCard = request.group_card();

    log("用户%d请求修改群%d的群名片为%s", userId, groupId, groupCard.c_str());

    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_MODIFY_CARD_RESQUEST);
}


void ClientConn::_HandleSearchGroupRequest(BasePdu *basePdu)
{
    group::SearchGroupRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId = request.user_id();
    base::SearchType type = request.search_type();
    std::string searchData = request.search_data();
    log("用户%d 以%d方式搜索%s", userId, type, searchData.c_str());

    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_SEARCH_GROUP_REQUEST);
}


void ClientConn::_HandleAddGroupRequest(BasePdu *basePdu)
{
    group::AddGroupRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t groupId = request.group_id();
    std::string verifyData = request.verify_data();

    log("用户%d请求加入群%d, 验证信息:%s", userId, groupId, verifyData);


    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_ADD_GROUP_REQUEST);
}


void ClientConn::_HandleGetGroupLatestMsgIdRequest(BasePdu *basePdu)
{
    group::GetLatestGroupMsgIdRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t groupId = request.group_id();

    log("用户%d请求获取群组%d最新消息ID", userId, groupId);

    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_GET_LATEST_MSG_ID_REQUEST);
}


void ClientConn::_HandleExitGroupRequest(BasePdu *basePdu)
{
    group::ExitGroupRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t groupId = request.group_id();

    log("用户%d请求退出群组%d", userId, groupId);

    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_EXIT_GROUP_REQUEST);
}

void ClientConn::_HandleGroupHeaderRequest(BasePdu *basePdu)
{
    group::ModifyGroupHeaderRequest request;
    request.ParseFromString(basePdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t groupId = request.group_id();

    log("用户%d请求更换群组%d的头像", userId, groupId);

    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_MODIFY_HEADER_REQUEST);
}


void ClientConn::_HandleSetManagerRequest(BasePdu *pdu)
{
    group::SetGroupManagerRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t member = request.member_id();
    uint32_t groupId = request.group_id();

    log("用户%d将用户%d设置为群组%d的管理员", userId, member, groupId);

    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_SET_MANAGER_REQUEST);

}

void ClientConn::_HandleKickOutMemberRequest(BasePdu *pdu)
{
    group::KickOutMemberRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();
    uint32_t member = request.member_id();
    uint32_t groupId = request.group_id();

    log("用户%d将用户%d踢出群组%d", userId, member, groupId);


    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_KICK_OUT_REQUEST);

}


void ClientConn::_HandleGetGroupOfflineMessageRequest(BasePdu *pdu)
{
    message::GetGroupOfflineMessageRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();

    log("用户%d请求群组离线消息", userId);

    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_GROUP_GET_OFFLINE_MESSAGE_REQUEST);
}



void ClientConn::_HandleClientFileRequest(BasePdu *pdu)
{
    file::SendFileRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t fromId = request.from_user_id();
    uint32_t toId = request.to_user_id();
    std::string fileName = request.file_name();
    uint32_t fileSize = request.file_size();
    base::TransferFileType type = request.trans_mode();

    log("收到来自用户%d的传输文件请求.接受者:%d, 文件名：%s, 文件大小:%d, 传输模式:%d", fromId, toId, fileName.c_str(), fileSize, type);
    FileServerConn *conn = get_random_file_server_conn();
    if (conn)
    {
        server::FileTransferRequest request1;
        request1.set_from_user_id(fromId);
        request1.set_to_user_id(toId);
        request1.set_file_name(fileName);
        request1.set_file_size(fileSize);
        request1.set_trans_mode(type);

        //离线文件，直接发送到文件服务器
        if (type == base::FILE_TYPE_OFFLINE)
            sendMessage(conn, request1, base::SID_SERVER, base::CID_SERVER_FILE_TRANSFER_REQUEST);
        else
        {
            //在线文件
            auto user = UserManager::instance()->getUser(toId);
            //用户当前服务器登录
            if (user)
                sendMessage(conn, request1, base::SID_SERVER, base::CID_SERVER_FILE_TRANSFER_REQUEST);
            else
            {
               //用户未在当前服务器登录，查询路由服务器

            }
        }

    }
    else
    {
        //无可用的消息服务器
        file::SendFileRespone respone;
        respone.set_result_code(1);
        respone.set_from_user_id(fromId);
        respone.set_to_user_id(toId);
        respone.set_file_name(fileName);
        respone.set_trans_mode(type);
        respone.set_task_id("");

        BasePdu basePdu;
        basePdu.setSID(base::SID_FILE);
        basePdu.setCID(base::CID_SERVER_FILE_TRANSFER_RESPONE);
        basePdu.writeMessage(&respone);
        sendBasePdu(&basePdu);

    }
}


void ClientConn::_HandleGetOfflineFileRequest(BasePdu *pdu)
{
    file::GetOfflineFileRequest request;
    request.ParseFromString(pdu->getMessage());

    auto conn = get_db_server_conn();
    if (conn)
        sendMessage(conn, request, base::SID_SERVER, base::CID_FILE_GET_OFFLINE_FILE_REQUEST);


}

//修改资料
void ClientConn::_HandleModifyInformation(BasePdu *pdu)
{
    other::ModifyInformationRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();

    log("用户%d请求修改资料", userId);

    DBServConn *dbServConn = get_db_server_conn();
    if (dbServConn)
        sendMessage(dbServConn, request, base::SID_OTHER, base::CID_OTHER_MODIFY_INFORMATION_REQUEST);
}


void ClientConn::_HandleModifyUserIcon(BasePdu *pdu)
{
    other::ModifyUserImageRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();

    log("用户%d请求修改头像", userId);

    DBServConn *dbServConn = get_db_server_conn();
    if (dbServConn)
        sendMessage(dbServConn, request, base::SID_OTHER, base::CID_OTHER_MODIFY_USER_HEADER_REQUEST);
}


void ClientConn::_HandleGetFriendInformationRequest(BasePdu *pdu)
{
    other::GetFriendInformationRequest request;
    request.ParseFromString(pdu->getMessage());

    uint32_t userId = request.user_id();
    log("用户%d请求好友信息", userId);


    DBServConn *dbServConn = get_db_server_conn();
    if (dbServConn)
        sendMessage(dbServConn, request, base::SID_SERVER, base::CID_OTHER_GET_FRIEND_INFORMATION_REQUEST);
}