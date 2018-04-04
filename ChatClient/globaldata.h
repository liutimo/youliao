#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QObject>
#include "protobuf/youliao.base.pb.h"

class GlobalData : public QObject
{
    Q_OBJECT
public:
    explicit GlobalData(QObject *parent = nullptr);
    static void     setCurrLoginUser(youliao::pdu::base::UserInfo user);
    static uint32_t getCurrLoginUserId () { return m_user.user_id(); }
    static QString  getCurrLoginUserIconPath() { return m_header_image_path;}

public slots:

private:
    static youliao::pdu::base::UserInfo m_user;
    static QString m_header_image_path;
};

#endif // GLOBALDATA_H
