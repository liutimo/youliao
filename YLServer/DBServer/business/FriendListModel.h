//
// Created by liuzheng on 18-3-26.
//

#ifndef DBSERVER_FRIENDLISTMODEL_H
#define DBSERVER_FRIENDLISTMODEL_H

#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"

using namespace youliao::pdu;

class FriendListModel {
public:
    FriendListModel();
    virtual ~FriendListModel();

    void getFriendList(uint32_t user_id, friendlist::FriendListRespone &friendListRespone);

};


#endif //DBSERVER_FRIENDLISTMODEL_H
