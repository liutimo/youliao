#include "yldatabase.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include "globaldata.h"
YLDataBase* YLDataBase::m_instance = nullptr;


YLDataBase* YLDataBase::instance()
{
    if (m_instance == nullptr)
        m_instance = new YLDataBase();
    return m_instance;
}

YLDataBase::YLDataBase(QObject *parent) : QObject(parent)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("youliao.db");
    m_database.setUserName("youliao");
    m_database.setPassword("123456");
    m_database.open();
}

void YLDataBase::saveMessage(const MessageData &msg, bool isSender)
{
    QString sql = "INSERT INTO yl_message(relate_id, sender_id, receiver_id, message_id, message_content, message_created)"
                  "VALUES(?, ?, ?, ?, ?, ?)";


    uint32_t friId = msg.from_user_id();

    if (isSender)
    {
        friId = msg.to_user_id();
    }

    QSqlQuery query;
    query.prepare(sql);
    query.addBindValue(GlobalData::getRelateIdByFriendId(friId));
    query.addBindValue(msg.from_user_id());
    query.addBindValue(msg.to_user_id());
    query.addBindValue(msg.msg_id());
    query.addBindValue(msg.message_data().c_str());
    query.addBindValue(msg.create_time());

    bool flag = query.exec();
    if (flag)
        qDebug() << "insert success";
    else
    {
        qDebug() << query.lastError().text();
    }
}
