//
// Created by liuzheng on 18-3-25.
//

#include <pdu/protobuf/youliao.login.pb.h>
#include "Interface.h"
#include "../ProxyConn.h"
#include "LoginModel.h"
#include "FriendListModel.h"
#include "MessageModel.h"
#include "GroupModel.h"
#include "util/util.h"
#include "SessionModel.h"
#include "OtherModel.h"
#include "AudioModel.h"
#include "pdu/protobuf/youliao.file.pb.h"
#include "pdu/protobuf/youliao.server.pb.h"
#include "pdu/protobuf/youliao.message.pb.h"
#include "pdu/protobuf/youliao.session.pb.h"
#include "pdu/protobuf/youliao.group.pb.h"
#include "pdu/protobuf/youliao.other.pb.h"

using namespace std;

namespace DB_INTERFACE
{
    void login(BasePdu *basePdu, uint32_t conn_uuid)
    {
        server::ValidateRequest validateRequest;
        validateRequest.ParseFromString(basePdu->getMessage());

        server::ValidateRespone validateRespone;
        validateRespone.set_attach_data(validateRequest.attach_data());

        LoginModel *loginModel = LoginModel::instance();

        base::UserInfo *userInfo = new base::UserInfo;
        if (loginModel->doLogin(validateRequest.user_name(), validateRequest.user_pwd(), *userInfo))
        {
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

        findProxyConn(conn_uuid)->sendBasePdu(pdu1);
        delete pdu1;
        //add to thread pool
    }


    void registerUser(BasePdu *basePdu, uint32_t conn_uuid) {
        login::UserRegisterRequest request;
        request.ParseFromString(basePdu->getMessage());

        LoginModel *loginModel = LoginModel::instance();

        uint32_t account;

        login::UserRegisterRespone respone;
        bool ret = loginModel->doRegister(request.nick_name(), request.password(), request.header(), account);

        if (ret) {
            respone.set_result_code(0);
            respone.set_user_account(std::to_string(account));
        } else {
            respone.set_result_code(1);
        }

        respone.set_handle(request.handle());


        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_LOGIN_REGISTER_RESPONE);
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
        friendListRespone.set_user_id(friendListRequest.user_id());

        FriendListModel *friendListModel = FriendListModel::instance() ;
        friendListModel->getFriendList(friendListRequest.user_id(), friendListRequest.msg_serv_idx(), friendListRespone);

        BasePdu *pdu = new BasePdu;
        pdu->setSID(base::SID_FRIEND_LIST);
        pdu->setCID(base::CID_FRIENDLIST_GET_RESPONE);
        pdu->writeMessage(&friendListRespone);

        findProxyConn(conn_uuid)->sendBasePdu(pdu);
        delete pdu;
    }

//    void logout(BasePdu* basePdu, uint32_t conn_uid)
//    {
//        server::UserOffline userOffline;
//        userOffline.ParseFromString(basePdu->getMessage());
//
//        uint32_t userId = userOffline.user_id();
//
//        LoginModel loginModel;
//        loginModel.doLogout(userId);
//    }
//

//    void getOnlineFriends(BasePdu *basePdu, uint32_t conn_uuid)
//    {
//        server::RouteGetOnlineFirendRequest routeGetOnlineFirendRequest;
//        routeGetOnlineFirendRequest.ParseFromString(basePdu->getMessage());
//
//        uint32_t userId = routeGetOnlineFirendRequest.user_id();
//
//        server::RouteGetOnlineFriendRespone routeGetOnlineFriendRespone;
//        routeGetOnlineFriendRespone.set_user_id(userId);
//        routeGetOnlineFriendRespone.set_route_status_type(routeGetOnlineFirendRequest.route_status_type());
//        routeGetOnlineFriendRespone.set_attach_data(routeGetOnlineFirendRequest.attach_data());
//
//        FriendListModel *friendListModel = FriendListModel::instance() ;
//        friendListModel->getOnlineFriends(userId, routeGetOnlineFriendRespone);
//
//        BasePdu basePdu1;
//        basePdu1.setSID(base::SID_SERVER);
//        basePdu1.setCID(base::CID_SERVER_GET_ONLINE_FRIENDS_RESPONE);
//        basePdu1.writeMessage(&routeGetOnlineFriendRespone);
//
//        findProxyConn(conn_uuid)->sendBasePdu(&basePdu1);
//    }


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

        //删除好友
        friendListModel->deleteFriend(userId, friendId);
        friendListModel->deleteFriend(friendId, userId);

        //删除session
        SessionModel *sessionModel = SessionModel::instance()->instance();
        uint32_t sessionId = sessionModel->getSessionId(userId, friendId, base::SESSION_TYPE_SINGLE);
        if (sessionId != 0)
            sessionModel->removeSession(sessionId);
        sessionId = sessionModel->getSessionId(friendId, userId, base::SESSION_TYPE_SINGLE);
        if (sessionId != 0)
            sessionModel->removeSession(sessionId);

