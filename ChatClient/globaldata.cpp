#include "globaldata.h"
#include <QDir>
#include <QUrl>
youliao::pdu::base::UserInfo GlobalData::m_user = youliao::pdu::base::UserInfo();
QMap<int, QVector<YLFriend>> GlobalData::m_friends = QMap<int, QVector<YLFriend>> ();
QString GlobalData::m_header_image_path = QString();
QList<YLSession> GlobalData::m_sessions = QList<YLSession>();

GlobalData::GlobalData(QObject *parent) : QObject(parent)
{

}

void GlobalData::setCurrLoginUser(youliao::pdu::base::UserInfo user)
{
    m_user = user;

    QUrl url(QString(user.user_header_url().c_str()));

    m_header_image_path = "file://" + QDir::currentPath() + "/" + url.fileName();
}


const YLFriend& GlobalData::getFriendById(const uint32_t friendId)
{
    for (QVector<YLFriend>& friends : m_friends)
    {
        for (YLFriend& fri : friends)
        {
            if (fri.friendId() == friendId)
                return fri;
        }
    }

    return YLFriend();
}

void GlobalData::setFriends(const QMap<int, QVector<YLFriend>> &friends)
{
    m_friends = friends;
}

void GlobalData::setSessions(const QList<YLSession> &sessions)
{
    m_sessions = sessions;
}

YLSession GlobalData::getSessionByFriendId(uint32_t friendId)
{
    for (auto &session : m_sessions)
    {
        if (session.getSessionType() == base::SESSION_TYPE_SINGLE && session.getOtherId() == friendId)
        {
            return session;
        }
    }

    return YLSession();
}
