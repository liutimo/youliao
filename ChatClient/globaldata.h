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
#include "YLChatWidget/ylsinglechatwidget.h"
#include "YLEntityObject/yladdrequest.h"
#include "YLEntityObject/ylfile.h"
#include "YLEntityObject/ylgroup.h"
#include "YLChatWidget/ylgroupchatwidget.h"
using namespace youliao::pdu;

class GlobalData : public QObject
{
    Q_OBJECT
public:
    explicit GlobalData(QObject *parent = nullptr);

    //登录用户信息，怎么方便怎么用
    static void     setCurrLoginUser(youliao::pdu::base::UserInfo user);
    static void     setCurrLoginUserHeaderIcon(const std::string url);

    static uint32_t getCurrLoginUserId () { return m_user.user_id(); }
    static QString  getCurrLoginUserIconPath() { return m_header_image_path;}
    static QString  getCurrLoginUserNick() { return m_user.user_nick().c_str(); }
    static QString  getCurrLoginUserHeadUrl() { return m_user.user_header_url().c_str(); }
    static QString getCurrLoginUserAccount() { return QString::number(m_user.user_account()); }
    static QString getCurrLoginUserSignature() { return m_user.user_sign_info().c_str(); }
    static base::UserInfo & getCurrLoginUser() { return m_user; }

    static const YLFriend getFriendById(const uint32_t friendId);
    static void setFriends(const QMap<int, QVector<YLFriend>> &friends);
    static uint32_t getRelateIdByFriendId(uint32_t friId);
    static const QMap<int, QVector<YLFriend>>& getFriends() { return m_friends; }

    //session
    static void setSessions(const QList<YLSession> &sessions);
    static void setTopSessions(const QList<YLSession> &sessions);

    static YLSession getSessionByFriendId(uint32_t friendId);
    static YLSession getSessionByGroupId(uint32_t groupId);
    static QList<YLSession>& getSessions();
    static QList<YLSession>& getTopSessions();

    static void setGroup(const QMap<int, QString> &group);
    static const QMap<int, QString>& getGroup();
    static const uint32_t getGroupIdByName(const QString &name);

    //////////chat widget
    static void addSingleChatWidget(uint32_t friendId, YLSingleChatWidget *singleChatWidget);
    static void removeSingleChatWidget(uint32_t friendId);
    static YLSingleChatWidget* getSingleChatWidget(uint32_t friendId);

    static void addGroupChatWidget(uint32_t groupId, YLGroupChatWidget *groupChatWidget);
    static void removeGroupChatWidget(uint32_t groupId);
    static YLGroupChatWidget* getGroupChatWidget(uint32_t groupId);


    //message
    static void addMessage(uint32_t friendId, const YLMessage& message);
    static QVector<YLMessage> getMessagesByFriendId(uint32_t friendId);
    static const QMap<uint32_t, QVector<YLMessage>>& getMessages();
    static void removeMessageByFriendId(uint32_t friId);
    static void setLatestMsgId(uint32_t friendId, uint32_t latestMsgId);
    static uint32_t getLatestMsgId(uint32_t friendId);
    static void setGroupLatestMsgId(uint32_t groupId, uint32_t latestMsgId);
    static uint32_t getGroupLatestMsgId(uint32_t groupId);

    //groupMessage
    static void addGroupMessage(uint32_t groupId, const YLMessage& message);
    static QVector<YLMessage> getGroupMessagesByGroupId(uint32_t groupId);
    static const QMap<uint32_t, QVector<YLMessage>>& getGroupMessages();
    static void removeGroupMessageByGroupId(uint32_t groupId);

    //add request
    static void setRequest(const YLAddRequest &);
    static const QVector<YLAddRequest> &getAddRequests();
    static void clearAllRequest() { m_add_request.clear(); }
    static void setRequestHistory(const QVector<YLAddRequest>&h) { m_add_request_history = h;}
    static const QVector<YLAddRequest>& getRequestHistory() { return m_add_request_history; }

    //群组验证消息
    static void addOneGroupRequest(const YLAddRequest &);
    static QVector<YLAddRequest> &getGroupAddRequests();

    //group
    static void setGroups(const QMap<uint32_t, YLGroup>&);
    static void remGroups();
    static void addToGroups(const YLGroup &);
    static QMap<uint32_t, YLGroup> getGroups();
    static void addUser(const base::UserInfo&);
    static void addUsers(const QList<base::UserInfo> &);
    static void addUSers(const QVector<base::UserInfo> &);
    static YLGroup& getGroupByGroupId(uint32_t groupId);
    static void remGroupByGroupId(uint32_t groupId);
    static base::UserInfo getCreatorByGroupId(uint32_t groupId);
    static QVector<base::UserInfo> getManagersByGroupId(uint32_t groupId);
    static QVector<base::UserInfo> getMembersByGroupId(uint32_t groupId);
    static void setGroupMember(uint32_t groupId, const QVector<base::MemberInfo> &members);
    static base::MemberInfo& getMemberInfo(uint32_t groupId, uint32_t memberId, bool &ret);

    //audio
    static void addAudio(const QString &, const QString &);
    static const QString& getAudio(const QString &);
    //文件

    //固定路径
    static QString imagePath;
    static QString audioPath;
    static QString filePath;

private:
    static youliao::pdu::base::UserInfo m_user;
    static QString m_header_image_path;
    static QMap<int, QVector<YLFriend>> m_friends;
    static QMap<int, QString> m_group;
    static QMap<uint32_t, YLSingleChatWidget*> m_single_chat_widgets;
    //消息相关
    static QMap<uint32_t, QVector<YLMessage>> m_messages;               //未读好友消息
    static QMap<uint32_t, QVector<YLMessage>> m_group_messages;         //未读群组消息


    static QMap<uint32_t, uint32_t> m_message_id;

    //add request
    static QVector<YLAddRequest> m_add_request;
    static QVector<YLAddRequest> m_add_request_history;
    static QVector<YLAddRequest> m_group_request;

    //group
    static QMap<uint32_t, YLGroup> m_groups;
    static QMap<uint32_t, base::UserInfo> m_all_user; //所有的用户信息
    static QMap<uint32_t, QMap<uint32_t, base::MemberInfo>> m_group_member; //群成员信息
    static QMap<uint32_t, uint32_t> m_group_message_id;
    static QMap<uint32_t, YLGroupChatWidget*> m_group_chat_widgets;
    static QMap<uint32_t, uint32_t> m_latest_msg_ids;

    //登录过程需要从服务器获取很多数据。这里记录是否加载情况。
    //只有全部加载完才会进入主界面
    static QMap<uint32_t, bool> m_load;

    //audio
    static QMap<QString, QString> m_audio_map;
    //文件

    //session
    static QList<YLSession> m_sessions;
    static QList<YLSession> m_top_data;
};

#endif // GLOBALDATA_H
