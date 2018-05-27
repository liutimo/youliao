#include "yldatabase.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QDateTime>
#include "globaldata.h"
//YLDataBase* YLDataBase::m_instance = nullptr;

bool YLDataBase::m_first = true;

//YLDataBase* YLDataBase::instance()
//{
//    if (m_instance == nullptr)
//        m_instance = new YLDataBase();
//    return m_instance;
//}

YLDataBase::YLDataBase(QObject *parent) : QObject(parent)
{
    QString dbName = QString("%1.db").arg(GlobalData::getCurrLoginUserId());
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setHostName("localhost");
    m_database.setDatabaseName(dbName);
    m_database.setUserName("youliao");
    m_database.setPassword("123456");
    m_database.open();

    if (m_first)
    {
        createFriendTable();
        createFriendGroupTable();
        createMessageTable();
        createGroupTable();
        createGroupMemberTable();
        m_first = false;
    }
}


YLDataBase::~YLDataBase()
{
    m_database.close();
}



void YLDataBase::saveMessage(const MessageData &msg)
{
    QString sql = "INSERT INTO yl_message(sender_id, receiver_id, message_type, message_id, message_content, created) "
                  "VALUES(?, ?, ?, ?, ?, ?);";

    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(msg.from_user_id());
    query.addBindValue(msg.to_id());
    query.addBindValue(msg.message_type());
    query.addBindValue(msg.msg_id());
    query.addBindValue(msg.message_data().c_str());
    query.addBindValue(msg.create_time());

    bool ret = query.exec();

    if (ret)
        qDebug() << "插入消息成功" ;
    else
        qDebug() << "插入消息失败" << query.lastError().text();
}


QVector<QPair<uint32_t, QString>> YLDataBase::getRecentMessage(uint32_t friendId)
{
    QVector<QPair<uint32_t, QString>> vec;

    uint32_t currentTime = QDateTime::currentDateTime().toTime_t();
    uint32_t oneHourAgo  = currentTime - 3600;


    QString sql = QString("SELECT sender_id, message_content, created "
                  "FROM yl_message "
                  "WHERE sender_id = %1 AND "
                  "created BETWEEN %2 AND %3 "
                  "UNION  "
                  "SELECT sender_id, message_content, created "
                  "FROM yl_message "
                  "WHERE receiver_id = %1 AND "
                  "created BETWEEN %2 AND %3 "
                  "ORDER BY yl_message.created;").arg(friendId).arg(oneHourAgo).arg(currentTime);
    qDebug() << sql;
    QSqlQuery query;
    if (query.exec(sql))
    {
        while (query.next()) {
            QPair<uint32_t, QString> pair;
            pair.first = query.value("sender_id").toUInt();
            pair.second = query.value("message_content").toString();
            vec.push_back(pair);
        }
    }

    return vec;
}


QVector<QPair<uint32_t, QString>> YLDataBase::getMoreMessage(uint32_t friendId, uint32_t page, uint32_t currentIndex)
{
    QVector<QPair<uint32_t, QString>> vec;

    QString sql = QString("SELECT sender_id, message_content, created "
                  "FROM yl_message WHERE sender_id = %1 "
                  "UNION  "
                  "SELECT sender_id, message_content, created "
                  "FROM yl_message "
                  "WHERE receiver_id = %1 "
                  "ORDER BY yl_message.created DESC LIMIT %2, 20;").arg(friendId).arg(currentIndex);

    QSqlQuery query;
    if (query.exec(sql))
    {
        while (query.next()) {
            QPair<uint32_t, QString> pair;
            pair.first = query.value("sender_id").toUInt();
            pair.second = query.value("message_content").toString();
            vec.push_back(pair);
        }
    }

    return vec;
}


void YLDataBase::addOneFriend(const YLFriend &fri)
{
    QString sql = "INSERT INTO yl_friend(friend_id, group_id, remark, nick, header, sign_info) VALUES(?, ?, ?, ?, ?, ?);";

    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(fri.friendId());
    query.addBindValue(fri.friendGroupId());
    query.addBindValue(fri.friendRemark());
    query.addBindValue(fri.friendNickName());
    query.addBindValue(fri.friendImagePath());
    query.addBindValue(fri.friendSigature());

    bool ret = query.exec();

    if (ret)
        qDebug() << "插入成功" ;
    else
        qDebug() << "插入失败" << query.lastError().text();
}


