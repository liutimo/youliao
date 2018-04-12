//
// Created by liuzheng on 18-3-26.
//

#include "FriendListModel.h"
#include "../DBPool.h"
#include "util/util.h"
#include "../CachePool.h"
#include <cstring>
FriendListModel::FriendListModel()
{

}

FriendListModel::~FriendListModel()
{

}


void FriendListModel::getGroups(uint32_t user_id, friendlist::GroupsRespone &groupsRespone)
{
    DBManager *manager = DBManager::instance();
    DBConn *dbConn = manager->getConnection();
    if (dbConn)
    {
        char query_sql_1[] = "SELECT group_id, group_name from yl_friend_group where user_id = '%d' or group_id = '1';";
        char query_sql_2[2048];
        sprintf(query_sql_2, query_sql_1, user_id);

        ResultSet *resultSet = dbConn->query(query_sql_2);
        auto m = groupsRespone.mutable_user_groups();

        while (resultSet->next())
        {
            uint32_t groupId = (uint32_t)resultSet->getInt("group_id");
            string groupName = resultSet->getString("group_name");
            (*m)[groupId] = groupName;
        }
    }

    manager->releaseConnection(dbConn);
}

void FriendListModel::getFriendList(uint32_t user_id, uint32_t msg_serv_idx, friendlist::FriendListRespone &friendListRespone)
{
    DBManager *manager = DBManager::instance();
    DBConn *conn = manager->getConnection();

    if (conn)
    {
        //卧槽,这个表建得有问题,怎么可以这么长的sql语句
        //查找指定用户的所有好友
        char query_sql_1[] =    "SELECT friend_id, group_id,  user_account, user_nickname, user_header, user_sign_info "
                                "FROM yl_friend, yl_user "
                                "WHERE yl_friend.user_id = '%d' and yl_user.user_id = yl_friend.friend_id and status = '1'  "
                                "order by yl_friend.friend_id DESC";

        char query_sql_2[2048];
        sprintf(query_sql_2, query_sql_1, user_id);

        std::cout << query_sql_2 << std::endl;

        ResultSet *resultSet = conn->query(query_sql_2);


        auto m = friendListRespone.mutable_friend_list();

        auto cacheConn = CacheManager::instance()->getCacheConn("OnlineUser");

        string mapName = "OnlineFriend_" + to_string(user_id);
        while (resultSet->next()) {
            uint32_t group_id = (uint32_t)resultSet->getInt("group_id");

            (*m)[group_id].set_group_id(group_id);

            uint32_t  friendId = (uint32_t )resultSet->getInt("friend_id");

            auto friend_ = (*m)[group_id].add_friend_();
            friend_->set_friend_id(friendId);
            friend_->set_friend_nick(resultSet->getString("user_nickname"));
            friend_->set_friend_header_url(resultSet->getString("user_header"));
            friend_->set_friend_sign_info(resultSet->getString("user_sign_info"));
            friend_->set_friend_account((uint32_t)resultSet->getInt("user_account"));

            //该好友在线
            string friendIdStr = to_string(friendId);
            if (!cacheConn->hget("user_map", friendIdStr).empty())
            {
                //创建该用户的在线好友map
                string field = resultSet->getString("friend_id");
                string value = cacheConn->hget("user_map", friendIdStr);
                cacheConn->hset(mapName, field, value);
                log("msg server index %s", value.c_str());
                log("%s online ", friendIdStr.c_str());
                friend_->set_friend_is_online(true);
            } else {
                friend_->set_friend_is_online(false);

                log("%s is't online ", resultSet->getString("friend_id").c_str());
            }
        }
        CacheManager::instance()->releaseCacheConn(cacheConn);
    }

    manager->releaseConnection(conn);
}

void FriendListModel::getOnlineFriends(uint32_t user_id, server::RouteGetOnlineFriendRespone &routeGetOnlineFriendRespone)
{
    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");

    if (conn)
    {
        string mapName = "OnlineFriend_" + to_string(user_id);
        map<string, string> onlineFriends;
        conn->hgetAll(mapName, onlineFriends);
        log("%s has %d online friends", mapName.c_str(), onlineFriends.size());

        auto onlineFriendMap = routeGetOnlineFriendRespone.mutable_online_firends();

        for (auto elem : onlineFriends)
        {
            string friendId = elem.first;
            string msg_idx = elem.second;
            log("key = %s value = %s", friendId.c_str(), msg_idx.c_str());
            (*onlineFriendMap)[atoi(friendId.c_str())] = (uint32_t )atoi(msg_idx.c_str());
        }
    }

    CacheManager::instance()->releaseCacheConn(conn);
}


bool FriendListModel::modifySignature(uint32_t user_id, const std::string &signature)
{
    bool res = false;

    auto conn = DBManager::instance()->getConnection();

    if (conn)
    {
        char update_sql_1[] = "UPDATE yl_user SET user_sign_info = '%s' WHERE user_id = '%d'";
        char update_sql_2[2048];
        sprintf(update_sql_2, update_sql_1, signature.c_str(), user_id);
        log("modify signature. sql = %s", update_sql_2);

        if (conn->update(update_sql_2))
            res = true;
        else
            res = false;
    }
    DBManager::instance()->releaseConnection(conn);

    return res;
}

bool FriendListModel::addNewFriendGroup(uint32_t user_id, const std::string &new_group_name)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();

    if (conn)
    {
        char insert_sql_1[] = "";
        char insert_sql_2[2048];

        log("insert new friend group %s to user %d", new_group_name.c_str(), user_id);
        if(conn->update(insert_sql_2))
            ret = true;
        else
            ret = false;
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}
