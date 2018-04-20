#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QList>
#include "protobuf/youliao.base.pb.h"
#include "YLEntityObject/ylfriend.h"
#include "YLEntityObject/ylsession.h"

class GlobalData : public QObject
{
    Q_OBJECT
public:
    explicit GlobalData(QObject *parent = nullptr);
    static void     setCurrLoginUser(youliao::pdu::base::UserInfo user);
    static uint32_t getCurrLoginUserId () { return m_user.user_id(); }
    static QString  getCurrLoginUserIconPath() { return m_header_image_path;}
    static const YLFriend& getFriendById(const uint32_t friendId);
    static void setFriends(const QMap<int, QVector<YLFriend>> &friends);

    static void setSessions(const QList<YLSession> &sessions);
    static YLSession getSessionByFriendId(uint32_t friendId);

public slots:

private:
    static youliao::pdu::base::UserInfo m_user;
    static QString m_header_image_path;
    static QMap<int, QVector<YLFriend>> m_friends;
    static QList<YLSession> m_sessions;
};

#endif // GLOBALDATA_H
