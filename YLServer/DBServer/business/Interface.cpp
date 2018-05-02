//
// Created by liuzheng on 18-3-25.
//

#include "Interface.h"
#include "../ProxyConn.h"
#include "LoginModel.h"
#include "FriendListModel.h"
#include "MessageModel.h"
#include "util/util.h"
#include "../CachePool.h"
#include "SessionModel.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "pdu/protobuf/youliao.message.pb.h"
#include "pdu/protobuf/youliao.session.pb.h"


namespace DB_INTERFACE
{
    void login(BasePdu *basePdu, uint32_t conn_uuid)
    {
        server::ValidateRequest validateRequest;
        validateRequest.ParseFromString(basePdu->getMessage());

        server::ValidateRespone validateRespone;
        validateRespone.set_attach_data(validateRequest.attach_data());

        LoginModel loginModel;

        base::UserInfo *userInfo = new base::UserInfo;
        if (loginModel.doLogin(validateRequest.user_name(), validateRequest.user_pwd(), *userInfo))
        {
            //将其登录状态保存到redis, 格式为user_id : msg_serv_id
            auto conn = CacheManager::instance()->getCacheConn("OnlineUser");
            conn->hset("user_map", to_string(userInfo->user_id()), to_string(validateRequest.msg_serv_id()));

            CacheManager::instance()->releaseCacheConn(conn);

            validateRespone.set_user_name(validateRequest.user_name());
            validateRespone.set_result_code(0);
            validateRespone.set_result_string("登录成功");
            validateRespone.set_allocated_user_info(userInfo);
            log("user %s login success!", validateRequest.user_name().c_str());
        }
        else
        {
            validateRespone.set_result_code(1);
            validateRespone.set_result_string("登录失败， 用户名或密码错误！");

            log("user %s login failed!", validateRequest.user_name().c_str());
        }

        BasePdu *pdu1 = new BasePdu;
        pdu1->setSID(base::SID_OTHER);
        pdu1->setCID(base::CID_SERVER_VALIDATE_RESPONE);
        pdu1->writeMessage(&validateRespone);

//        sendBasePdu(pdu1);
        findProxyConn(conn_uuid)->sendBasePdu(pdu1);
        delete pdu1;
        //add to thread pool
    }

    void getFriendGroups(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::GroupsRequest groupsRequest;
        groupsRequest.ParseFromString(basePdu->getMessage());

        uint32_t userId = groupsRequest.user_id();

        friendlist::GroupsRespone groupsRespone;
        groupsRespone.set_user_id(userId);

        FriendListModel *friendListModel = FriendListModel::instance();
        friendListModel->getGroups(userId, groupsRespone);

        BasePdu basePdu1;
        basePdu1.setSID(base::SID_SERVER);
        basePdu1.setCID(base::CID_FRIENDLIST_GET_GROUPS_REPSONE);
        basePdu1.writeMessage(&groupsRespone);

        log("send user %d groups to msg_server", userId);
        findProxyConn(conn_uid)->sendBasePdu(&basePdu1);
    }

    void getFriendList(BasePdu* basePdu, uint32_t conn_uuid)
    {
        friendlist::FriendListRequest friendListRequest;
        friendListRequest.ParseFromString(basePdu->getMessage());

        friendlist::FriendListRespone friendListRespone;
        friendListRespone.set_attach_data(friendListRequest.attach_data());

        FriendListModel *friendListModel = FriendListModel::instance() ;
        friendListModel->getFriendList(friendListRequest.user_id(), friendListRequest.msg_serv_idx(), friendListRespone);

        BasePdu *pdu = new BasePdu;
        pdu->setSID(base::SID_FRIEND_LIST);
        pdu->setCID(base::CID_FRIENDLIST_GET_RESPONE);
        pdu->writeMessage(&friendListRespone);

        findProxyConn(conn_uuid)->sendBasePdu(pdu);
        delete pdu;
    }

    void logout(BasePdu* basePdu, uint32_t conn_uid)
    {
        server::UserOffline userOffline;
        userOffline.ParseFromString(basePdu->getMessage());

        uint32_t userId = userOffline.user_id();

        LoginModel loginModel;
        loginModel.doLogout(userId);
    }