void YLDataBase::remOneFriend(uint32_t friId)
{
    QString sql = "DELETE FROM yl_friend WHERE id = " + QString::number(friId);

    QSqlQuery query;
    bool ret = query.exec(sql);
    if (ret)
        qDebug() << "删除成功" ;
    else
        qDebug() << "删除失败" << query.lastError().text();


}

uint32_t YLDataBase::getFriendIdx(uint32_t friendId)
{
    QString sql = QString("SELECT id FROM yl_friend WHERE friend_id = %1;").arg(friendId);

    QSqlQuery query;
    if (query.exec(sql))
    {
        if (query.next())
        {
            return query.value("id").toInt();
        }
    }
    else
    {
        qDebug() << "查询失败:" << query.lastError().text();
        return 0;
    }
}

void YLDataBase::setFriends(const  QMap<int, QVector<YLFriend>>& friendList)
{
    for (const QVector<YLFriend> &fris : friendList)
    {
        for (int i = 0; i < fris.size(); ++i)
        {
            const YLFriend &fri = fris[i];

            uint32_t id = getFriendIdx(fri.friendId());
            if (0 != id)
            {
                remOneFriend(id);
            }

            addOneFriend(fri);
        }
    }
}

uint32_t YLDataBase::getFriendGroupIdx(uint32_t friendGroupId)
{
    QString sql = QString("SELECT id FROM yl_friend_group WHERE group_id = %1;").arg(friendGroupId);

    QSqlQuery query;
    if (query.exec(sql))
    {
        if (query.next())
        {
            return query.value("id").toInt();
        }
    }
    else
    {
        qDebug() << "查询失败:" << query.lastError().text();
        return 0;
    }
}

void YLDataBase::addOneFriendGroup(uint32_t groupId, const QString &groupName)
{
    QString sql = "INSERT INTO yl_friend_group(group_id, group_name) VALUES(?, ?);";

    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(groupId);
    query.addBindValue(groupName);

    bool ret = query.exec();

    if (ret)
        qDebug() << "添加好友分组成功";
    else
        qDebug() << "添加好友分组失败";
}

void YLDataBase::addSomeFriendGroup(const QMap<int, QString> &groups)
{
    for (QString groupName : groups)
    {
        uint32_t groupId = groups.key(groupName);
        uint32_t groupIdx = getFriendGroupIdx(groupId);
        if (groupIdx != 0)
            remOneFriendGroup(groupId);

        addOneFriendGroup(groupId, groupName);
    }
}

void YLDataBase::remOneFriendGroup(uint32_t groupId)
{
    QString sql = QString("DELETE FROM yl_friend_group WHERE group_id = %1").arg(groupId);

    QSqlQuery query;
    bool ret = query.exec(sql);
    if (ret)
        qDebug() << "删除好友分组成功";
    else
        qDebug() << "删除好友分组失败";
}

void YLDataBase::clearFriendGroup()
{
    QString sql = "DELETE FROM yl_friend_group";

    QSqlQuery query;
    bool ret = query.exec(sql);
    if (ret)
        qDebug() << "清空好友分组成功";
    else
        qDebug() << "清空好友分组失败";
}



void YLDataBase::createFriendTable()
{
    QString sql = "CREATE TABLE IF NOT EXISTS yl_friend (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "friend_id INTEGER (11, 11) NOT NULL, group_id INTEGER (11, 11) NOT NULL, "
                  "remark VARCHAR (255, 255), nick VARCHAR (255, 255), header VARCHAR (1024,"
                  " 1024), sign_info VARCHAR (2048, 2048));";


    QSqlQuery query;
    bool ret = query.exec(sql);
    if (ret)
        qDebug() << "创建好友表成功";
    else
        qDebug() << "创建好友表失败" << query.lastError().text();
}


void YLDataBase::createMessageTable()
{
    QString sql = "CREATE TABLE IF NOT EXISTS yl_message (id INTEGER PRIMARY KEY AUTOINCREMENT, sender_id INTEGER NOT NULL,"
                  "receiver_id INTEGER NOT NULL, message_type INT, message_id INTEGER NOT NULL, "
                  "message_content VARCHAR (1, 4096), created INTEGER);";
    QSqlQuery query;
    bool ret = query.exec(sql);
    if (ret)
        qDebug() << "创建消息表成功";
    else
        qDebug() << "创建消息表失败"  << query.lastError().text();
}

