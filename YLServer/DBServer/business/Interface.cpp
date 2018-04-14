//
// Created by liuzheng on 18-3-25.
//

#include "Interface.h"
#include "../ProxyConn.h"
#include "LoginModel.h"
#include "FriendListModel.h"
#include "util/util.h"
#include "../CachePool.h"

#include "pdu/protobuf/youliao.server.pb.h"


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

        FriendListModel friendListModel;
        friendListModel.getGroups(userId, groupsRespone);

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

        FriendListModel friendListModel;
        friendListModel.getFriendList(friendListRequest.user_id(), friendListRequest.msg_serv_idx(), friendListRespone);

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

        FriendListModel friendListModel;
        friendListModel.getOnlineFriends(userId, routeGetOnlineFriendRespone);

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

        FriendListModel friendListModel;
        bool ret = friendListModel.modifySignature(userId, userSignature);

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

        FriendListModel friendListModel;
        if (friendListModel.addNewFriendGroup(userId, newGroupName, groupId))
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

        FriendListModel friendListModel;
        friendListModel.renameFriendGroup(userId, groupNewName, groupId);
    }

    //删除分组
    void deleteFriendGroup(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::DeleteFriendGroupRequest deleteFriendGroupRequest;
        deleteFriendGroupRequest.ParseFromString(basePdu->getMessage());

        uint32_t userId = deleteFriendGroupRequest.user_id();
        uint32_t groupId = deleteFriendGroupRequest.group_id();

        FriendListModel friendListModel;
        friendListModel.deleteFriendGroup(userId, groupId);
    }

    //移动好友到指定分组
    void moveFriendToGroup(BasePdu *basePdu, uint32_t conn_uid)
    {
        friendlist::MoveFriendToGroupRequest request;
        request.ParseFromString(basePdu->getMessage());

        FriendListModel friendListModel;
        friendListModel.moveFriendToGroup(request.user_id(), request.friend_id(), request.group_id());
    }

}


