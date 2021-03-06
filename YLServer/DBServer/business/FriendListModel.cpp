//
// Created by liuzheng on 18-3-26.
//

#include "FriendListModel.h"
#include "../DBPool.h"
#include "util/util.h"
#include <string>
using namespace std;

FriendListModel* FriendListModel::m_instance = nullptr;

FriendListModel* FriendListModel::instance()
{
    if (!m_instance)
        m_instance = new FriendListModel;
    return m_instance;
}

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

        delete resultSet;
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
        char query_sql_1[] =    "SELECT id, friend_id, group_id, friend_remark, user_account, user_nickname, user_header, user_sign_info "
                                "FROM yl_friend, yl_user "
                                "WHERE yl_friend.user_id = '%d' and yl_user.user_id = yl_friend.friend_id and status = '1'  "
                                "order by yl_friend.friend_id";

        char query_sql_2[2048];
        sprintf(query_sql_2, query_sql_1, user_id);
        printSql2Log(query_sql_2);


        ResultSet *resultSet = conn->query(query_sql_2);


        auto m = friendListRespone.mutable_friend_list();

        string mapName = "OnlineFriend_" + to_string(user_id);
        while (resultSet->next()) {
            uint32_t group_id = (uint32_t)resultSet->getInt("group_id");

            (*m)[group_id].set_group_id(group_id);

            uint32_t  friendId = (uint32_t )resultSet->getInt("friend_id");

            auto friend_ = (*m)[group_id].add_friend_();
            friend_->set_related_id((uint32_t)resultSet->getInt("id"));
            friend_->set_friend_id(friendId);
            friend_->set_friend_nick(resultSet->getString("user_nickname"));
            friend_->set_friend_header_url(resultSet->getString("user_header"));
            friend_->set_friend_sign_info(resultSet->getString("user_sign_info"));
            friend_->set_friend_account((uint32_t)resultSet->getInt("user_account"));
            friend_->set_friend_remark(resultSet->getString("friend_remark"));

            //好友在线信息改由routeserver 维护
            //该消息到达MsgServer后， 转发routerServer查询好友在线信息

//            //该好友在线
//            string friendIdStr = to_string(friendId);
//            if (!cacheConn->hget("user_map", friendIdStr).empty())
//            {
//                //创建该用户的在线好友map
//                string field = resultSet->getString("friend_id");
//                string value = cacheConn->hget("user_map", friendIdStr);
//                cacheConn->hset(mapName, field, value);
//                log("msg server index %s", value.c_str());
//                log("%s online ", friendIdStr.c_str());
//                friend_->set_friend_is_online(true);
//            } else {
//                friend_->set_friend_is_online(false);
//
//                log("%s is't online ", resultSet->getString("friend_id").c_str());
//            }
        }
        delete resultSet;

    }

    manager->releaseConnection(conn);
}

//void FriendListModel::getOnlineFriends(uint32_t user_id, server::RouteGetOnlineFriendRespone &routeGetOnlineFriendRespone)
//{
//    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");
//
//    if (conn)
//    {
//        string mapName = "OnlineFriend_" + to_string(user_id);
//        map<string, string> onlineFriends;
//        conn->hgetAll(mapName, onlineFriends);
//        log("Redis: MapName = %s, 有%d个在线好友", mapName.c_str(), onlineFriends.size());
//        log("----------------------------");
//        auto onlineFriendMap = routeGetOnlineFriendRespone.mutable_online_firends();
//
//        for (auto elem : onlineFriends)
//        {
//            string friendId = elem.first;
//            string msg_idx = elem.second;
//            log("| key = %s value = %s |", friendId.c_str(), msg_idx.c_str());
//            (*onlineFriendMap)[atoi(friendId.c_str())] = (uint32_t )atoi(msg_idx.c_str());
//        }
//        log("----------------------------");
//    }
//
//    CacheManager::instance()->releaseCacheConn(conn);
//}


