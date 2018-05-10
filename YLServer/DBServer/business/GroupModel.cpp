//
// Created by liuzheng on 18-5-7.
//

#include "GroupModel.h"
#include "../DBPool.h"
#include "util/util.h"
GroupModel* GroupModel::m_instance = nullptr;


GroupModel* GroupModel::instance()
{
    if (m_instance == nullptr)
        m_instance = new GroupModel();
    return m_instance;
}



GroupModel::GroupModel()
{

}

uint32_t GroupModel::createGroup(uint32_t userId, std::string groupName, base::GroupType type, base::GroupVerifyType verify, uint32_t max_members)
{
    uint32_t groupId = 0;
    auto conn = DBManager::instance()->getConnection();
    uint32_t created = (uint32_t)time(nullptr);
    if (conn)
    {
        std::string sql = "INSERT INTO yl_group(group_name, group_creator, group_type, group_user_max_count, group_created, group_verify)"
                          " VALUES(?, ?, ?, ?, ?, ?)";
        printSql2Log(sql.c_str());
        PrepareStatement *prepareStatement = new PrepareStatement;
        if (prepareStatement->init(conn->getMysql(), sql))
        {
            int index = 0;
            int groupType =(uint32_t)type;
            int verifyType = (uint32_t)verify;
            prepareStatement->setParam(index++, groupName);
            prepareStatement->setParam(index++, userId);
            prepareStatement->setParam(index++, groupType);
            prepareStatement->setParam(index++, max_members);
            prepareStatement->setParam(index++, created);
            prepareStatement->setParam(index++, verifyType);
            auto ret = prepareStatement->executeUpdate();
            if (ret)
                groupId = conn->getInsertId();
        }
    }
    DBManager::instance()->releaseConnection(conn);
    return groupId;
}

bool GroupModel::addMembers(uint32_t groupId, const std::list<uint32_t> &members)
{
    bool ret = false;
    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "INSERT INTO yl_group_member(group_id, member_id) VALUES ";

        for (uint32_t memId : members)
        {
            sql += "(" + std::to_string(groupId) + ", " + std::to_string(memId) +"),";
        }
        sql.pop_back();
        printSql2Log(sql.c_str());

       ret = conn->update(sql);
    }
    DBManager::instance()->releaseConnection(conn);
    return ret;
}


bool GroupModel::getGroupInfoByGroupId(uint32_t groupId, base::GroupInfo &groupInfo)
{
    bool ret = false;
    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT * FROM yl_group WHERE group_id = " + std::to_string(groupId);
        printSql2Log(sql.c_str());

        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                groupInfo.set_group_id((uint32_t)resultSet->getInt("group_id"));
                groupInfo.set_group_created((uint32_t)resultSet->getInt("group_created"));
                groupInfo.set_group_name(resultSet->getString("group_name"));
                groupInfo.set_group_head(resultSet->getString("group_head"));
                groupInfo.set_group_capacity((uint32_t)resultSet->getInt("group+user_max_count"));
                groupInfo.set_group_creator((uint32_t)resultSet->getInt("group_creator"));

                //查找群管理员成员
                std::list<uint32_t> groupManagers;
                getGroupManagers(groupId, groupManagers);
                for (uint32_t manager : groupManagers)
                    groupInfo.add_managers(manager);

                //查找群管理员成员
                std::list<uint32_t> groupMembers;
                getGroupMembers(groupId, groupMembers);
                for (uint32_t member : groupMembers)
                    groupInfo.add_members(member);
            }

            delete resultSet;
            ret = true;
        }

    }
    DBManager::instance()->releaseConnection(conn);
    return ret;
}



bool GroupModel::getOtherGroupByUserId(uint32_t userId, std::list<uint32_t> &groups)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT group_id FROM yl_group_member WHERE status = 1 AND member_id = " + std::to_string(userId);
        printSql2Log(sql.c_str());

        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                groups.push_back((uint32_t)resultSet->getInt("group_id"));
            }

            delete resultSet;
            ret = true;
        }

    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}


//获取用户创建的群
bool GroupModel::getSelfGroupByUserId(uint32_t userId, std::list<uint32_t> &groups)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT group_id FROM yl_group WHERE  group_creator = " + std::to_string(userId);
        printSql2Log(sql.c_str());
        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                groups.push_back((uint32_t)resultSet->getInt("group_id"));
            }

            delete resultSet;
            ret = true;
        }
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}


bool GroupModel::getGroupManagers(uint32_t groupId, std::list<uint32_t> &managers)
{
    auto ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT member_id FROM yl_group_member WHERE type = 1 AND group_id = " + std::to_string(groupId);
        printSql2Log(sql.c_str());

        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                managers.push_back((uint32_t)resultSet->getInt("member_id"));
            }

            delete resultSet;
            ret = true;
        }
    }
    DBManager::instance()->releaseConnection(conn);
    return ret;
}


bool GroupModel::getGroupMembers(uint32_t groupId, std::list<uint32_t> &members)
{
    auto ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT member_id FROM yl_group_member WHERE type =0 AND group_id = " + std::to_string(groupId);
        printSql2Log(sql.c_str());

        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                members.push_back((uint32_t)resultSet->getInt("member_id"));
            }
            delete resultSet;
            ret = true;
        }
    }
    DBManager::instance()->releaseConnection(conn);
    return ret;
}
