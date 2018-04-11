//
// Created by liuzheng on 18-3-26.
//

#ifndef DBSERVER_FRIENDLISTMODEL_H
#define DBSERVER_FRIENDLISTMODEL_H

#include <pdu/protobuf/youliao.server.pb.h>
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"

using namespace youliao::pdu;

class FriendListModel {
public:
    FriendListModel();
    virtual ~FriendListModel();

    void getFriendList(uint32_t user_id, uint32_t msg_serv_idx, friendlist::FriendListRespone &friendListRespone);

    void getOnlineFriends(uint32_t user_id, server::RouteGetOnlineFriendRespone &routeGetOnlineFriendRespone);

    bool modifySignature(uint32_t user_id, const std::string &signature);
};


#endif //DBSERVER_FRIENDLISTMODEL_H
