#include "globaldata.h"
#include "yllocalsettings.h"
#include <QDir>
#include <QUrl>
youliao::pdu::base::UserInfo GlobalData::m_user = youliao::pdu::base::UserInfo();
QMap<int, QVector<YLFriend>> GlobalData::m_friends = QMap<int, QVector<YLFriend>> ();
QString GlobalData::m_header_image_path = QString();
QMap<int, QString> GlobalData::m_group = QMap<int, QString>();
QMap<uint32_t, YLSingleChatWidget*> GlobalData::m_single_chat_widgets = QMap<uint32_t, YLSingleChatWidget*>();

//消息
QMap<uint32_t, QVector<YLMessage>> GlobalData::m_messages = QMap<uint32_t, QVector<YLMessage>>();
QMap<uint32_t, QVector<YLMessage>> GlobalData::m_group_messages = QMap<uint32_t, QVector<YLMessage>>();
QMap<uint32_t, uint32_t> GlobalData::m_message_id = QMap<uint32_t, uint32_t>();

QVector<YLAddRequest> GlobalData::m_add_request = QVector<YLAddRequest>();
QVector<YLAddRequest> GlobalData::m_add_request_history = QVector<YLAddRequest>();
QVector<YLAddRequest> GlobalData::m_group_request = QVector<YLAddRequest>();
QMap<uint32_t, YLGroup> GlobalData::m_groups = QMap<uint32_t, YLGroup>();
QMap<uint32_t, base::UserInfo>  GlobalData::m_all_user = QMap<uint32_t, base::UserInfo>();
QMap<uint32_t, QMap<uint32_t, base::MemberInfo>> GlobalData::m_group_member = QMap<uint32_t, QMap<uint32_t, base::MemberInfo>>();
QMap<uint32_t, YLGroupChatWidget*>  GlobalData::m_group_chat_widgets = QMap<uint32_t, YLGroupChatWidget*>();
QMap<QString, QString> GlobalData::m_audio_map = QMap<QString, QString>();


//group
QMap<uint32_t, uint32_t> GlobalData::m_group_message_id = QMap<uint32_t, uint32_t>();

//文件保存路径
QString GlobalData::imagePath = QString();
QString GlobalData::audioPath = QString();
QString GlobalData::filePath = QString();


//session
QList<YLSession> GlobalData::m_sessions = QList<YLSession>();
QList<YLSession> GlobalData::m_top_data = QList<YLSession>();

GlobalData::GlobalData(QObject *parent) : QObject(parent)
{

}

void GlobalData::setCurrLoginUser(youliao::pdu::base::UserInfo user)
{
    m_user = user;

    QUrl url(QString(user.user_header_url().c_str()));
    m_header_image_path = "file://" + imagePath + "/" + url.fileName();

    //修改配置文件,设置头像
    YLLocalSettings::instance()->setValue(QString::number(user.user_account()), m_header_image_path);
}

