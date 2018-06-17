//
// Created by liuzheng on 18-5-7.
//

#include "GroupModel.h"
#include "LoginModel.h"
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
    addCreator(groupId, userId);
    return groupId;
}

bool GroupModel::addMembers(uint32_t groupId, const std::list<uint32_t> &members)
{
    bool ret = false;

    for (uint32_t memId : members)
    {
        addOne(groupId, memId, 0, 0);
    }

    return ret;
}

//添加成员
bool GroupModel::addMember(uint32_t groupId, uint32_t memberId)
{
    return addOne(groupId, memberId, 0, 1);
}

//添加管理员
bool GroupModel::addManager(uint32_t groupId, uint32_t managerId)
{
    return addOne(groupId, managerId, 1, 1);
}

//添加群主
bool GroupModel::addCreator(uint32_t groupId, uint32_t creator)
{
    return addOne(groupId, creator, 2, 1);
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
                groupInfo.set_group_id(groupId);
                groupInfo.set_group_created((uint32_t)resultSet->getInt("group_created"));
                groupInfo.set_group_name(resultSet->getString("group_name"));
                groupInfo.set_group_head(resultSet->getString("group_head"));
                groupInfo.set_group_capacity((uint32_t)resultSet->getInt("group_user_max_count"));
                groupInfo.set_group_creator((uint32_t)resultSet->getInt("group_creator"));
                groupInfo.set_group_verify_type((uint32_t)resultSet->getInt("group_verify"));
                groupInfo.set_group_latest_msg_id(getLatestMsgIdByGroupId(groupId));

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

//获取群成员
bool GroupModel::getMembersByGroupId(uint32_t groupId, std::list<base::MemberInfo> &members)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT member_id, group_card, last_chat_time FROM yl_group_member WHERE status = 1 AND group_id = " + std::to_string(groupId);
        printSql2Log(sql.c_str());
        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                base::MemberInfo memberInfo;
                uint32_t userId = (uint32_t)resultSet->getInt("member_id");
                memberInfo.set_user_id(userId);
                memberInfo.set_group_card(resultSet->getString("group_card"));
                memberInfo.set_last_chat_time((uint32_t)resultSet->getInt("last_chat_time"));

                base::UserInfo *info = new base::UserInfo;
                LoginModel::instance()->getUserInfo(userId, *info);
                memberInfo.set_allocated_user_info(info);
                members.push_back(memberInfo);
            }

            delete resultSet;
            ret = true;
        }
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}


//修改群名片
bool GroupModel::modifyGroupCard(uint32_t groupId, uint32_t memberId, const std::string &groupCard)
{
    auto ret = false;
    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "UPDATE yl_group_member SET group_card = '" + groupCard + "' WHERE group_id = " + std::to_string(groupId) + " AND member_id = " + std::to_string(memberId);
        printSql2Log(sql.c_str());
        ret = conn->update(sql);
    }
    DBManager::instance()->releaseConnection(conn);
    return ret;
}

