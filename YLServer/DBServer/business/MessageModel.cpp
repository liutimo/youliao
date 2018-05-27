//
// Created by liuzheng on 18-4-17.
//

#include "MessageModel.h"
#include "AudioModel.h"
#include "../DBPool.h"
#include "util/util.h"
#include "FriendListModel.h"

using namespace std;

MessageModel* MessageModel::m_instance = nullptr;

MessageModel* MessageModel::instance()
{
    if (!m_instance)
        m_instance = new MessageModel();
    return m_instance;
}

MessageModel::MessageModel()
{

}

MessageModel::~MessageModel()
{

}

//bool MessageModel::getFriendOnlineStatus(uint32_t friend_id, int &msg_idx)
//{
//    auto conn = CacheManager::instance()->getCacheConn("OnlineUser");
//
//    msg_idx = 0;
//    if (conn)
//    {
//        string msgIdx =  conn->hget("user_map", to_string(friend_id));
//        if (msgIdx.empty())
//            return false;
//        else
//        {
//            msg_idx = atoi(msgIdx.c_str());
//            return true;
//        }
//
//    }
//    CacheManager::instance()->releaseCacheConn(conn);
//
//    return false;
//}

bool MessageModel::saveMessage(uint32_t relatedId, uint32_t senderId, uint32_t receiverId,
                               uint32_t messageType, uint32_t createTime, uint32_t messageId, const std::string &content)
{
    bool ret = false;

    if (0 == senderId || 0 == receiverId)
    {
        log("无效：%u->%u", senderId, receiverId);
        return ret;
    }

    DBConn *dbConn = DBManager::instance()->getConnection();

    if (!dbConn)
    {
        log("无效的数据库连接！");
        return ret;
    }
    //后期分表后可以在这里更改表名
    string strTableName = "yl_message";
    string strSql = "insert into " + strTableName + " (relate_id, sender_id, receiver_id, message_id, message_content, "
                    "message_type, message_updated, message_created) values(?, ?, ?, ?, ?, ?, ?, ?)";

    PrepareStatement *pStmt = new PrepareStatement;

    if (pStmt->init(dbConn->getMysql(), strSql))
    {
        uint32_t index = 0;
        pStmt->setParam(index++, relatedId);
        pStmt->setParam(index++, senderId);
        pStmt->setParam(index++, receiverId);
        pStmt->setParam(index++, messageId);
        pStmt->setParam(index++, content);
        pStmt->setParam(index++, messageType);
        pStmt->setParam(index++, createTime);
        pStmt->setParam(index++, createTime);

        ret = pStmt->executeUpdate();
    }
    delete pStmt;
    DBManager::instance()->releaseConnection(dbConn);

    if (ret)
    {
        log("插入消息记录成功!");
    }
    else
    {
        log("插入消息记录失败！");
    }

    return ret;
}


bool MessageModel::saveAudioMessage(uint32_t relatedId, uint32_t senderId, uint32_t receiverId, uint32_t createTime,
                                    uint32_t messageId, const std::string &content)
{
    bool ret = false;
    ret = saveMessage(relatedId, senderId, receiverId, base::MESSAGE_TYPE_SINGLE_AUDIO, createTime, messageId, content);
    return ret;

}

bool MessageModel::saveGroupMesage(uint32_t groupId, uint32_t senderId, uint32_t messageType, uint32_t createTime,
                                   uint32_t messageId, const std::string &content)
{
    bool ret = false;

    if (0 == senderId || groupId == 0)
    {
        return ret;
    }

    DBConn *dbConn = DBManager::instance()->getConnection();

    if (!dbConn)
    {
        log("无效的数据库连接！");
        return ret;
    }
    //后期分表后可以在这里更改表名
    string strTableName = "yl_group_message";
    string strSql = "INSERT INTO " + strTableName + " (group_id, sender_id, msg_id, content, type, updated, created) "
                    "values(?, ?, ?, ?, ?, ?, ?)";

    PrepareStatement *pStmt = new PrepareStatement;

    if (pStmt->init(dbConn->getMysql(), strSql))
    {
        uint32_t index = 0;
        pStmt->setParam(index++, groupId);
        pStmt->setParam(index++, senderId);
        pStmt->setParam(index++, messageId);
        pStmt->setParam(index++, content);
        pStmt->setParam(index++, messageType);
        pStmt->setParam(index++, createTime);
        pStmt->setParam(index++, createTime);
        ret = pStmt->executeUpdate();
    }
    delete pStmt;
    DBManager::instance()->releaseConnection(dbConn);

    if (ret)
    {
        log("插入消息记录成功!");
    }
    else
    {
        log("插入消息记录失败！");
    }

    return ret;
}


bool MessageModel::getLastMessage(uint32_t senderId, uint32_t receiverId, std::string &content)
{
//
    bool ret = false;

    uint32_t relateId = FriendListModel::instance()->getRelationId(senderId, receiverId);

    if (relateId == 0)
    {
        log("用户%d和用户%d不是好友关系。无法获取消息！", senderId, receiverId);
        return ret;
    }

    DBConn *dbConn = DBManager::instance()->getConnection();
    if(!dbConn)
        return ret;
    std::string querySql = "SELECT message_content FROM yl_message FORCE INDEX(relateId_status_created_IDX) "
                           "WHERE relate_id =" + std::to_string(relateId) +" AND message_status=0 ORDER "
                           "BY message_created DESC LIMIT 1";
    printSql2Log(querySql.c_str());

    ResultSet *resultSet = dbConn->query(querySql);

    if (!resultSet)
    {
        log("执行SQL失败");

    }
    else
    {
        while(resultSet->next())
        {
            content = resultSet->getString("message_content");
        }
        ret = true;
        delete resultSet;
    }

    DBManager::instance()->releaseConnection(dbConn);
    return ret;
}



bool MessageModel::getLatestMsgId(uint32_t senderId, uint8_t receiverId, uint32_t &msgId)
{
    bool ret = false;

    uint32_t relateId = FriendListModel::instance()->getRelationId(senderId, receiverId);

    if (relateId == 0)
    {
        log("用户%d和用户%d不是好友关系。无法获取消息！", senderId, receiverId);
        return ret;
    }

    DBConn *dbConn = DBManager::instance()->getConnection();
    if(!dbConn)
        return ret;
    std::string querySql = "SELECT message_id FROM yl_message FORCE INDEX(relateId_status_created_IDX) WHERE relate_id "
                           "=" + std::to_string(relateId) +" AND message_status=0 ORDER BY message_created DESC LIMIT 1";
    printSql2Log(querySql.c_str());

    ResultSet *resultSet = dbConn->query(querySql);

    if (!resultSet)
    {
        log("执行SQL失败");

    }
    else
    {
        while(resultSet->next())
        {
            msgId = (uint32_t)resultSet->getInt("message_id");
        }
        ret = true;
        delete resultSet;
    }

    DBManager::instance()->releaseConnection(dbConn);
    return ret;
}
