#ifndef YLDATABASE_H
#define YLDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include "protobuf/youliao.message.pb.h"

using namespace youliao::pdu::message;

class YLDataBase : public QObject
{
    Q_OBJECT
public:
    static YLDataBase* instance();
    void saveMessage(const MessageData &, bool isSender = false);
private:
    YLDataBase(QObject *parent = nullptr);

    static YLDataBase* m_instance;
    QSqlDatabase m_database;
};

#endif // YLDATABASE_H
