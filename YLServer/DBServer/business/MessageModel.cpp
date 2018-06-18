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

bool MessageModel::saveMessage(uint32_t senderId, uint32_t receiverId, uint32_t messageType,
                               uint32_t createTime, uint32_t messageId, const std::string &content)
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
    string strSql = "insert into " + strTableName + " (sender_id, receiver_id, message_id, message_content, "
                    "message_type, message_updated, message_created) values(?, ?, ?, ?, ?, ?, ?)";

    PrepareStatement *pStmt = new PrepareStatement;

    if (pStmt->init(dbConn->getMysql(), strSql))
    {
        uint32_t index = 0;
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


bool MessageModel::saveAudioMessage(uint32_t senderId, uint32_t receiverId, uint32_t createTime,
                                    uint32_t messageId, const std::string &content)
{
    bool ret = false;
    ret = saveMessage(senderId, receiverId, base::MESSAGE_TYPE_SINGLE_AUDIO, createTime, messageId, content);
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


bool MessageModel::getLastMessage(uint32_t senderId, uint32_t receiverId, std::string &content, uint32_t &latestTime)
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
    std::string querySql = "SELECT message_content, message_created,message_id FROM yl_message "
                           "FORCE INDEX(relateId_status_created_IDX) WHERE sender_id = " + std::to_string(senderId) +
                           " AND receiver_id = " + std::to_string(receiverId) + " UNION "
                           "SELECT message_content, message_created,message_id FROM yl_message "
                           "FORCE INDEX(relateId_status_created_IDX) WHERE sender_id = " + std::to_string(receiverId) +
                           " AND receiver_id = " + std::to_string(senderId) +
                           " ORDER BY message_id DESC LIMIT 1 ";
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
            content     = resultSet->getString("message_content");
            latestTime  = (uint32_t)resultSet->getInt("message_created");
        }
        ret = true;
        delete resultSet;
    }

    DBManager::instance()->releaseConnection(dbConn);
    return ret;
}


bool MessageModel::getLastestGroupMessage(uint32_t groupId, std::string &content, uint32_t &latestTime)
{
    bool ret = false;

    DBConn *dbConn = DBManager::instance()->getConnection();

    if (dbConn)
    {

        std::string querySql = "SELECT content, created FROM yl_group_message WHERE group_id = " + std::to_string(groupId) +
                               " ORDER BY created DESC LIMIT 1;";
        printSql2Log(querySql.c_str());

        ResultSet *resultSet = dbConn->query(querySql);

        if (!resultSet) {
            log("执行SQL失败");

        } else {
            while (resultSet->next()) {
                content = resultSet->getString("content");
                latestTime = (uint32_t)resultSet->getInt("created");
            }
            ret = true;
            delete resultSet;
        }

    }
    DBManager::instance()->releaseConnection(dbConn);
    return ret;
}


bool MessageModel::getLatestMsgId(uint32_t senderId, uint32_t receiverId, uint32_t &msgId)
{
    bool ret = false;

    DBConn *dbConn = DBManager::instance()->getConnection();
    if(!dbConn)
        return ret;
    std::string querySql = "SELECT message_content, message_created,message_id FROM yl_message "
                           "FORCE INDEX(relateId_status_created_IDX) WHERE sender_id = " + std::to_string(senderId) +
                           " AND receiver_id = " + std::to_string(receiverId) + " UNION "
                           "SELECT message_content, message_created,message_id FROM yl_message "
                           "FORCE INDEX(relateId_status_created_IDX) WHERE sender_id = " + std::to_string(receiverId) +
                           " AND receiver_id = " + std::to_string(senderId) +
                           " ORDER BY message_id DESC LIMIT 1 ";
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


uint32_t MessageModel::getMsgIndex(uint32_t senderId, uint32_t receiverId, uint32_t msgId)
{
    uint32_t index = 0;

    DBConn *dbConn = DBManager::instance()->getConnection();
    if(!dbConn)
        return index;
    std::string querySql = "SELECT id FROM yl_message WHERE sender_id = " + std::to_string(senderId) +
            " AND receiver_id = " + std::to_string(receiverId) + " AND message_id  = " + std::to_string(msgId);
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
            index = (uint32_t)resultSet->getInt("id");
        }
        delete resultSet;
    }

    DBManager::instance()->releaseConnection(dbConn);
    return index;
}