    void getOnlineFriends(BasePdu *basePdu, uint32_t conn_uuid)
    {
        server::RouteGetOnlineFirendRequest routeGetOnlineFirendRequest;
        routeGetOnlineFirendRequest.ParseFromString(basePdu->getMessage());

        uint32_t userId = routeGetOnlineFirendRequest.user_id();

        server::RouteGetOnlineFriendRespone routeGetOnlineFriendRespone;
        routeGetOnlineFriendRespone.set_user_id(userId);
        routeGetOnlineFriendRespone.set_route_status_type(routeGetOnlineFirendRequest.route_status_type());
        routeGetOnlineFriendRespone.set_attach_data(routeGetOnlineFirendRequest.attach_data());

        FriendListModel *friendListModel = FriendListModel::instance() ;
        friendListModel->getOnlineFriends(userId, routeGetOnlineFriendRespone);

        BasePdu basePdu1;
        basePdu1.setSID(base::SID_SERVER);
        basePdu1.setCID(base::CID_SERVER_GET_ONLINE_FRIENDS_RESPONE);
        basePdu1.writeMessage(&routeGetOnlineFriendRespone);

        findProxyConn(conn_uuid)->sendBasePdu(&basePdu1);
    }


    void modifySignature(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::SignatureChangeResquest signatureChangeResquest;
        signatureChangeResquest.ParseFromString(basePdu->getMessage());

        uint32_t userId = signatureChangeResquest.user_id();
        string userSignature = signatureChangeResquest.user_signature();

        FriendListModel *friendListModel = FriendListModel::instance() ;
        bool ret = friendListModel->modifySignature(userId, userSignature);

        friendlist::SignatureChangeRespone signatureChangeRespone;
        signatureChangeRespone.set_user_id(userId);

        if (ret)
        {
            signatureChangeRespone.set_result_type(base::NONE);
            signatureChangeRespone.set_user_signature(userSignature);
        }
        else
        {
            signatureChangeRespone.set_result_type(base::SIGNATURE_MODIFY_FAILED);
        }
        BasePdu basePdu1;
        basePdu1.setSID(base::SID_SERVER);
        basePdu1.setCID(base::CID_FRIENDLIST_SIGNATURE_CHANGED_RESPONE);
        basePdu1.writeMessage(&signatureChangeRespone);

        log("send user %d modify signature result to msg_server", userId);
        findProxyConn(conn_uid)->sendBasePdu(&basePdu1);
    }

    void addFriendGroup(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::AddNewFriendGroupRequest addNewFriendGroupRequest;
        addNewFriendGroupRequest.ParseFromString(basePdu->getMessage());

        uint32_t groupId;
        uint32_t userId = addNewFriendGroupRequest.user_id();
        string newGroupName = addNewFriendGroupRequest.new_group_name();

        FriendListModel *friendListModel = FriendListModel::instance() ;
        if (friendListModel->addNewFriendGroup(userId, newGroupName, groupId))
        {
            //添加成功
            friendlist::AddNewFriendGroupRespone addNewFriendGroupRespone;

            addNewFriendGroupRespone.set_user_id(userId);
            addNewFriendGroupRespone.set_group_id(groupId);
            addNewFriendGroupRespone.set_group_name(newGroupName);

            BasePdu basePdu1;
            basePdu1.setSID(base::SID_SERVER);
            basePdu1.setCID(base::CID_FRIENDLIST_ADD_FRIEND_GROUP_RESPONE);
            basePdu1.writeMessage(&addNewFriendGroupRespone);

            log("send user %d add new friend group result to msg_server", userId);
            findProxyConn(conn_uid)->sendBasePdu(&basePdu1);
        }
        //否则丢弃该请求，

    }

    void renameFriendGroup(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::RenameFriendGroupRequest renameFriendGroupRequest;
        renameFriendGroupRequest.ParseFromString(basePdu->getMessage());

        uint32_t userId = renameFriendGroupRequest.user_id();
        uint32_t groupId = renameFriendGroupRequest.group_id();
        string groupNewName = renameFriendGroupRequest.group_new_name();

        FriendListModel *friendListModel = FriendListModel::instance() ;
        friendListModel->renameFriendGroup(userId, groupNewName, groupId);
    }

    //删除分组
    void deleteFriendGroup(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::DeleteFriendGroupRequest deleteFriendGroupRequest;
        deleteFriendGroupRequest.ParseFromString(basePdu->getMessage());

        uint32_t userId = deleteFriendGroupRequest.user_id();
        uint32_t groupId = deleteFriendGroupRequest.group_id();

        FriendListModel *friendListModel = FriendListModel::instance() ;
        friendListModel->deleteFriendGroup(userId, groupId);
    }

