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

void FriendListModel::getFriendList(uint32_t user_id, uint32_t msg_serv_idx, friendlist::FriendListRespone &friendListRespone)
{
    DBManager *manager = DBManager::instance();
    DBConn *conn = manager->getConnection();

    if (conn)
    {
        //卧槽,这个表建得有问题,怎么可以这么长的sql语句
        //查找指定用户的所有好友
        char query_sql_1[] =    "SELECT user_a_id, b_group_id as group_id, group_name, user_account, user_nickname, user_header, user_sign_info "
                                "from yl_friend, yl_friend_group ,yl_user "
                                "where yl_friend_group.group_id = b_group_id and user_b_id = '%d' and status = 0 and yl_user.user_id = user_a_id "
                                "UNION "
                                "SELECT user_b_id, a_group_id as group_id, group_name, user_account, user_nickname, user_header, user_sign_info "
                                "from yl_friend, yl_friend_group ,yl_user "
                                "where yl_friend_group.group_id = a_group_id and user_a_id = '%d' and status = 0 and yl_user.user_id = user_b_id;";

        char query_sql_2[2048];
        sprintf(query_sql_2, query_sql_1, user_id, user_id);

        std::cout << query_sql_2 << std::endl;

        ResultSet *resultSet = conn->query(query_sql_2);


        auto m = friendListRespone.mutable_friend_list();

        auto cacheConn = CacheManager::instance()->getCacheConn("OnlineUser");

        string mapName = "OnlineFriend_" + to_string(user_id);
        while (resultSet->next()) {
            uint32_t group_id = (uint32_t)resultSet->getInt("group_id");

            (*m)[group_id].set_group_id(group_id);
            (*m)[group_id].set_group_name(resultSet->getString("group_name"));

            uint32_t  friendId = (uint32_t )resultSet->getInt("user_a_id");

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
                string field = resultSet->getString("user_a_id");
                string value = cacheConn->hget("user_map", friendIdStr);
                cacheConn->hset(mapName, field, value);
                log("msg server index %s", value.c_str());
                log("%s online ", friendIdStr.c_str());
                friend_->set_friend_is_online(true);
            } else {
                friend_->set_friend_is_online(false);

                log("%s is't online ", resultSet->getString("user_a_id").c_str());
            }
        }
        CacheManager::instance()->releaseCacheConn(cacheConn);
    }

    manager->releaseConnection(conn);
}

void FriendListModel::getOnlineFriends(uint32_t user_id, server::OnlineFriendRespone &onlineFriendRespone)
{
    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");

    if (conn)
    {
        string mapName = "OnlineFriend_" + to_string(user_id);
        map<string, string> onlineFriends;
        conn->hgetAll(mapName, onlineFriends);
        log("%s has %d online friends", mapName.c_str(), onlineFriends.size());


        auto& onlineFriendMap = *onlineFriendRespone.mutable_online_firends();

        for (auto elem : onlineFriends)
        {
            string friendId = elem.first;
            string msg_idx = elem.second;
            log("key = %s value = %s", friendId.c_str(), msg_idx.c_str());
            onlineFriendMap[atoi(friendId.)]
        }
    }

    CacheManager::instance()->releaseCacheConn(conn);
}