//搜索群
bool GroupModel::searchGroup(uint32_t userId, const std::string &searchData, base::SearchType searchType, std::list<base::GroupInfo> &groupList)
{
    bool ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {

        std::string querySql;
        if (searchType == base::SEARCH_TYPE_ACCOUNT)
        {
            querySql = "SELECT * FROM yl_group WHERE group_id =" + searchData;
        }
        else if (searchType == base::SEARCH_TYPE_NICKNAME)
        {
            querySql = "SELECT * FROM yl_group WHERE group_name LIKE '%"+ searchData +"%';";
        }

        ResultSet *resultSet = conn->query(querySql);

        if (resultSet)
        {
            ret = true;
            while (resultSet->next())
            {
                base::GroupInfo groupInfo;
                uint32_t groupId = (uint32_t)resultSet->getInt("group_id");
                groupInfo.set_group_id(groupId);
                groupInfo.set_group_created((uint32_t)resultSet->getInt("group_created"));
                groupInfo.set_group_name(resultSet->getString("group_name"));
                groupInfo.set_group_head(resultSet->getString("group_head"));
                groupInfo.set_group_capacity((uint32_t)resultSet->getInt("group_user_max_count"));
                groupInfo.set_group_creator((uint32_t)resultSet->getInt("group_creator"));
                groupInfo.set_group_verify_type((uint32_t)resultSet->getInt("group_verify"));
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
                groupList.push_back(groupInfo);
            }

            delete resultSet;
        }

    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}


bool GroupModel::exitGroup(uint32_t groupId, uint32_t userId)
{
    bool ret = false;

    DBConn *conn = DBManager::instance()->getConnection();

    if (conn)
    {
        std::string updateSql = "UPDATE youliao.yl_group_member SET status = 2, group_card='', updated = "
                                + std::to_string(time(nullptr)) +  " WHERE group_id = " + std::to_string(groupId)
                                + " AND member_id = "  + std::to_string(userId);

        printSql2Log(updateSql.c_str());

        ret = conn->update(updateSql);
    }

    DBManager::instance()->releaseConnection(conn);

    return ret;
}


//设置管理员
bool GroupModel::setGroupManager(uint32_t groupId, uint32_t memberId)
{
    bool ret = false;

    DBConn *conn = DBManager::instance()->getConnection();

    if (conn)
    {
        std::string updateSql = "UPDATE yl_group_member SET type = 1, updated = "
                                + std::to_string(time(nullptr)) +  " WHERE group_id = " + std::to_string(groupId)
                                + " AND member_id = "  + std::to_string(memberId);

        printSql2Log(updateSql.c_str());

        ret = conn->update(updateSql);
    }

    DBManager::instance()->releaseConnection(conn);

    return ret;
}


bool GroupModel::modifyGroupHeader(uint32_t groupId, const std::string &url)
{
    bool ret = false;

    DBConn *conn = DBManager::instance()->getConnection();

    if (conn)
    {
        std::string updateSql = "UPDATE yl_group SET group_head = '" + url
                              + "' WHERE group_id = " + std::to_string(groupId);


        printSql2Log(updateSql.c_str());

        ret = conn->update(updateSql);
    }

    DBManager::instance()->releaseConnection(conn);

    return ret;
}


uint32_t GroupModel::getLatestMsgIdByGroupId(uint32_t groupId)
{
//    SELECT  msg_id FROM youliao.yl_group_message WHERE group_id = 26 ORDER BY msg_id DESC LIMIT 1;
    uint32_t msgId = 0;
    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT  msg_id FROM youliao.yl_group_message WHERE group_id = "
                          + std::to_string(groupId) + " ORDER BY msg_id DESC LIMIT 1;";
        printSql2Log(sql.c_str());

        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                msgId = (uint32_t)resultSet->getInt("msg_id");
            }

            delete resultSet;
        }
    }
    DBManager::instance()->releaseConnection(conn);

    return msgId;
}


base::GroupVerifyType  GroupModel::getVerofyTypeByGroupId(uint32_t groupId)
{
    base::GroupVerifyType type = base::GROUP_VERIFY_NEED;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT group_verify FROM yl_group WHERE group_id = " + std::to_string(groupId);
        printSql2Log(sql.c_str());

        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                uint32_t res = (uint32_t)resultSet->getInt("group_verify");
                type = static_cast<base::GroupVerifyType>(res);
            }

            delete resultSet;
        }
    }
    DBManager::instance()->releaseConnection(conn);

    return type;
}


uint32_t GroupModel::addNewGroupRequest(uint32_t requestUserId, uint32_t groupId, const std::string &validateData)
{
    uint32_t requestId = 0;

    bool flag = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "INSERT INTO yl_group_request(request_user_id, group_id, request_validate_data) "
                          "VALUES(?, ?, ?);";
        printSql2Log(sql.c_str());

        PrepareStatement *prepareStatement = new PrepareStatement;
        if (prepareStatement->init(conn->getMysql(), sql))
        {
            uint32_t idx = 0;
            prepareStatement->setParam(idx++, requestUserId);
            prepareStatement->setParam(idx++, groupId);
            prepareStatement->setParam(idx++, validateData);

            flag = prepareStatement->executeUpdate();
        }

        delete prepareStatement;
    }

    if (flag)
        requestId = conn->getInsertId();

    DBManager::instance()->releaseConnection(conn);

    return requestId;
}


