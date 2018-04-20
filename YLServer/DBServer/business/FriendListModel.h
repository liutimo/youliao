//
// Created by liuzheng on 18-3-26.
//

#ifndef DBSERVER_FRIENDLISTMODEL_H
#define DBSERVER_FRIENDLISTMODEL_H

#include "pdu/protobuf/youliao.server.pb.h"
#include "pdu/protobuf/youliao.base.pb.h"
#include "pdu/protobuf/youliao.friendlist.pb.h"
#include <list>

using namespace youliao::pdu;

class FriendListModel {
public:
    static FriendListModel* instance();
    virtual ~FriendListModel();

    void getGroups(uint32_t user_id, friendlist::GroupsRespone &groupsRespone);

    void getFriendList(uint32_t user_id, uint32_t msg_serv_idx, friendlist::FriendListRespone &friendListRespone);

    void getOnlineFriends(uint32_t user_id, server::RouteGetOnlineFriendRespone &routeGetOnlineFriendRespone);

    bool modifySignature(uint32_t user_id, const std::string &signature);

    bool addNewFriendGroup(uint32_t user_id, const std::string &new_group_name, uint32_t &groupId);

    bool renameFriendGroup(uint32_t user_id, const std::string &group_nnew_ame, uint32_t &groupId);

    bool deleteFriendGroup(uint32_t user_id, uint32_t group_id);

    bool moveFriendToGroup(uint32_t user_id, uint32_t friend_id, uint32_t group_id);

    bool deleteFriend(uint32_t user_id, uint32_t friend_id);

    bool modifyFriendRemark(uint32_t user_id, uint32_t friend_id, const std::string &friendRemark);

    uint32_t getRelationId(uint32_t userId, uint32_t friendId);

    bool searchFriend(std::string &searchData, base::SearchType searchType, std::list<base::FriendInfo> &);

private:
    FriendListModel();
    static FriendListModel *m_instance;
};


#endif //DBSERVER_FRIENDLISTMODEL_H