void YLDataBase::createFriendGroupTable()
{
    QString sql = "CREATE TABLE IF NOT EXISTS yl_friend_group (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "group_id INTEGER NOT NULL, group_name VARCHAR (255, 255));";
    QSqlQuery query;
    bool ret = query.exec(sql);
    if (ret)
        qDebug() << "创建好友分组表成功";
    else
        qDebug() << "创建好友分组表失败" << query.lastError().text();
}

void YLDataBase::createGroupTable()
{
    QString sql = "CREATE TABLE IF NOT EXISTS yl_group (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "group_id INTEGER NOT NULL, group_name VARCHAR (1, 255) NOT NULL,"
                  " group_header VARCHAR (255, 255) NOT NULL "
                  "DEFAULT ('http://www.liutimo.cn/group_default_head.png'), group_creator INTEGER);";
    QSqlQuery query;
    bool ret = query.exec(sql);
    if (ret)
        qDebug() << "创建群组表成功";
    else
        qDebug() << "创建群组表失败" << query.lastError().text();
}

void YLDataBase::createGroupMemberTable()
{
    QString sql = "CREATE TABLE yl_group_member (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "group_id INTEGER NOT NULL, member_id INTEGER, last_chat_time INTEGER, "
                  "group_card VARCHAR (1, 255), type INTEGER, member_nick VARCHAR (1, 255), "
                  "member_header VARCHAR (0, 1024));";

    QSqlQuery query;
    bool ret = query.exec(sql);
    if (ret)
        qDebug() << "创建群组成员表成功";
    else
        qDebug() << "创建群组成员表失败" << query.lastError().text();
}

/*************群组相关*****************/

uint32_t YLDataBase::getGroupIdx(uint32_t groupId)
{
    uint32_t index = 0;

    QString sql = "SELECT id FROM yl_group WHERE group_id = " + QString::number(groupId);

    QSqlQuery query;
    if (query.exec(sql))
    {
        if (query.next())
            index = query.value("id").toInt();
    }
    return index;
}


void YLDataBase::addOneGroup(const YLGroup &group)
{
    QString sql = "INSERT INTO yl_group(group_id, group_name, group_header, group_creator) VALUES(?, ?, ?, ?)";

    QSqlQuery query;
    if (query.prepare(sql))
    {
        query.addBindValue(group.getGroupId());
        query.addBindValue(group.getGroupName());
        query.addBindValue(group.getGroupImage());
        query.addBindValue(group.getGroupCreator());
    }

    query.exec();
}

void YLDataBase::addSomeGroup(const QVector<YLGroup> &groups)
{
    for (const YLGroup &group : groups)
    {
        uint32_t index = getGroupIdx(group.getGroupId());
        if(index != 0)
        {
            remOneGroup(index);
        }

        addOneGroup(group);
    }
}


void YLDataBase::remOneGroup(uint32_t idx)
{
    QString sql = "DELETE FROM yl_group WHERE id = " + QString::number(idx);

    QSqlQuery query;
    query.exec(sql);
}

uint32_t YLDataBase::getMemberIdx(uint32_t groupId, uint32_t member_id)
{
    uint32_t index = 0;

    QString sql = QString("SELECT id FROM yl_group_member WHERE group_id = %1 AND member_id = %2").arg(groupId).arg(member_id);

    QSqlQuery query;
    if (query.exec(sql))
    {
        if (query.next())
        {
            index = query.value("id").toInt();
        }
    }

    return index;
}


void YLDataBase::addOneMember(uint32_t groupId, const base::MemberInfo &member, uint32_t type)
{
    QString sql = "INSERT INTO yl_group_member(group_id, member_id, last_chat_time, group_card, type, member_nick, member_header) VALUES(?, ?, ?, ?, ?, ?, ?)";

    QSqlQuery query;
    if (query.prepare(sql))
    {
        query.addBindValue(groupId);
        query.addBindValue(member.user_id());
        query.addBindValue(member.last_chat_time());
        query.addBindValue(member.group_card().c_str());
        query.addBindValue(type);
        query.addBindValue(member.user_info().user_nick().c_str());
        query.addBindValue(member.user_info().user_header_url().c_str());
    }

    query.exec();
}


void YLDataBase::remOneMember(uint32_t idx)
{
    QString sql = "DELETE FROM yl_group_member WHERE id = " + QString::number(idx);

    QSqlQuery query;
    query.exec(sql);
}