//处理加群申请
bool GroupModel::updateAddGroupRequest(uint32_t requestUserId, uint32_t groupId,
                                       uint32_t handleUserId, base::GroupVerifyResult result)
{
    bool ret = false;

    DBConn *conn = DBManager::instance()->getConnection();

    if (conn)
    {
        std::string updateSql = "UPDATE yl_group_request SET  request_handle_time = CURRENT_TIMESTAMP, "
                                "request_handle_result = ?, request_handle_user = ? "
                                "WHERE request_user_id = ? AND group_id = ?;";

        printSql2Log(updateSql.c_str());

        PrepareStatement *prepareStatement = new PrepareStatement;
        if (prepareStatement->init(conn->getMysql(), updateSql))
        {
            uint32_t idx = 0;
            auto resCode = (uint32_t)result;
            prepareStatement->setParam(idx++, resCode);
            prepareStatement->setParam(idx++, handleUserId);
            prepareStatement->setParam(idx++, requestUserId);
            prepareStatement->setParam(idx++, groupId);

            ret = prepareStatement->executeUpdate();
        }
        delete prepareStatement;
    }

    DBManager::instance()->releaseConnection(conn);

    return ret;
}


//获取成员和群组的对应id
uint32_t GroupModel::getRelationId(uint32_t groupId, uint32_t userId)
{
    uint32_t relationId = 0;
    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT id FROM yl_group_member WHERE group_id = " + std::to_string(groupId) + " AND member_id = " + std::to_string(userId);
        printSql2Log(sql.c_str());

        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                relationId = (uint32_t)resultSet->getInt("id");
            }

            delete resultSet;
        }
    }
    DBManager::instance()->releaseConnection(conn);

    return relationId;
}



bool GroupModel::getGroupManagers(uint32_t groupId, std::list<uint32_t> &managers)
{
    auto ret = false;

    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT member_id FROM yl_group_member WHERE type = 1 AND status = 1 AND group_id = " + std::to_string(groupId);
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
        std::string sql = "SELECT member_id FROM yl_group_member WHERE type = 0 AND status = 1  AND group_id = " + std::to_string(groupId);
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

uint32_t GroupModel::getId(uint32_t groupId, uint32_t userId)
{
    uint32_t id = 0;
    auto conn = DBManager::instance()->getConnection();
    if (conn)
    {
        std::string sql = "SELECT id FROM yl_group_member WHERE group_id  = " + std::to_string(groupId) + " AND member_id = " + std::to_string(userId);
        printSql2Log(sql.c_str());

        ResultSet *resultSet = conn->query(sql);
        if (resultSet)
        {
            while (resultSet->next())
            {
                id = (uint32_t)resultSet->getInt("id");
            }
            delete resultSet;
        }
    }
    DBManager::instance()->releaseConnection(conn);
    return id;
}

bool GroupModel::addOne(uint32_t groupId, uint32_t userId, uint32_t type, uint32_t status)
{
    bool ret = false;
    uint32_t id = getId(groupId, userId);
    if (id == 0)
    {
        auto conn = DBManager::instance()->getConnection();
        if (conn)
        {
            uint32_t t = (uint32_t)time(nullptr);
            std::string sql = "INSERT INTO yl_group_member(group_id, member_id, type, last_chat_time, created, updated, status) VALUES( "
                              + std::to_string(groupId) + "," + std::to_string(userId) + ", " + std::to_string(type)
                              + ", " + std::to_string(t) + ", " + std::to_string(t) + ", " + std::to_string(t)
                              + ", " + std::to_string(status) + ")";

            printSql2Log(sql.c_str());
            ret = conn->update(sql);
        }
        DBManager::instance()->releaseConnection(conn);
    }
    else
    {
        auto conn = DBManager::instance()->getConnection();
        if (conn)
        {
            std::string sql = "UPDATE yl_group_member SET status = 1, type = " + std::to_string(type) + " WHERE id = " + std::to_string(id);
            printSql2Log(sql.c_str());
            ret = conn->update(sql);
        }
        DBManager::instance()->releaseConnection(conn);
    }
    return ret;
}
