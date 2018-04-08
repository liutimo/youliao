//
// Created by liuzheng on 18-3-25.
//

#include "Interface.h"
#include "../ProxyConn.h"
#include "LoginModel.h"
#include "FriendListModel.h"

#include "pdu/protobuf/youliao.server.pb.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"


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
            validateRespone.set_user_name(validateRequest.user_name());
            validateRespone.set_result_code(0);
            validateRespone.set_result_string("登录成功");
            validateRespone.set_allocated_user_info(userInfo);
        }
        else
        {
            validateRespone.set_result_code(1);
            validateRespone.set_result_string("登录失败， 用户名或密码错误！");
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

    void getFriendList(BasePdu* basePdu, uint32_t conn_uuid)
    {
        friendlist::FriendListRequest friendListRequest;
        friendListRequest.ParseFromString(basePdu->getMessage());

        friendlist::FriendListRespone friendListRespone;
        friendListRespone.set_attach_data(friendListRequest.attach_data());

        FriendListModel friendListModel;
        friendListModel.getFriendList(friendListRequest.user_id(), friendListRespone);

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
}