        //通知被删除的好友
        friendlist::DeleteFriendRespone respone;
        respone.set_user_id(friendId);
        respone.set_friend_id(userId);

        auto conn = findProxyConn(conn_uid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_FRIENDLIST_DELETE_FRIEND_RESPONE);
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



//    //获取好友状态
//    void getOnlineFriendStatus(BasePdu *basePdu, uint32_t conn_uid)
//    {
//        server::RouteGetFriendOnlineStatus routeGetFriendOnlineStatus;
//        routeGetFriendOnlineStatus.ParseFromString(basePdu->getMessage());
//
//        MessageModel *messageModel = MessageModel::instance();
//
//        int msgIdx = 0;
//
//        if(messageModel->getFriendOnlineStatus(routeGetFriendOnlineStatus.friend_id(), msgIdx))
//        {
//            if (msgIdx != 0)
//            {
//                server::RouteGetFriendOnlineStatus reply;
//                reply.set_user_id(routeGetFriendOnlineStatus.user_id());
//                reply.set_friend_id(routeGetFriendOnlineStatus.friend_id());
//                reply.set_msg_id(routeGetFriendOnlineStatus.msg_id());
//                reply.set_create_time(routeGetFriendOnlineStatus.create_time());
//                reply.set_message_data(routeGetFriendOnlineStatus.message_data());
//                reply.set_msg_idx(msgIdx);
//                reply.set_message_type(routeGetFriendOnlineStatus.message_type());
//
//                BasePdu basePdu1;
//                basePdu1.setSID(base::SID_SERVER);
//                basePdu1.setCID(base::CID_SERVER_GET_FRIEND_ONLINE_STATUS);
//                basePdu1.writeMessage(&reply);
//
//                findProxyConn(conn_uid)->sendBasePdu(&basePdu1);
//            }
//
//            //消息服务器ID错误。忽略
//        }
//
//        //不在线。忽略
//
//    }