bool FriendListModel::modifySignature(uint32_t user_id, const std::string &signature)
{
    bool res = false;

    auto conn = DBManager::instance()->getConnection();

    if (conn)
    {
        char update_sql_1[] = "UPDATE yl_user SET user_sign_info = '%s' WHERE user_id = '%d'";
        char update_sql_2[2048];
        sprintf(update_sql_2, update_sql_1, signature.c_str(), user_id);
        printSql2Log(update_sql_2);

        if (conn->update(update_sql_2))
            res = true;
        else
            res = false;
    }
    DBManager::instance()->releaseConnection(conn);

    return res;
}

bool FriendListModel::addNewFriendGroup(uint32_t user_id, const std::string &new_group_name, uint32_t &groupId)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();

    if (conn)
    {
        char insert_sql_1[] = "INSERT INTO yl_friend_group(user_id, group_name) VALUES(%d, '%s');";
        char insert_sql_2[2048];
        sprintf(insert_sql_2, insert_sql_1, user_id, new_group_name.c_str());
        printSql2Log(insert_sql_2);

        if(conn->update(insert_sql_2))
        {
            ret = true;
            char query_sql_1[] = "SELECT group_id from yl_friend_group where group_name = '%s' and user_id = %d;";
            char query_sql_2[2048];
            printSql2Log(query_sql_2);
            sprintf(query_sql_2, query_sql_1, new_group_name.c_str(), user_id);
            auto resultSet = conn->query(query_sql_2);
            if (resultSet->next())
                groupId = (uint32_t)resultSet->getInt("group_id");

            delete resultSet;
        }else
            ret = false;
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}


bool FriendListModel::renameFriendGroup(uint32_t user_id, const std::string &group_new_name, uint32_t &groupId)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();

    if (conn)
    {
        char update_sql_1[] = "UPDATE yl_friend_group set group_name = '%s' where user_id = %d and group_id = %d;";
        char update_sql_2[2048];
        sprintf(update_sql_2, update_sql_1, group_new_name.c_str(), user_id, groupId);
        printSql2Log(update_sql_2);
        if(conn->update(update_sql_2))
            ret = true;
        else
            ret = false;
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}

bool FriendListModel::deleteFriendGroup(uint32_t user_id, uint32_t group_id)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();

    if (conn)
    {
        char delete_sql[] = "DELETE FROM yl_friend_group where user_id = %d and group_id = %d;";
        char sql[2048];
        sprintf(sql, delete_sql, user_id, group_id);
        printSql2Log(sql);
        if(conn->update(sql))
        {
            ret = true;
            //删除成功，将原来该分组的所有好友移动到默认分组
            char update_sql[] = "UPDATE yl_friend set group_id = 1 where user_id = %d and group_id = %d";
            sprintf(sql, update_sql, user_id, group_id);
            printSql2Log(sql);
            conn->update(sql);
        }
        else
            ret = false;
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}

bool FriendListModel::moveFriendToGroup(uint32_t user_id, uint32_t friend_id, uint32_t group_id)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();

    if (conn)
    {
        //移动好友到指定分组
        char update_sql[] = "UPDATE yl_friend set group_id = %d where user_id = %d and friend_id = %d";
        char sql[2048];
        sprintf(sql, update_sql, group_id, user_id, friend_id);
        printSql2Log(sql);

        if (conn->update(sql))
            ret = true;
        else
            ret = false;
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}

bool FriendListModel::deleteFriend(uint32_t user_id, uint32_t friend_id)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        //删除好友,只需将status字段由1改成2
        string update_sql = "UPDATE yl_friend set status = 4 where user_id = "+ to_string(user_id) +" and friend_id = " + to_string(friend_id);
        printSql2Log(update_sql.c_str());

        if (conn->update(update_sql))
            ret = true;
        else
            ret = false;
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}

bool FriendListModel::modifyFriendRemark(uint32_t user_id, uint32_t friend_id, const std::string &friendRemark)
{

    bool ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        //修改好友备注
        string update_sql = "UPDATE yl_friend set friend_remark = '" + friendRemark +"' where user_id = "+ to_string(user_id) +" and friend_id = " + to_string(friend_id);
        printSql2Log(update_sql.c_str());

        if (conn->update(update_sql))
            ret = true;
        else
            ret = false;
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}