bool MessageModel::messageAck(uint32_t senderId, uint32_t receiverId, uint32_t msgId)
{
    bool ret = false;

    uint32_t msgIndex = getMsgIndex(senderId, receiverId, msgId);
    if (msgIndex == 0)
        msgIndex = getMsgIndex(receiverId, senderId, msgId);

    if (msgIndex == 0)
    {
        log("用户%d和用户%d从未有过交流！", senderId, receiverId);
        return ret;
    }

    DBConn *dbConn = DBManager::instance()->getConnection();
    if(!dbConn)
        return ret;
    std::string updateSql = "UPDATE yl_message SET message_status = 1 WHERE id = " + std::to_string(msgIndex);
    printSql2Log(updateSql.c_str());

    ret = dbConn->update(updateSql);

    DBManager::instance()->releaseConnection(dbConn);
    return ret;
}


bool MessageModel::getOfflineMessage(uint32_t userId, message::GetOfflineMessageRespone &respone)
{
    bool ret = false;

    DBConn *conn = DBManager::instance()->getConnection();

    if (!conn)
        return ret;

    std::string querySql = "SELECT * FROM yl_message WHERE message_status = 0 AND receiver_id = " + std::to_string(userId);

    printSql2Log(querySql.c_str());

    ResultSet *resultSet = conn->query(querySql);

    if (resultSet)
    {
        while (resultSet->next())
        {
            message::MessageData *data = respone.add_msg_data();
            data->set_relate_id((uint32_t)resultSet->getInt("relate_id"));
            data->set_from_user_id((uint32_t)resultSet->getInt("sender_id"));
            data->set_to_id(userId);
            data->set_msg_id((uint32_t)resultSet->getInt("message_id"));
            data->set_create_time((uint32_t)resultSet->getInt("message_created"));

            base::MessageType type = (base::MessageType)resultSet->getInt("message_type");
            data->set_message_type(type);

            if (type == base::MESSAGE_TYPE_SINGLE_AUDIO)
            {
                uint32_t audioId = (uint32_t)resultSet->getInt("message_content");
                if (audioId != 0)
                {
                    uint32_t audioDuration = 0;
                    string audioPath = "";
                    AudioModel::instance()->getAudioInfo(audioId, audioDuration, audioPath);
                    data->set_message_data(audioPath);
                    data->set_audio_time(audioDuration);
                }
            }
            else if (type == base::MESSAGE_TYPE_SINGLE_TEXT)
                data->set_message_data(resultSet->getString("message_content"));

        }
        ret = true;

        delete resultSet;
    }

    DBManager::instance()->releaseConnection(conn);

    return ret;
}

bool MessageModel::getGroupOfflineMessage(uint32_t groupId, uint32_t currentMsgId, message::GetGroupOfflineMessageRespone &respone)
{
    bool ret = false;

    DBConn *conn = DBManager::instance()->getConnection();

    if (!conn)
        return ret;

    std::string querySql = "SELECT sender_id, msg_id, content, type, created "
                           "FROM yl_group_message "
                           "WHERE group_id = "+ std::to_string(groupId)+ " AND msg_id > " + std::to_string(currentMsgId);

    printSql2Log(querySql.c_str());

    ResultSet *resultSet = conn->query(querySql);

    if (resultSet)
    {
        while (resultSet->next())
        {
            message::MessageData *data = respone.add_msg_data();
            data->set_msg_id((uint32_t)resultSet->getInt("msg_id"));
            data->set_create_time((uint32_t)resultSet->getInt("created"));
            data->set_message_data(resultSet->getString("content"));
            data->set_from_user_id((uint32_t)resultSet->getInt("sender_id"));
            data->set_to_id(groupId);
            data->set_message_type((base::MessageType)resultSet->getInt("type"));
        }
        ret = true;

        delete resultSet;
    }

    DBManager::instance()->releaseConnection(conn);
    return ret;
}
