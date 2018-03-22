#ifndef YLBUSINESS_H
#define YLBUSINESS_H

#include <QObject>
#include <protobuf/youliao.base.pb.h>

using namespace youliao::pdu::base;

class YLBusiness : public QObject
{
    Q_OBJECT
public:
    explicit YLBusiness(QObject *parent = nullptr);
    static void login(const QString &account, const QString &password, UserStatusType type = USER_STATUS_ONLINE);
};

#endif // YLBUSINESS_H
