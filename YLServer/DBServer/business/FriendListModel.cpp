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

void FriendListModel::getFriendList(uint32_t user_id, friendlist::FriendListRespone &friendListRespone)
{
    DBManager *manager = DBManager::instance();
    DBConn *conn = manager->getConnection();

    if (conn)
    {
        //卧槽,这个表建得有问题,怎么可以这么长的sql语句
        //查找指定用户的所有好友
//        char query_sql_1[] =    "SELECT user_a_id, b_group_id as group_id, group_name, user_account, user_nickname, user_phone, user_sex, user_email, user_header, user_sign_info "
//                                "from yl_friend, yl_friend_group ,yl_user "
//                                "where yl_friend_group.group_id = b_group_id and user_b_id = '%d' and status = 0 and yl_user.user_id = user_a_id "
//                                "UNION "
//                                "SELECT user_b_id, a_group_id as group_id, group_name, user_account, user_nickname, user_phone, user_sex, user_email, user_header, user_sign_info "
//                                "from yl_friend, yl_friend_group ,yl_user "
//                                "where yl_friend_group.group_id = a_group_id and user_a_id = '%d' and status = 0 and yl_user.user_id = user_b_id;";

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

        while (resultSet->next()) {
            uint32_t group_id = resultSet->getInt("group_id");

            (*m)[group_id].set_group_id(group_id);
            (*m)[group_id].set_group_name(resultSet->getString("group_name"));

            auto friend_ = (*m)[group_id].add_friend_();

            friend_->set_friend_id(resultSet->getInt("user_a_id"));
            friend_->set_friend_nick(resultSet->getString("user_nickname"));
//            friend_->set_friend_email(resultSet->getString("user_email"));
            friend_->set_friend_header_url(resultSet->getString("user_header"));
            friend_->set_friend_sign_info(resultSet->getString("user_sign_info"));
            friend_->set_friend_account(resultSet->getInt("user_account"));
//            friend_->set_friend_sex(resultSet->getInt("user_sex"));
//            friend_->set_friend_phone(resultSet->getString("user_phone"));

            //该好友在线
            if (cacheConn->sIsMem("OnlineUser", resultSet->getString("user_a_id"))) {
                log("%s online ", resultSet->getString("user_a_id").c_str());
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