void GlobalData::setCurrLoginUserHeaderIcon(const std::string urlStr)
{
    m_user.set_user_header_url(urlStr);

    QUrl url(QString(urlStr.c_str()));
    m_header_image_path = "file://" + imagePath + "/" + url.fileName();
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

void GlobalData::setTopSessions(const QList<YLSession> &sessions)
{
    m_top_data = sessions;
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

YLSession GlobalData::getSessionByGroupId(uint32_t groupId)
{
    for (auto &session : m_sessions)
    {
        if (session.getSessionType() == base::SESSION_TYPE_GROUP && session.getOtherId() == groupId)
        {
            return session;
        }
    }

    return YLSession();
}


QList<YLSession>& GlobalData::getSessions()
{
    return m_sessions;
}

QList<YLSession>& GlobalData::getTopSessions()
{
    return m_top_data;
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
void GlobalData::addSingleChatWidget(uint32_t friendId, YLSingleChatWidget *chatWidget)
{
    m_single_chat_widgets[friendId] = chatWidget;
}


void GlobalData::removeSingleChatWidget(uint32_t friendId)
{
    m_single_chat_widgets.remove(friendId);
}

YLSingleChatWidget* GlobalData::getSingleChatWidget(uint32_t friendId)
{
    auto iter = m_single_chat_widgets.find(friendId);
    if (iter == m_single_chat_widgets.cend())
        return nullptr;
    else
        return *iter;
}

void GlobalData::addGroupChatWidget(uint32_t groupId, YLGroupChatWidget *groupChatWidget)
{
    m_group_chat_widgets[groupId] = groupChatWidget;
}

void GlobalData::removeGroupChatWidget(uint32_t groupId)
{
    m_group_chat_widgets.remove(groupId);
}

YLGroupChatWidget* GlobalData::getGroupChatWidget(uint32_t groupId)
{
    auto iter = m_group_chat_widgets.find(groupId);
    if (iter == m_group_chat_widgets.cend())
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


void GlobalData::setGroupLatestMsgId(uint32_t groupId, uint32_t latestMsgId)
{
    m_group_message_id[groupId] = latestMsgId;
}

uint32_t GlobalData::getGroupLatestMsgId(uint32_t groupId)
{
    auto iter = m_group_message_id.find(groupId);
    if (iter == m_group_message_id.end())
        return 0;
    else
        return iter.value();
}

/****************群组消息****************/
void GlobalData::addGroupMessage(uint32_t groupId, const YLMessage& message)
{
    m_group_messages[groupId].push_back(message);
}

QVector<YLMessage> GlobalData::getGroupMessagesByGroupId(uint32_t groupId)
{
    auto iter = m_group_messages.find(groupId);
    if (iter == m_group_messages.cend())
        return QVector<YLMessage>();
    else
        return *iter;
}

const QMap<uint32_t, QVector<YLMessage>>& GlobalData::getGroupMessages()
{
    return m_group_messages;
}

void GlobalData::removeGroupMessageByGroupId(uint32_t groupId)
{
    auto iter = m_group_messages.find(groupId);
    if (iter != m_group_messages.end())
        m_group_messages.erase(iter);
}


void GlobalData::setRequest(const YLAddRequest &req)
{
    m_add_request.push_back(req);
}

const QVector<YLAddRequest>& GlobalData::getAddRequests()
{
    return m_add_request;
}

void GlobalData::addOneGroupRequest(const YLAddRequest &request)
{
    m_group_request.push_back(request);
}

QVector<YLAddRequest> &GlobalData::getGroupAddRequests()
{
    return m_group_request;
}

//group
void GlobalData::setGroups(const QMap<uint32_t, YLGroup>&groups)
{
    m_groups = groups;
}

void GlobalData::addToGroups(const YLGroup &group)
{
    m_groups[group.getGroupId()] = group;
}

QMap<uint32_t, YLGroup> GlobalData::getGroups()
{
    return m_groups;
}

void GlobalData::addUser(const base::UserInfo &user)
{
    m_all_user[user.user_id()] = user;
}

void GlobalData::addUsers(const QList<base::UserInfo> &users)
{
    for (const auto &user : users)
    {
        addUser(user);
    }
}

void GlobalData::addUSers(const QVector<base::UserInfo> &users)
{
    for (const auto &user : users)
    {
        addUser(user);
    }
}


YLGroup& GlobalData::getGroupByGroupId(uint32_t groupId)
{
    YLGroup g;
    auto iter = m_groups.find(groupId);
    if (iter == m_groups.end())
        return g;
    else
        return *iter;
}

void GlobalData::remGroupByGroupId(uint32_t groupId)
{
    auto iter = m_groups.find(groupId);
    if (iter != m_groups.end())
        m_groups.erase(iter);
}

base::UserInfo GlobalData::getCreatorByGroupId(uint32_t groupId)
{
    const YLGroup &group = m_groups[groupId];
    uint32_t creatorId = group.getGroupCreator();

    return m_all_user[creatorId];
}

QVector<base::UserInfo> GlobalData::getManagersByGroupId(uint32_t groupId)
{
    QVector<base::UserInfo> managers;
    const YLGroup &group = m_groups[groupId];
    const auto &ms = group.getManagers();

    for (uint32_t id : ms)
    {
        managers.push_back(m_all_user[id]);
    }
    return managers;
}

QVector<base::UserInfo> GlobalData::getMembersByGroupId(uint32_t groupId)
{
    QVector<base::UserInfo> members;
    const YLGroup &group = m_groups[groupId];
    const auto &ms = group.getMembers();

    for (uint32_t id : ms)
    {
        members.push_back(m_all_user[id]);
    }
    return members;
}

void GlobalData::setGroupMember(uint32_t groupId, const QVector<base::MemberInfo> &members)
{
    QMap<uint32_t, base::MemberInfo> map;
    for (const base::MemberInfo &mem : members)
    {
        map[mem.user_id()] = mem;
    }

    m_group_member[groupId] = map;

}

base::MemberInfo& GlobalData::getMemberInfo(uint32_t groupId, uint32_t memberId, bool &ret)
{
    auto iter = m_group_member.find(groupId);
    if (iter != m_group_member.end())
    {
        ret = true;
        return (*iter)[memberId];
    }
    else
    {
        ret = false;
        base::MemberInfo member = base::MemberInfo();
        return member;
    }
}

//audio
void GlobalData::addAudio(const QString &key, const QString &value)
{
    m_audio_map[key] = value;
}

const QString& GlobalData::getAudio(const QString &key)
{
    static QString sTmp = "";
    auto iter = m_audio_map.find(key);
    if (iter != m_audio_map.end())
        return *iter;
    return sTmp;
}

//文件