    //移动好友到指定分组
    void moveFriendToGroup(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::MoveFriendToGroupRequest request;
        request.ParseFromString(basePdu->getMessage());

        FriendListModel *friendListModel = FriendListModel::instance() ;
        friendListModel->moveFriendToGroup(request.user_id(), request.friend_id(), request.group_id());
    }

    //删除好友
    void deleteFriend(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::DeleteFriendRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t friendId = request.friend_id();

        FriendListModel *friendListModel = FriendListModel::instance() ;
        friendListModel->deleteFriend(userId, friendId);
    }

    //修改好友备注
    void modifyFriendRemark(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::ModifyFriendRemarkRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t friendId = request.friend_id();
        string friendRemark = request.friend_remark();

        FriendListModel *friendListModel = FriendListModel::instance() ;
        friendListModel->modifyFriendRemark(userId, friendId, friendRemark);
    }



    //获取好友状态
    void getOnlineFriendStatus(BasePdu *basePdu, uint32_t conn_uid)
    {
        server::RouteGetFriendOnlineStatus routeGetFriendOnlineStatus;
        routeGetFriendOnlineStatus.ParseFromString(basePdu->getMessage());

        MessageModel *messageModel = MessageModel::instance();

        int msgIdx = 0;

        if(messageModel->getFriendOnlineStatus(routeGetFriendOnlineStatus.friend_id(), msgIdx))
        {
            if (msgIdx != 0)
            {
                server::RouteGetFriendOnlineStatus reply;
                reply.set_user_id(routeGetFriendOnlineStatus.user_id());
                reply.set_friend_id(routeGetFriendOnlineStatus.friend_id());
                reply.set_msg_id(routeGetFriendOnlineStatus.msg_id());
                reply.set_create_time(routeGetFriendOnlineStatus.create_time());
                reply.set_message_data(routeGetFriendOnlineStatus.message_data());
                reply.set_msg_idx(msgIdx);
                reply.set_message_type(routeGetFriendOnlineStatus.message_type());

                BasePdu basePdu1;
                basePdu1.setSID(base::SID_SERVER);
                basePdu1.setCID(base::CID_SERVER_GET_FRIEND_ONLINE_STATUS);
                basePdu1.writeMessage(&reply);

                findProxyConn(conn_uid)->sendBasePdu(&basePdu1);
            }

            //消息服务器ID错误。忽略
        }

        //不在线。忽略

    }


