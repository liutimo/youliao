//
// Created by liuzheng on 18-4-18.
//

#include "SessionModel.h"
#include "MessageModel.h"
#include "../DBPool.h"
#include "util/util.h"

SessionModel* SessionModel::m_instance = nullptr;

SessionModel* SessionModel::instance()
{
    if (m_instance == nullptr)
        m_instance = new SessionModel();
    return m_instance;
}

SessionModel::SessionModel()
{

}

SessionModel::~SessionModel()
{

}


uint32_t SessionModel::getSessionId(uint32_t userId, uint32_t otherId, uint32_t type, bool flag)
{
    uint32_t sessionId = 0;

    DBConn *dbConn = DBManager::instance()->getConnection();
    if(!dbConn)
    {
        log("获取数据库连接失败!");
        return sessionId;
    }

    //不管session是否删除
    std::string strSql = "SELECT session_id FROM yl_session where user_id=" + std::to_string(userId) + " AND other_id=" + std::to_string(otherId) + " AND session_type=" + std::to_string(type);

    //选择未删除的session
    if (!flag)
        strSql += + " AND session_status=0";

    ResultSet *resultSet = dbConn->query(strSql);

    if (resultSet)
    {
        while (resultSet->next())
        {
            sessionId = (uint32_t)resultSet->getInt("session_id");
        }

        delete resultSet;
    }
    DBManager::instance()->releaseConnection(dbConn);

    return sessionId;
}

uint32_t SessionModel::addSession(uint32_t userId, uint32_t otherId, uint32_t type)
{
    uint32_t createdTime = (uint32_t)time(nullptr);
    uint32_t sessionId = getSessionId(userId, otherId, type, true);

    DBConn *dbConn = DBManager::instance()->getConnection();

    if (!dbConn)
    {
        log("获取数据库连接失败!");
        sessionId = 0;
        return sessionId;
    }

    std::string strSql;

    //session 不存在， insert
    if (sessionId == 0)
    {
        strSql = "INSERT INTO yl_session(user_id, other_id, session_type, session_created, session_updated) values(?, ?, ?, ?, ?)";
        printSql2Log(strSql.c_str());
        PrepareStatement *pStmt = new PrepareStatement;
        if (pStmt->init(dbConn->getMysql(), strSql))
        {
            uint32_t index = 0;
            pStmt->setParam(index++, userId);
            pStmt->setParam(index++, otherId);
            pStmt->setParam(index++, type);
            pStmt->setParam(index++, createdTime);
            pStmt->setParam(index++, createdTime);
            bool ret = pStmt->executeUpdate();
            if (ret)
            {
                sessionId = dbConn->getInsertId();
            }
            else
            {
                log("SQL 执行失败");
            }
        }
        delete pStmt;
    }
    //Session存在， update status
    else
    {
        strSql = "UPDATE yl_session SET session_status=0, session_updated=" + std::to_string(createdTime) + " WHERE session_id=" + std::to_string(sessionId);
        printSql2Log(strSql.c_str());

        if(!dbConn->update(strSql))
        {
            log("更新session失败");
            sessionId = 0;
        }
    }

    DBManager::instance()->releaseConnection(dbConn);

    return sessionId;
}

bool SessionModel::updateSession(uint32_t sessionId)
{
    bool ret = false;
    DBConn *dbConn = DBManager::instance()->getConnection();
    if(!dbConn)
    {
        return ret;
    }

    uint32_t updateTime = (uint32_t)time(nullptr);

    std::string updateSql = "UPDATE yl_session SET session_updated=" + std::to_string(updateTime) + " WHERE session_id=" + std::to_string(sessionId);

    ret = dbConn->update(updateSql);

    if (!ret)
        log("更新Session %d失败！", sessionId);
    else
        log("更新Session %d成功！", sessionId);

    DBManager::instance()->releaseConnection(dbConn);

    return ret;
}

bool SessionModel::removeSession(uint32_t sessionId)
{
    bool ret = false;
    DBConn *dbConn = DBManager::instance()->getConnection();

    if (!dbConn)
        return ret;

    std::string removeSql = "UPDATE yl_session set session_status=1 WHERE session_id=" + std::to_string(sessionId);
    printSql2Log(removeSql.c_str());

    ret = dbConn->update(removeSql);

    if (!ret)
        log("删除Session %d失败！", sessionId);
    else
        log("删除Session %d成功！", sessionId);

    DBManager::instance()->releaseConnection(dbConn);

    return ret;
}

bool SessionModel::topSession(uint32_t sessionId)
{
    bool ret = false;
    DBConn *dbConn = DBManager::instance()->getConnection();

    if (!dbConn)
        return ret;

    std::string removeSql = "UPDATE yl_session SET session_top=CASE session_top WHEN 1 THEN 2 WHEN 2 THEN 1 END WHERE session_id = " + std::to_string(sessionId);
    printSql2Log(removeSql.c_str());

    ret = dbConn->update(removeSql);

    if (!ret)
        log("置顶Session %d失败！", sessionId);
    else
        log("置顶Session %d成功！", sessionId);

    DBManager::instance()->releaseConnection(dbConn);

    return ret;
}

bool SessionModel::getSessions(uint32_t userId, std::list<base::SessionInfo> &sessionList)
{

    bool ret = false;
    DBConn *dbConn = DBManager::instance()->getConnection();

    if (!dbConn)
        return ret;

    std::string querySql = "SELECT session_id, other_id, session_type, session_top, session_updated FROM yl_session WHERE session_status=0 AND user_id=" + std::to_string(userId) + " order by session_updated DESC";

    printSql2Log(querySql.c_str());

    ResultSet *resultSet = dbConn->query(querySql);

    if (resultSet)
    {
        while (resultSet->next())
        {
            uint32_t friId = (uint32_t)resultSet->getInt("other_id");
            base::SessionInfo sessionInfo;
            sessionInfo.set_session_id((uint32_t)resultSet->getInt("session_id"));
            sessionInfo.set_other_id(friId);
            sessionInfo.set_session_type((uint32_t)resultSet->getInt("session_type"));
            sessionInfo.set_session_top((uint32_t)resultSet->getInt("session_top"));
            sessionInfo.set_session_update((uint32_t)resultSet->getInt("session_updated"));
            std::string content;
            if(MessageModel::instance()->getLastMessage(userId, (uint32_t)resultSet->getInt("other_id"), content))
                sessionInfo.set_last_message_data(content);
            sessionList.push_back(sessionInfo);
        }

        delete resultSet;
    }

    DBManager::instance()->releaseConnection(dbConn);

    return ret;
}