uint32_t FriendListModel::getRelationId(uint32_t userId, uint32_t friendId)
{
    uint32_t relationId = 0;

    DBConn *dbConn = DBManager::instance()->getConnection();

    if (!dbConn)
    {
        return relationId;
    }

    string strSql = "SELECT id FROM yl_friend WHERE user_id=" + to_string(userId) + " and friend_id=" + to_string(friendId);
    printSql2Log(strSql.c_str());
    ResultSet *resultSet = dbConn->query(strSql);
    if (resultSet)
    {
        while (resultSet->next())
        {
            relationId = (uint32_t)resultSet->getInt("id");
        }
        delete resultSet;
    }

    DBManager::instance()->releaseConnection(dbConn);
    return relationId;
}


bool FriendListModel::searchFriend(std::string &searchData, base::SearchType searchType, list<base::FriendInfo> &result)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {

        string querySql;
        if (searchType == base::SEARCH_TYPE_ACCOUNT)
        {
            querySql = "SELECT * FROM yl_user WHERE user_account =" + searchData;
        }
        else if (searchType == base::SEARCH_TYPE_NICKNAME)
        {
            querySql = "SELECT * FROM yl_user WHERE user_nickname LIKE '%"+ searchData +"%';";
        }

        ResultSet *resultSet = conn->query(querySql);

        if (resultSet)
        {
            ret = true;
            while (resultSet->next())
            {
                base::FriendInfo info;
                info.set_friend_id((uint32_t)resultSet->getInt("user_id"));
                info.set_friend_account((uint32_t)resultSet->getInt("user_account"));
                info.set_friend_header_url(resultSet->getString("user_header"));
                info.set_friend_nick(resultSet->getString("user_nickname"));
                result.push_back(info);
            }

            delete resultSet;
        }

    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}