    //保存消息记录
    void saveMessage(BasePdu *basePdu, uint32_t conn_uuid)
    {
        message::MessageData msg;
        if(msg.ParseFromString(basePdu->getMessage()))
        {
            uint32_t senderId = msg.from_user_id();
            uint32_t receiverId = msg.to_user_id();
            uint32_t createdTime = msg.create_time();
            base::MessageType msgType = msg.message_type();
            uint32_t msgLen = msg.message_data().length();
            uint32_t msgId = msg.msg_id();
            if (base::MessageType_IsValid(msgType))
            {
                if (msgLen > 0)
                {
                    MessageModel *messageModel = MessageModel::instance();
                    //[1] 更新sender和receiver的session
                    //[2] 保存消息
                    // 一条消息要保存两份。 发送者和接受者各一份
                    uint32_t senderRelatedId = FriendListModel::instance()->getRelationId(senderId, receiverId);
                    uint32_t receiverRelatedId = FriendListModel::instance()->getRelationId(receiverId, senderId);

                    if (senderRelatedId == 0 || receiverRelatedId == 0)
                    {
                        //两者不是互为好友的关系。消息不予保存。
                        return;
                    }

                    uint32_t senderSessionId = SessionModel::instance()->getSessionId(senderId, receiverId, base::SESSION_TYPE_SINGLE);
                    //Session不存在。  (从未添加过改Session)
                    if (senderSessionId == 0)
                    {
                        senderSessionId = SessionModel::instance()->addSession(senderId, receiverId, base::SESSION_TYPE_SINGLE);
                        //新增session转发到客户端
                        session::NewSessionRespone respone;
                        respone.set_user_id(senderId);
                        respone.set_other_id(receiverId);
                        respone.set_session_id(senderSessionId);
                        respone.set_session_type(base::SESSION_TYPE_SINGLE);
                        auto conn = findProxyConn(conn_uuid);
                        if (conn)
                            sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);
                    }
                    uint32_t receiverSessionId = SessionModel::instance()->getSessionId(receiverId, senderId, base::SESSION_TYPE_SINGLE);
                    if (receiverSessionId == 0)
                    {
                        receiverSessionId = SessionModel::instance()->addSession(receiverId, senderId, base::SESSION_TYPE_SINGLE);
                        //新增session转发到客户端
                        session::NewSessionRespone respone;
                        respone.set_user_id(receiverId);
                        respone.set_other_id(senderId);
                        respone.set_session_id(receiverId);
                        respone.set_session_type(base::SESSION_TYPE_SINGLE);
                        auto conn = findProxyConn(conn_uuid);
                        if (conn)
                            sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);
                    }


                    if (msgType == base::MESSAGE_TYPE_SINGLE_TEXT)
                    {

                        //保存消息到数据库
                        messageModel->saveMessage(senderRelatedId, senderId, receiverId, msgType, createdTime, msgId, msg.message_data());
                        messageModel->saveMessage(receiverRelatedId, senderId, receiverId, msgType, createdTime, msgId, msg.message_data());
                        //更新session
                        SessionModel::instance()->updateSession(senderSessionId);
                        SessionModel::instance()->updateSession(receiverSessionId);
                    }
                }
                else
                {
                    log("消息长度错误! senderId=%u, receiverId=%u, type=%u", senderId, receiverId, msgType);
                }
            }
            else
            {
                log("无效的MessageType! senderId=%u, receiverId=%u, type=%u", senderId, receiverId, msgType);
            }

        }
        else
        {
            log("解析PDU失败！");
        }
    }


    void getLatestMsgId(BasePdu *basePdu, uint32_t conn_uuid)
    {
        message::LatestMsgIdRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t friId = request.friend_id();

        uint32_t latestMsgId = 0;
        MessageModel::instance()->getLatestMsgId(userId, friId, latestMsgId);

        message::LatestMsgIdRespone respone;
        respone.set_user_id(userId);
        respone.set_friend_id(friId);
        respone.set_latest_msg_id(latestMsgId);

        auto conn = findProxyConn(conn_uuid);

        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_MESSAGE_GET_LATEST_MSG_ID_RESPONE);

    }


    //搜索好友
    void searchFriend(BasePdu *basePdu, uint32_t conn_uuid)
    {
        friendlist::SearchFriendRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        string searchData = request.search_data();
        base::SearchType searchType = request.search_type();

        list<base::FriendInfo> result;
        FriendListModel::instance()->searchFriend(searchData, searchType, result);

        friendlist::SearchFriendRespone respone;
        respone.set_user_id(userId);

        for (const auto &elem : result)
        {
            auto fri = respone.add_friends();
            (*fri) = elem;
        }

        auto conn = findProxyConn(conn_uuid);

        if (conn)
            sendMessage(conn, respone, base::SID_SESSION, base::CID_FRIENDLIST_SEARCH_FRIEND_RESPONE);
    }

    //添加好友
    void addFriend(BasePdu *basePdu, uint32_t conn_uuid)
    {
        friendlist::AddFriendRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t friendId = request.friend_id();
        uint32_t groupId = request.group_id();
        string remark = request.friend_remark();
        string validateData = request.validatedata();

        FriendListModel *friendListModel = FriendListModel::instance();

        bool ret = friendListModel->addFriend(userId, friendId, groupId, remark, validateData);

        if (!ret)
        {
            //do something
        }

    }

    void getSessions(BasePdu *basePdu, uint32_t conn_uuid)
    {
        session::GetSessionsRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.userid();

        std::list<base::SessionInfo> list;
        SessionModel::instance()->getSessions(userId, list);

        session::GetSessionReponse respone;
        respone.set_userid(userId);

        for (base::SessionInfo &sessionInfo : list)
        {
            uint32_t latestMsgId = 0;
            MessageModel::instance()->getLatestMsgId(userId, sessionInfo.other_id(), latestMsgId);
            sessionInfo.set_latest_msg_id(latestMsgId);
            auto session = respone.add_sessions();
            *session = sessionInfo;
        }

        auto conn = findProxyConn(conn_uuid);
        sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_GET_SESSIONS_RESPONE);
    }


    //删除session
    void deleteSession(BasePdu *basePdu, uint32_t conn_uid)
    {
        session::DeleteSessionRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t sessionId = request.session_id();

        SessionModel::instance()->removeSession(sessionId);

    }
    //置顶session
    void topSession(BasePdu *basePdu, uint32_t conn_uid)
    {
        session::TopSessionRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t sessionId = request.session_id();

        SessionModel::instance()->topSession(sessionId);
    }
}