    //保存消息记录
    void saveMessage(BasePdu *basePdu, uint32_t conn_uuid)
    {
        message::MessageData msg;
        if(msg.ParseFromString(basePdu->getMessage()))
        {
            uint32_t senderId = msg.from_user_id();
            uint32_t receiverId = msg.to_id();
            uint32_t createdTime = msg.create_time();
            base::MessageType msgType = msg.message_type();
            uint32_t msgLen = (uint32_t)msg.message_data().length();
            uint32_t msgId = msg.msg_id();

            if (base::MessageType_IsValid(msgType))
            {
                if (msgLen > 0)
                {
                    MessageModel *messageModel = MessageModel::instance();
                    if (msgType == base::MESSAGE_TYPE_SINGLE_TEXT)
                    {

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
                            base::SessionInfo *sessionInfo = new base::SessionInfo;
                            sessionInfo->set_session_type(base::SESSION_TYPE_SINGLE);
                            sessionInfo->set_latest_msg_id(msgId);
                            sessionInfo->set_last_message_data(msg.message_data());
                            sessionInfo->set_session_top(base::SESSION_FLAG_NORMAL);
                            sessionInfo->set_latest_msg_time(createdTime);
                            sessionInfo->set_session_id(senderSessionId);
                            sessionInfo->set_other_id(receiverId);

                            //新增session转发到客户端
                            session::NewSessionRespone respone;
                            respone.set_user_id(senderId);
                            respone.set_allocated_session(sessionInfo);

                            auto conn = findProxyConn(conn_uuid);
                            if (conn)
                                sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);
                        }
                        uint32_t receiverSessionId = SessionModel::instance()->getSessionId(receiverId, senderId, base::SESSION_TYPE_SINGLE);
                        if (receiverSessionId == 0)
                        {
                            receiverSessionId = SessionModel::instance()->addSession(receiverId, senderId, base::SESSION_TYPE_SINGLE);
                            base::SessionInfo *sessionInfo = new base::SessionInfo;
                            sessionInfo->set_session_type(base::SESSION_TYPE_SINGLE);
                            sessionInfo->set_latest_msg_id(msgId);
                            sessionInfo->set_last_message_data(msg.message_data());
                            sessionInfo->set_session_top(base::SESSION_FLAG_NORMAL);
                            sessionInfo->set_latest_msg_time(createdTime);
                            sessionInfo->set_session_id(receiverSessionId);
                            sessionInfo->set_other_id(senderId);

                            //新增session转发到客户端
                            session::NewSessionRespone respone;
                            respone.set_user_id(receiverId);
                            respone.set_allocated_session(sessionInfo);
                            auto conn = findProxyConn(conn_uuid);
                            if (conn)
                                sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);
                        }

                        //保存消息到数据库
                        messageModel->saveMessage(senderId, receiverId, msgType, createdTime, msgId, msg.message_data());
//                        messageModel->saveMessage(receiverRelatedId, senderId, receiverId, msgType, createdTime, msgId, msg.message_data());
                        //更新session
                        SessionModel::instance()->updateSession(senderSessionId);
                        SessionModel::instance()->updateSession(receiverSessionId);
                    }
                    else if (msgType == base::MESSAGE_TYPE_GROUP_TEXT)
                    {

                        //群组消息
                        GroupModel *groupModel = GroupModel::instance();
                        uint32_t relationId = groupModel->getRelationId(receiverId, senderId);
                        if (relationId == 0)
                        {
                            //不是该群成员
                            log("用户%d不属于群组%d", senderId, receiverId);
                            return;
                        }

                        uint32_t sessionId = SessionModel::instance()->getSessionId(senderId, receiverId, base::SESSION_TYPE_GROUP);
                        if (sessionId == 0)
                        {
                            sessionId = SessionModel::instance()->addSession(senderId, receiverId, base::SESSION_TYPE_GROUP);

                            base::SessionInfo *sessionInfo = new base::SessionInfo;
                            sessionInfo->set_session_type(base::SESSION_TYPE_GROUP);
                            sessionInfo->set_latest_msg_id(msgId);
                            sessionInfo->set_last_message_data(msg.message_data());
                            sessionInfo->set_session_top(base::SESSION_FLAG_NORMAL);
                            sessionInfo->set_latest_msg_time(createdTime);
                            sessionInfo->set_session_id(sessionId);
                            sessionInfo->set_other_id(receiverId);

                            //新增session转发到客户端
                            session::NewSessionRespone respone;
                            respone.set_user_id(senderId);
                            respone.set_allocated_session(sessionInfo);
                            auto conn = findProxyConn(conn_uuid);
                            if (conn)
                                sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);
                        }

                        //保存消息到数据库
                        messageModel->saveGroupMesage(receiverId, senderId, msgType, createdTime, msgId, msg.message_data());
                        //更新session
                        SessionModel::instance()->updateSession(sessionId);

                    }
                    else if (msgType == base::MESSAGE_TYPE_SINGLE_AUDIO)
                    {
                        //将音频文件上传到http服务器
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

                            base::SessionInfo *sessionInfo = new base::SessionInfo;
                            sessionInfo->set_session_type(base::SESSION_TYPE_SINGLE);
                            sessionInfo->set_latest_msg_id(msgId);
                            sessionInfo->set_last_message_data(msg.message_data());
                            sessionInfo->set_session_top(base::SESSION_FLAG_NORMAL);
                            sessionInfo->set_latest_msg_time(createdTime);
                            sessionInfo->set_session_id(senderSessionId);
                            sessionInfo->set_other_id(receiverId);
                            sessionInfo->set_last_message_data("[语音]");

                            //新增session转发到客户端
                            session::NewSessionRespone respone;
                            respone.set_user_id(senderId);
                            respone.set_allocated_session(sessionInfo);
                            auto conn = findProxyConn(conn_uuid);
                            if (conn)
                                sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);
                        }
                        uint32_t receiverSessionId = SessionModel::instance()->getSessionId(receiverId, senderId, base::SESSION_TYPE_SINGLE);
                        if (receiverSessionId == 0)
                        {
                            receiverSessionId = SessionModel::instance()->addSession(receiverId, senderId, base::SESSION_TYPE_SINGLE);

                            base::SessionInfo *sessionInfo = new base::SessionInfo;
                            sessionInfo->set_session_type(base::SESSION_TYPE_SINGLE);
                            sessionInfo->set_latest_msg_id(msgId);
                            sessionInfo->set_last_message_data(msg.message_data());
                            sessionInfo->set_session_top(base::SESSION_FLAG_NORMAL);
                            sessionInfo->set_latest_msg_time(createdTime);
                            sessionInfo->set_session_id(receiverSessionId);
                            sessionInfo->set_other_id(senderId);
                            sessionInfo->set_last_message_data("[语音]");

                            //新增session转发到客户端
                            session::NewSessionRespone respone;
                            respone.set_user_id(receiverId);
                            respone.set_allocated_session(sessionInfo);

                            auto conn = findProxyConn(conn_uuid);
                            if (conn)
                                sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);
                        }

                        AudioModel *audioModel = AudioModel::instance();
                        int audioId = audioModel->saveAudioInfo(senderId, receiverId, createdTime, msg.message_data(),
                                msg.audio_time());

                        if (audioId != -1) {
                            //保存消息到数据库
                            messageModel->saveAudioMessage(senderId, receiverId, createdTime, msgId,
                                                           std::to_string(audioId));
//                            messageModel->saveAudioMessage(receiverRelatedId, senderId, receiverId, createdTime, msgId,
//                                                           std::to_string(audioId));
                            //更新session
                            SessionModel::instance()->updateSession(senderSessionId);
                            SessionModel::instance()->updateSession(receiverSessionId);
                        }
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


    void readMessageAck(BasePdu *basePdu, uint32_t conn_uuid)
    {
        message::MessageDataAck ack;
        ack.ParseFromString(basePdu->getMessage());

        uint32_t fromUserId = ack.from_user_id();
        uint32_t toUserId   = ack.to_user_id();
        uint32_t messageId  = ack.msg_id();

        //修改数据库
        MessageModel::instance()->messageAck(fromUserId, toUserId, messageId);
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


    //获取历史消息
    void getOfflineMessageData(BasePdu *basePdu, uint32_t conn_uuid)
    {
        message::GetOfflineMessageRequest request;
        request.ParseFromString(basePdu->getMessage());

        message::GetOfflineMessageRespone respone;

        uint32_t userId = request.user_id();
        respone.set_user_id(userId);

        bool ret = MessageModel::instance()->getOfflineMessage(userId, respone);

        if (ret)
        {
            auto conn = findProxyConn(conn_uuid);
            if (conn)
                sendMessage(conn, respone, base::SID_SERVER, base::CID_MESSAGE_GET_OFFLINE_MESSAGE_RESPONE);
        }
    }


    //获取群组历史消息
    void getGroupOfflineMessage(BasePdu *basePdu, uint32_t conn_uuid) {
        message::GetGroupOfflineMessageRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t groupId = request.group_id();
        uint32_t currMsgId = request.curr_msg_id();

        message::GetGroupOfflineMessageRespone respone;
        respone.set_user_id(userId);
        respone.set_group_id(groupId);

        //获取离线消息
        bool ret = MessageModel::instance()->getGroupOfflineMessage(userId, groupId, currMsgId, respone);

        if (ret && respone.msg_data_size() > 0)
        {
            auto conn = findProxyConn(conn_uuid);
            if (conn)
                sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_GET_OFFLINE_MESSAGE_RESPONE);
        }
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

        bool ret = friendListModel->addFriend(userId, friendId, groupId, remark);

        if (!ret)
        {
            //do something
        }

        ret = friendListModel->saveAddRequest(userId, friendId, validateData);
        if (!ret)
        {

        }

        //创建session
        uint32_t sessionId = SessionModel::instance()->getSessionId(friendId, 3, base::SESSION_TYPE_VALIDATE_MSG);
        if (sessionId == 0)
        {
            sessionId = SessionModel::instance()->addSession(friendId, 3, base::SESSION_TYPE_VALIDATE_MSG);

            base::SessionInfo *sessionInfo = new base::SessionInfo;
            sessionInfo->set_session_id(sessionId);
            sessionInfo->set_other_id(3);
            sessionInfo->set_session_type(base::SESSION_TYPE_VALIDATE_MSG);
            sessionInfo->set_session_top(base::SESSION_FLAG_NORMAL);
            sessionInfo->set_last_message_data("[验证消息]");
            sessionInfo->set_latest_msg_time(time(nullptr));

            //将session信息发送到客户端
            session::NewSessionRespone respone;
            respone.set_user_id(friendId);
            respone.set_allocated_session(sessionInfo);

            auto conn = findProxyConn(conn_uuid);
            if (conn)
                sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);
        }
        else
        {
            SessionModel::instance()->updateSession(sessionId);
        }


    }


    void addFriendRespone(BasePdu *basePdu, uint32_t conn_uuid)
    {
        friendlist::AddFriendRespone respone;
        respone.ParseFromString(basePdu->getMessage());

        uint32_t userId = respone.user_id();
        uint32_t friendId = respone.friend_id();
        uint32_t resultId = respone.result_id();
        uint32_t groupId = respone.group_id();
        std::string remark = respone.remark();

        FriendListModel *friendListModel = FriendListModel::instance();

        bool ret = friendListModel->updateAddRequest(userId, friendId, resultId);

        if (!ret)
        {
        }

        if (resultId == 1)
        {
            //同意添加好友
            //[1] 修改请求者的好友信息
            //[2] 修改响应者的好友信息
            friendListModel->addFriend(userId, friendId, groupId, remark, 1);
            friendListModel->addFriend(friendId, userId, 0, remark, 1);
        }
        else if (resultId == 2)
        {
            //拒绝添加好友
            friendListModel->addFriend(friendId, userId, groupId, remark, 2);
        }
        else if (resultId == 3)
        {
            //忽略
            friendListModel->addFriend(friendId, userId, groupId, remark, 3);
        }

        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_FRIENDLIST_ADD_FRIEND_RESPONE);
    }

    //获取好友历史记录
    void getAddRequestHistory(BasePdu *basePdu, uint32_t conn_uuid)
    {
        friendlist::GetAddRequestHistoryRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        log("用户%d请求获取历史好友申请记录", userId);

        std::list<base::AddRequestInfo> history;
        FriendListModel *friendListModel = FriendListModel::instance();
        friendListModel->getAddRequestHistory(userId, history);

        friendlist::GetAddRequestHistoryRespone respone;
        respone.set_user_id(userId);

        for (const auto& elem : history)
        {
            auto info = respone.add_history();
            (*info) = elem;
        }

        auto conn = findProxyConn(conn_uuid);
        if (conn)
        {
            sendMessage(conn, respone, base::SID_SERVER, base::CID_FRIENDLIST_GET_REQUEST_HISTORY_RESPONE);
        }
    }


    void handleVerifyGroupResult(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::VerifyHandlerResult result;
        result.ParseFromString(basePdu->getMessage());

        uint32_t handleUserId   = result.handle_user_id();
        uint32_t groupId        = result.group_id();
        uint32_t requestUserId  = result.request_user_id();
        base::GroupVerifyResult verifyResult   = result.verify_result();

        //保存处理结果
        bool ret = GroupModel::instance()->updateAddGroupRequest(requestUserId, groupId, handleUserId, verifyResult);

        if (ret)
        {
            if (verifyResult == base::GROUP_VERIFY_RESULT_PASS)             //通过验证
            {
                GroupModel::instance()->addMember(groupId, requestUserId);
            }

            base::UserInfo userInfo;
            LoginModel::instance()->getUserInfo(handleUserId, userInfo);

            //构造消息包通知请求者处理结果
            group::GroupAddRequestHandleResult handleResult;
            handleResult.set_user_id(requestUserId);
            handleResult.set_group_id(groupId);
            handleResult.set_handle_user_nick(userInfo.user_nick());
            handleResult.set_verify_result(verifyResult);

            auto conn = findProxyConn(conn_uuid);
            if (conn)
                sendMessage(conn, handleResult, base::SID_SERVER, base::CID_GROUP_ADD_REQUEST_HANDLE_RESULT);
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
            sessionInfo.set_latest_msg_id(latestMsgId + 1);
            auto session = respone.add_sessions();
            *session = sessionInfo;
        }

        auto conn = findProxyConn(conn_uuid);
        if (conn)
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


    //新增session
    void createNewSession(BasePdu *basePdu, uint32_t conn_uid)
    {
        session::CreateNewSession request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId         = request.user_id();
        uint32_t otherId        = request.other_id();
        base::SessionType type  = request.session_type();


        uint32_t sessionId = SessionModel::instance()->addSession(userId, otherId, type);

        //创建成功
        if (sessionId != 0)
        {

            uint32_t msgId = 0;
            std::string content = "";
            uint32_t latestTime = 0;

            MessageModel::instance()->getLastestGroupMessage(otherId, content,latestTime);
            msgId = GroupModel::instance()->getLatestMsgIdByGroupId(otherId);

            base::SessionInfo *sessionInfo = new base::SessionInfo;
            sessionInfo->set_latest_msg_id(msgId);
            sessionInfo->set_other_id(otherId);
            sessionInfo->set_last_message_data(content);
            sessionInfo->set_session_top(base::SESSION_FLAG_NORMAL);
            sessionInfo->set_latest_msg_time(latestTime);
            sessionInfo->set_session_id(sessionId);
            sessionInfo->set_session_type(base::SESSION_TYPE_GROUP);

            session::NewSessionRespone respone;
            respone.set_user_id(userId);
            respone.set_allocated_session(sessionInfo);

            auto conn = findProxyConn(conn_uid);
            if (conn)
                sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);

        }

    }


    void createGroup(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::GroupCreateRequest request;
        request.ParseFromString(basePdu->getMessage());

        GroupModel *groupModel = GroupModel::instance();

        uint32_t groupId = groupModel->createGroup(request.user_id(), request.group_name(), request.group_type(), request.group_verify_type(), request.group_max_members());

        if (groupId != 0)
        {
            std::list<uint32_t> members;
            for (int i = 0; i < request.member_ids_size(); ++i)
            {
                members.push_back(request.member_ids(i));
            }
            auto ret = groupModel->addMembers(groupId, members);
            if (ret)
                log("加入群成功");
            else
                log("加入失败");
        }


        base::GroupInfo *groupInfo = new base::GroupInfo;
        groupInfo->set_group_id(groupId);
        groupInfo->set_group_name(request.group_name());
        groupInfo->set_group_capacity(request.group_max_members());
        groupInfo->set_group_head("http://www.liutimo.cn/group_default_head.png");
        groupInfo->set_group_creator(request.user_id());


        group::GroupCreateRespone respone;
        respone.set_user_id(request.user_id());
        respone.set_result_code(groupId == 0 ? 0 : 1);  //0成功 1失败
        respone.set_allocated_group_info(groupInfo);

        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_CREATE_RESPONE);
    }


    //获取群组list
    void getGroupList(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::GetGroupListRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();

        group::GetGroupListRespone respone;
        respone.set_user_id(userId);

        GroupModel *groupModel = GroupModel::instance();

        //获取用户的所有群组
        std::list<uint32_t> groups;
        groupModel->getOtherGroupByUserId(userId, groups);
        groupModel->getSelfGroupByUserId(userId, groups);

        //设置每个群的信息到response
        for (uint32_t groupId : groups)
        {
            base::GroupInfo *groupInfo = respone.add_group_info();
            groupModel->getGroupInfoByGroupId(groupId, *groupInfo);
        }

        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_GET_LIST_RESPONE);

    }


    //获取群成员
    void getGroupMember(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::GetGroupMemberInfoRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t groupId = request.group_id();

        GroupModel *groupModel = GroupModel::instance();

        //查找群成员信息
        list<base::MemberInfo> memberInfoList;
        groupModel->getMembersByGroupId(groupId, memberInfoList);

        group::GetGroupMemberInfoRespone respone;
        respone.set_user_id(userId);
        respone.set_group_id(groupId);
        for (base::MemberInfo &memberInfo : memberInfoList)
        {
            auto memInfo = respone.add_member_infos();
            *memInfo = memberInfo;
        }


        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_GET_MEMBER_RESPONE);
    }

    //修改群名片
    void modifyGroupCard(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::ModifyGroupCard request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t groupId = request.group_id();
        std::string groupCard = request.group_card();

        GroupModel *groupModel = GroupModel::instance();
        groupModel->modifyGroupCard(groupId, userId, groupCard);

    }

    //搜索群组
    void searchGroup(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::SearchGroupRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        base::SearchType type = request.search_type();
        std::string searchData = request.search_data();

        GroupModel *groupModel = GroupModel::instance();
        std::list<base::GroupInfo> groupList;
        groupModel->searchGroup(userId, searchData, type, groupList);

        group::SearchGroupRespone respone;
        respone.set_user_id(userId);
        for (auto &group : groupList)
        {
            auto g = respone.add_groups();
            *g = group;
        }

        auto conn = findProxyConn(conn_uuid);
        if (conn)
        {
            sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_SEARCH_GROUP_RESPONE);
        }
    }

    //添加群组
    void addGroup(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::AddGroupRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t groupId = request.group_id();
        std::string verifyData = request.verify_data();

        GroupModel *groupModel = GroupModel::instance();

        base::GroupVerifyType type = groupModel->getVerofyTypeByGroupId(groupId);

        if (type == base::GROUP_VERIFY_NEED)    //需要验证信息 转发消息到管理员和群组
        {
            //保存请求信息
            uint32_t requestId = GroupModel::instance()->addNewGroupRequest(userId, groupId, verifyData);

            // [1]获取请求用户信息
            base::UserInfo *userInfo = new base::UserInfo;
            LoginModel *loginModel = LoginModel::instance();
            loginModel->getUserInfo(userId, *userInfo);

            // [2]设置返回的验证信息
            group::GroupVerifyNotify *groupVerifyNotify = new group::GroupVerifyNotify;
            groupVerifyNotify->set_user_id(userId);
            groupVerifyNotify->set_group_id(groupId);
            groupVerifyNotify->set_verify_data(verifyData);
            groupVerifyNotify->set_allocated_user_info(userInfo);

            // [3]获取管理员和群主
            base::GroupInfo groupInfo;
            groupModel->getGroupInfoByGroupId(groupId, groupInfo);

            // [4]创建session
            DB_PRIVATE::AddValidateMessageSession(groupInfo.group_creator(), userInfo->user_nick(),
                                                  groupInfo.group_name(), conn_uuid); //群主

            // [5]构造响应包
            group::GroupVerifyNotifyUsers groupVerifyNotifyUsers;
            groupVerifyNotifyUsers.set_allocated_verify_notify(groupVerifyNotify);
            groupVerifyNotifyUsers.add_notify_users(groupInfo.group_creator());     // 添加群主
            for (int i = 0; i < groupInfo.managers_size(); ++i)                     // 添加管理员
            {
                groupVerifyNotifyUsers.add_notify_users(groupInfo.managers(i));
                DB_PRIVATE::AddValidateMessageSession(groupInfo.managers(i), userInfo->user_nick(),
                                                      groupInfo.group_name(), conn_uuid); //为管理员创建session
            }

            // [6]发送到消息服务器
            auto conn = findProxyConn(conn_uuid);
            if (conn)
            {
                sendMessage(conn, groupVerifyNotifyUsers, base::SID_SERVER, base::CID_GROUP_VERIFY_NOTIFY);
            }

        }
        else if (type == base::GROUP_VERIFY_ALL)
        {
            //无需验证信息，直接加入
            //考虑加入后是否通知群员。
            base::GroupInfo *groupInfo = new base::GroupInfo;
            groupModel->getGroupInfoByGroupId(groupId, *groupInfo);

            uint32_t capacity = groupInfo->group_capacity();
            uint32_t current = groupInfo->managers().size() + groupInfo->members().size() + 1;

            if (current >= capacity)
            {
                //群已满
            }
            else
            {
                bool ret = groupModel->addMember(groupId, userId);
                group::AddGroupRespone respone;
                respone.set_user_id(userId);
                respone.set_result_coid(ret ? 0 : 1);
                respone.set_allocated_group_info(groupInfo);

                auto conn = findProxyConn(conn_uuid);
                if (conn)
                    sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_ADD_GROUP_RESPONE);
            }
        }


    }

    //获取群组最新消息ID
    void getLatestGroupMsgId(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::GetLatestGroupMsgIdRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId     = request.user_id();
        uint32_t groupId    = request.group_id();

        uint32_t latestGroupId = GroupModel::instance()->getLatestMsgIdByGroupId(groupId);

        group::GetLatestGroupMsgIdRespone respone;
        respone.set_user_id(userId);
        respone.set_group_id(groupId);
        respone.set_latest_msg_id(latestGroupId);

        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_GET_LATEST_MSG_ID_RESPONE);
    }



    //退出群组
    void exitGroup(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::ExitGroupRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId     = request.user_id();
        uint32_t groupId    = request.group_id();


        group::ExitGroupRespone respone;
        respone.set_user_id(userId);
        respone.set_group_id(groupId);


        base::GroupInfo groupInfo;
        GroupModel::instance()->getGroupInfoByGroupId(groupId, groupInfo);

        auto conn = findProxyConn(conn_uuid);
        //群主退出
        if (groupInfo.group_creator() == userId)
        {
            //解散群
            GroupModel::instance()->ungroup(groupId);

            //删除与该群相关的session
            SessionModel::instance()->deleteGroupSession(groupId);

            //通知群员
            group::UngroupNotify notify;
            notify.set_user_id(userId);
            notify.set_group_id(groupId);

            if (conn)
                sendMessage(conn, notify, base::SID_SERVER, base::CID_GROUP_UNGROUP);
        }
        else
        {
            bool ret = GroupModel::instance()->exitGroup(groupId, userId);

            if (ret)
            {
                //删除session
                uint32_t sessionId = SessionModel::instance()->getSessionId(userId, groupId, base::SESSION_TYPE_GROUP);
                if (sessionId != 0)
                    SessionModel::instance()->removeSession(sessionId);
            }

            uint32_t resCode = ret ? 0 : 1;

            respone.set_result_code(resCode);
        }


        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_EXIT_GROUP_RESPONE);
    }


    //修改群头像
    void modifyGroupHeader(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::ModifyGroupHeaderRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t groupId = request.group_id();
        string url = request.header_url();
        //需要判断权限
        bool ret = GroupModel::instance()->modifyGroupHeader(groupId, url);

        group::ModifyGroupHeaderRespone respone;
        respone.set_user_id(userId);
        respone.set_group_id(groupId);
        if (ret) {
            respone.set_header_url(url);
            respone.set_result_code(0);
        } else
            respone.set_result_code(1);

        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_MODIFY_HEADER_RESPONE);

    }

    //设置管理员
    void setGroupManager(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::SetGroupManagerRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId     = request.user_id();
        uint32_t memberId   = request.member_id();
        uint32_t groupId    = request.group_id();


        //验证userId 是否具备该权限
        //...

        bool ret = GroupModel::instance()->setGroupManager(groupId, memberId);
        uint32_t resultCode = ret ? 0 : 1;

        group::SetGroupManagerRespone respone;
        respone.set_user_id(userId);
        respone.set_member_id(memberId);
        respone.set_group_id(groupId);
        respone.set_result_code(resultCode);


        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_SET_MANAGER_RESPONE);
    }

    //踢出群组
    void kickOutGroupMember(BasePdu *basePdu, uint32_t conn_uuid)
    {
        group::KickOutMemberRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId     = request.user_id();
        uint32_t memberId   = request.member_id();
        uint32_t groupId    = request.group_id();

        //验证userId 是否具备该权限
        //...

        bool ret = GroupModel::instance()->exitGroup(groupId, memberId);

        if (ret)
        {
            //成功退出
            uint32_t sessionId = SessionModel::instance()->getSessionId(userId, groupId, base::SESSION_TYPE_GROUP);
            if (sessionId != 0)
                SessionModel::instance()->removeSession(sessionId);
        }
        uint32_t resultCode = ret ? 0 : 1;

        group::KickOutMemberRespone respone;
        respone.set_user_id(userId);
        respone.set_member_id(memberId);
        respone.set_group_id(groupId);
        respone.set_result_code(resultCode);


        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_GROUP_KICK_OUT_RESPONE);
    }

    void modifyInformation(BasePdu *basePdu, uint32_t conn_uuid)
    {
        other::ModifyInformationRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();

        OtherModel *model = OtherModel::instance();
        bool ret = model->modifyUserInformation(userId, request.user_info());


//        响应
        other::ModifyInformationRespone respone;
        respone.set_user_id(userId);

        uint32_t resCode = ret ? 0 : 1;
        respone.set_result_code(resCode);

        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_OTHER_MODIFY_INFORMATION_RESPONE);

    }


    void modifyUserIcon(BasePdu *basePdu, uint32_t conn_uuid)
    {
        other::ModifyUserImageRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        std::string url = request.icon_url();

        OtherModel *otherModel = OtherModel::instance();
        bool ret = otherModel->modifyUserIcon(userId, url);

        other::ModifyUserImageRespone respone;
        respone.set_user_id(userId);

        uint32_t resCode = ret ? 0 : 1;
        respone.set_result_code(resCode);

        if (ret)
            respone.set_icon_url(url);

        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_OTHER_MODIFY_USER_HEADER_RESPONE);
    }



    //获取好友详细信息
    void getFriendInformation(BasePdu *basePdu, uint32_t conn_uuid)
    {
        other::GetFriendInformationRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();
        uint32_t friendId = request.friend_id();

        base::UserInfo *userInfo = new base::UserInfo;
        LoginModel::instance()->getUserInfo(friendId, *userInfo);

        other::GetFriendInformationRespone respone;
        respone.set_user_id(userId);
        respone.set_allocated_user_info(userInfo);

        auto conn = findProxyConn(conn_uuid);
        if (conn)
            sendMessage(conn, respone, base::SID_SERVER, base::CID_OTHER_GFT_FRIEND_INFORMATION_RESPONE);
    }


    //离线文件传输
    void offlineFileUploadComplete(BasePdu *basePdu, uint32_t conn_uuid)
    {
        server::OfflineUploadComplete request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t senderId = request.sender_id();
        uint32_t receiverId = request.receiver_id();
        std::string taskId = request.task_id();

        OtherModel::instance()->saveOfflineFile(senderId, receiverId, taskId);
    }

    //获取离线文件
    void getOfflineFile(BasePdu *basePdu, uint32_t conn_uid)
    {
        file::GetOfflineFileRequest request;
        request.ParseFromString(basePdu->getMessage());

        uint32_t userId = request.user_id();

        file::GetOfflineFileRespone respone;
        respone.set_user_id(userId);
        bool ret = OtherModel::instance()->getOfflineFile(userId, respone);

        if (ret) {
            auto conn = findProxyConn(conn_uid);
            if (conn)
                sendMessage(conn, respone, base::SID_FILE, base::CID_FILE_GET_OFFILNE_FILE_RESPONE);
        }
    }
}


