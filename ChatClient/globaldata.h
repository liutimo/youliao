#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QList>
#include <QUrl>
#include "protobuf/youliao.base.pb.h"
#include "YLEntityObject/ylmessage.h"
#include "YLEntityObject/ylfriend.h"
#include "YLEntityObject/ylsession.h"
#include "YLChatWidget/ylchatwidget.h"
#include "YLEntityObject/yladdrequest.h"

using namespace youliao::pdu;

class GlobalData : public QObject
{
    Q_OBJECT
public:
    explicit GlobalData(QObject *parent = nullptr);
    static void     setCurrLoginUser(youliao::pdu::base::UserInfo user);
    static uint32_t getCurrLoginUserId () { return m_user.user_id(); }
    static QString  getCurrLoginUserIconPath() { return m_header_image_path;}
    static QString  getCurrLoginUserNick() { return m_user.user_nick().c_str(); }
    static QString  getCurrLoginUserHeadUrl() { return m_user.user_header_url().c_str(); }
    static QString getCurrLoginUserAccount() { return QString::number(m_user.user_account()); }

    static const YLFriend getFriendById(const uint32_t friendId);
    static void setFriends(const QMap<int, QVector<YLFriend>> &friends);
    static uint32_t getRelateIdByFriendId(uint32_t friId);
    static const QMap<int, QVector<YLFriend>>& getFriends() { return m_friends; }

    static void setSessions(const QList<YLSession> &sessions);
    static YLSession getSessionByFriendId(uint32_t friendId);

    static void setGroup(const QMap<int, QString> &group);
    static const QMap<int, QString>& getGroup();
    static const uint32_t getGroupIdByName(const QString &name);

    //////////chat widget
    static void addChatWidget(uint32_t friendId, YLChatWidget *chatWidget);
    static void removeChatWidget(uint32_t friendId);
    static YLChatWidget* getChatWidget(uint32_t friendId);

    //message
    static void addMessage(uint32_t friendId, const YLMessage& message);
    static QVector<YLMessage> getMessagesByFriendId(uint32_t friendId);
    static const QMap<uint32_t, QVector<YLMessage>>& getMessages();
    static void removeMessageByFriendId(uint32_t friId);
    static void setLatestMsgId(uint32_t friendId, uint32_t latestMsgId);
    static uint32_t getLatestMsgId(uint32_t friendId);

    //add request
    static void setRequest(const YLAddRequest &);
    static const QVector<YLAddRequest> &getAddRequests();
    static void clearAllRequest() { m_add_request.clear(); }
    static void setRequestHistory(const QVector<YLAddRequest>&h) { m_add_request_history = h;}
    static const QVector<YLAddRequest>& getRequestHistory() { return m_add_request_history; }

private:
    static youliao::pdu::base::UserInfo m_user;
    static QString m_header_image_path;
    static QMap<int, QVector<YLFriend>> m_friends;
    static QList<YLSession> m_sessions;
    static QMap<int, QString> m_group;
    static QMap<uint32_t, YLChatWidget*> m_chat_widgets;
    static QMap<uint32_t, QVector<YLMessage>> m_messages;
    static QMap<uint32_t, uint32_t> m_message_id;
    //add request
    static QVector<YLAddRequest> m_add_request;
    static QVector<YLAddRequest> m_add_request_history;
};

#endif // GLOBALDATA_H
