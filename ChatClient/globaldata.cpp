#include "globaldata.h"
#include <QDir>
#include <QUrl>
youliao::pdu::base::UserInfo GlobalData::m_user = youliao::pdu::base::UserInfo();
QMap<int, QVector<YLFriend>> GlobalData::m_friends = QMap<int, QVector<YLFriend>> ();
QString GlobalData::m_header_image_path = QString();
QList<YLSession> GlobalData::m_sessions = QList<YLSession>();
QMap<int, QString> GlobalData::m_group = QMap<int, QString>();
QMap<uint32_t, YLChatWidget*> GlobalData::m_chat_widgets = QMap<uint32_t, YLChatWidget*>();
QMap<uint32_t, QVector<YLMessage>> GlobalData::m_messages = QMap<uint32_t, QVector<YLMessage>>();
QMap<uint32_t, uint32_t> GlobalData::m_message_id = QMap<uint32_t, uint32_t>();
QVector<YLAddRequest> GlobalData::m_add_request = QVector<YLAddRequest>();
QVector<YLAddRequest> GlobalData::m_add_request_history = QVector<YLAddRequest>();
QList<YLGroup> GlobalData::m_groups = QList<YLGroup>();

GlobalData::GlobalData(QObject *parent) : QObject(parent)
{

}

void GlobalData::setCurrLoginUser(youliao::pdu::base::UserInfo user)
{
    m_user = user;

    QUrl url(QString(user.user_header_url().c_str()));
    m_header_image_path = "file://" + QDir::currentPath() + "/" + url.fileName();
}


const YLFriend GlobalData::getFriendById(const uint32_t friendId)
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

uint32_t GlobalData::getRelateIdByFriendId(uint32_t friId)
{
    auto fri = getFriendById(friId);
    return fri.relateId();
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

void GlobalData::setGroup(const QMap<int, QString> &group)
{
    m_group = group;
}

const QMap<int, QString>& GlobalData::getGroup()
{
    return m_group;
}


const uint32_t GlobalData::getGroupIdByName(const QString &name)
{
    return m_group.key(name);
}

/////////////chat widget
void GlobalData::addChatWidget(uint32_t friendId, YLChatWidget *chatWidget)
{
    m_chat_widgets[friendId] = chatWidget;
}


void GlobalData::removeChatWidget(uint32_t friendId)
{
    m_chat_widgets.remove(friendId);
}

YLChatWidget* GlobalData::getChatWidget(uint32_t friendId)
{
    auto iter = m_chat_widgets.find(friendId);
    if (iter == m_chat_widgets.cend())
        return nullptr;
    else
        return *iter;
}

/////////////////message
void GlobalData::addMessage(uint32_t friendId, const YLMessage& message)
{
    m_messages[friendId].push_back(message);
}

QVector<YLMessage> GlobalData::getMessagesByFriendId(uint32_t friendId)
{
    auto iter = m_messages.find(friendId);
    if (iter == m_messages.cend())
        return QVector<YLMessage>();
    else
        return *iter;
}

const QMap<uint32_t, QVector<YLMessage>>& GlobalData::getMessages()
{
    return m_messages;
}


void GlobalData::removeMessageByFriendId(uint32_t friId)
{
    auto iter = m_messages.find(friId);
    if (iter != m_messages.end())
        m_messages.erase(iter);
}

void GlobalData::setLatestMsgId(uint32_t friendId, uint32_t latestMsgId)
{
    m_message_id[friendId] = latestMsgId;
}

uint32_t GlobalData::getLatestMsgId(uint32_t friendId)
{
    auto iter = m_message_id.find(friendId);
    if (iter == m_message_id.end())
        return 0;
    else
        return iter.value();
}

void GlobalData::setRequest(const YLAddRequest &req)
{
    m_add_request.push_back(req);
}

const QVector<YLAddRequest>& GlobalData::getAddRequests()
{
    return m_add_request;
}


//group
void GlobalData::setGroups(const QList<YLGroup>&groups)
{
    m_groups = groups;
}

void GlobalData::addToGroups(const YLGroup &group)
{
    m_groups.push_back(group);
}

QList<YLGroup> GlobalData::getGroups()
{
    return m_groups;
}