bool FriendListModel::addFriend(uint32_t userId, uint32_t friendId, uint32_t groupId, const std::string &remark, uint32_t status)
{
    bool ret = false;

    uint32_t relationId = getRelationId(userId, friendId);
    auto conn = DBManager::instance()->getConnection();
    uint32_t createTime = (uint32_t)time(nullptr);
    if (relationId == 0)
    {
        if (conn)
        {
            string insertSql = "INSERT INTO yl_friend(user_id, friend_id, group_id, created, friend_remark, status) VALUES(?, ?, ?, ?, ?, ?)";
            printSql2Log(insertSql.c_str());
            PrepareStatement *prepareStatement = new PrepareStatement;
            if (prepareStatement->init(conn->getMysql(), insertSql))
            {
                int index = 0;
                prepareStatement->setParam(index++, userId);
                prepareStatement->setParam(index++, friendId);
                prepareStatement->setParam(index++, groupId);
                prepareStatement->setParam(index++, createTime);
                prepareStatement->setParam(index++, remark);
                prepareStatement->setParam(index++, status);
                ret = prepareStatement->executeUpdate();
            }

        }
    }
    else
    {
        string childSql =  (groupId == 0 ? "" : "group_id = ? ,");
        string updateSql = "UPDATE yl_friend SET status = ?,  " + childSql +  "created = ?, friend_remark = ? WHERE id = ?";
        printSql2Log(updateSql.c_str());
        PrepareStatement *prepareStatement = new PrepareStatement;
        if (prepareStatement->init(conn->getMysql(), updateSql))
        {
            int index = 0;
            prepareStatement->setParam(index++, status);
            if (groupId != 0)
                prepareStatement->setParam(index++, groupId);
            prepareStatement->setParam(index++, createTime);
            prepareStatement->setParam(index++, remark);
            prepareStatement->setParam(index++, relationId);
            ret = prepareStatement->executeUpdate();
        }
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;

}


uint32_t  FriendListModel::getRequestId(uint32_t userId, uint32_t friendId)
{
    uint32_t requestId = 0;

    DBConn *dbConn = DBManager::instance()->getConnection();

    if (!dbConn)
    {
        return requestId;
    }

    string strSql = "SELECT id FROM yl_friend_request WHERE request_sender_id =" + to_string(userId) + " and request_receiver_id = " + to_string(friendId) + " and request_handle_time = 0";
    printSql2Log(strSql.c_str());
    ResultSet *resultSet = dbConn->query(strSql);
    if (resultSet)
    {
        while (resultSet->next())
        {
            requestId = (uint32_t)resultSet->getInt("id");
        }
        delete resultSet;
    }

    DBManager::instance()->releaseConnection(dbConn);
    return requestId;
}

bool FriendListModel::saveAddRequest(uint32_t userId, uint32_t otherId, const std::string &validateData)
{
    bool ret = false;
    auto conn = DBManager::instance()->getConnection();
    uint32_t createTime = (uint32_t)time(nullptr);

    if (conn)
    {

        uint32_t requestId = getRequestId(userId, otherId);

        if (requestId == 0)
        {
            std::string sql = "INSERT INTO yl_friend_request(request_sender_id, request_receiver_id, request_create_time, request_validate_data) VALUES(?, ?, ?, ?)";
            printSql2Log(sql.c_str());

            PrepareStatement *prepareStatement = new PrepareStatement();
            if (prepareStatement->init(conn->getMysql(), sql)) {
                int index = 0;
                prepareStatement->setParam(index++, userId);
                prepareStatement->setParam(index++, otherId);
                prepareStatement->setParam(index++, createTime);
                prepareStatement->setParam(index++, validateData);
                ret = prepareStatement->executeUpdate();
            }
        }
        else
        {
            std::string sql = "UPDATE yl_friend_request SET request_create_time = " + to_string(createTime) + ", request_validate_data = " + validateData + " WHERE id = " + to_string(requestId);
            printSql2Log(sql.c_str());
            ret = conn->update(sql);
        }
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}


bool FriendListModel::updateAddRequest(uint32_t userId, uint32_t otherId, uint32_t resultId)
{
    bool ret = false;
    auto conn = DBManager::instance()->getConnection();
    uint32_t updateTime = (uint32_t)time(nullptr);

    if (conn)
    {
        std::string sql = "UPDATE yl_friend_request SET request_handle_time = ?, request_handle_reslut = ? WHERE request_sender_id = ? AND request_receiver_id = ? AND request_handle_time = 0";
        printSql2Log(sql.c_str());
        PrepareStatement *prepareStatement = new PrepareStatement();
        if (prepareStatement->init(conn->getMysql(), sql))
        {
            int index = 0;
            prepareStatement->setParam(index++, updateTime);
            prepareStatement->setParam(index++, resultId);
            prepareStatement->setParam(index++, otherId);
            prepareStatement->setParam(index++, userId);
            ret = prepareStatement->executeUpdate();
        }
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}

bool FriendListModel::getAddRequestHistory(uint32_t userId, std::list<base::AddRequestInfo> &history)
{
    bool ret = false;
    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT r.id, u.user_id, r.request_handle_reslut, r.request_handle_time, r.request_validate_data, u.user_header, u.user_nickname FROM yl_friend_request AS r, yl_user AS u WHERE request_receiver_id =" + to_string(userId) + " AND r.request_sender_id = u.user_id;";
        printSql2Log(sql.c_str());
        ResultSet *resultSet = conn->query(sql);

        if (resultSet)
        {
            while (resultSet->next())
            {
                base::AddRequestInfo info;
                info.set_id((uint32_t)resultSet->getInt("id"));
                info.set_other_id((uint32_t)resultSet->getInt("user_id"));
                info.set_result_id((uint32_t)resultSet->getInt("request_handle_reslut"));
                info.set_handle_time((uint32_t)resultSet->getInt("request_handle_time"));
                info.set_validate_data(resultSet->getString("request_validate_data"));
                info.set_other_head_url(resultSet->getString("user_header"));
                info.set_other_nick(resultSet->getString("user_nickname"));
                history.push_back(info);
            }
            delete resultSet;
        }
        ret = true;
    }
    DBManager::instance()->releaseConnection(conn);
    return ret;
}