namespace DB_PRIVATE {
    //群组验证消息session创建
    void AddValidateMessageSession(uint32_t userId, const std::string &userNick,
                                   const std::string &groupName, uint32_t connUuid) {
        uint32_t sessionId = SessionModel::instance()->getSessionId(userId, 3, base::SESSION_TYPE_VALIDATE_MSG);
        if (sessionId == 0) {
            sessionId = SessionModel::instance()->addSession(userId, 3, base::SESSION_TYPE_VALIDATE_MSG);

            base::SessionInfo *sessionInfo = new base::SessionInfo;
            sessionInfo->set_session_id(sessionId);
            sessionInfo->set_other_id(3);
            sessionInfo->set_session_type(base::SESSION_TYPE_VALIDATE_MSG);
            sessionInfo->set_session_top(base::SESSION_FLAG_NORMAL);
            sessionInfo->set_last_message_data(userNick + "请求加入" + groupName);
            sessionInfo->set_latest_msg_time(time(nullptr));

            //将session信息发送到客户端
            session::NewSessionRespone respone;
            respone.set_user_id(userId);
            respone.set_allocated_session(sessionInfo);

            auto conn = findProxyConn(connUuid);
            if (conn)
                sendMessage(conn, respone, base::SID_SERVER, base::CID_SESSIONLIST_ADD_SESSION);
        } else {
            SessionModel::instance()->updateSession(sessionId);
        }
    }
}