#ifndef YLDATABASE_H
#define YLDATABASE_H

#include <QObject>
#include <QSqlDatabase>

#include "YLEntityObject/ylgroup.h"
#include "YLEntityObject/ylfriend.h"
#include "YLEntityObject/ylmessage.h"
#include "YLEntityObject/ylgroupmember.h"

#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.message.pb.h"

using namespace youliao::pdu::message;
using namespace youliao::pdu;

class YLDataBase : public QObject
{
    Q_OBJECT
public:
    YLDataBase(QObject *parent = nullptr);
    ~YLDataBase();

    /*************消息相关*****************/
    //好友之间的消息(const YLMessage &msg)
    void saveMessage(const MessageData &msg);
    void saveMessage(const YLMessage &msg);
    void getMessage();

    /**
     * @brief getRecentMessage
     * @param friendId
     * @return
     * 获取最近消息，这里是1小时之内的消息, 在打开聊天窗口时使用
     */
    QVector<QPair<uint32_t, QString>> getRecentMessage(uint32_t friendId);

    /**
     * @brief getMoreMessage
     * @param friendId
     * @return
     * 加载更过消息
     */

    QVector<QPair<uint32_t, QString>> getMoreMessage(uint32_t friendId, uint32_t page, uint32_t currentIndex);
    /*************好友列表相关*****************/

    //好友
    uint32_t getFriendIdx(uint32_t friendId);
    void addOneFriend(const YLFriend &fri);
    void remOneFriend(uint32_t friId);
    void setFriends(const QMap<int, QVector<YLFriend>>& friendList);

    //好友分组
    uint32_t getFriendGroupIdx(uint32_t friendGroupId);
    void addOneFriendGroup(uint32_t groupId, const QString &groupName);
    void addSomeFriendGroup(const QMap<int, QString> &groups);
    void remOneFriendGroup(uint32_t groupId);
    void clearFriendGroup();

    /*************群组相关*****************/
    /**
     * @brief getGroupIdx
     * @param groupId
     * @return group 的 index
     * 查询group是否存在， 存在返回index， 否则返回0
     */
    uint32_t getGroupIdx(uint32_t groupId);

    /**
     * @brief addOneGroup
     * @param group
     * 添加一个群组
     */
    void addOneGroup(const YLGroup &group);

    /**
     * @brief addSomeGroup
     * @param groups
     * 添加多个群组
     */
    void addSomeGroup(const QVector<YLGroup> &groups);

    /**
     * @brief remOneGroup
     * @param idx
     * 根据参数idx删除群组
     */
    void remOneGroup(uint32_t idx);

    /**
     * @brief getMemberIdx
     * @param groupId
     * @param member_id
     * @return
     * 获取指定群组成员的index
     */
    uint32_t getMemberIdx(uint32_t groupId, uint32_t member_id);

    /**
     * @brief addOneMember
     * @param member
     * 添加一个成员
     */
    void addOneMember(uint32_t groupId, const base::MemberInfo &member, uint32_t type);

    /**
     * @brief remOneMember
     * @param idx
     * 移除一个成员
     */
    void remOneMember(uint32_t idx);

    /**
     * @brief getMemberByGroupId
     * @param groupId
     * @return 群成员
     * 获取群组成员
     */
    QVector<YLGroupMember> getMemberByGroupId(uint32_t groupId);

    /**
     * @brief addOneGroupMessage
     * @param groupId　　群组ＩＤ
     * @param senderId  发送者ＩＤ
     * @param msg_id    消息ＩＤ
     * @param content   文本
     * @param created   创建时间
     * @param type      消息类型
     */
    void addOneGroupMessage(uint32_t groupId, uint32_t senderId,
                            uint32_t msg_id, const QString &content,
                            uint32_t created, uint32_t type = 0);
    /**
     * @brief getGroupMsgIdByGroupId
     * @param groupId
     * @return
     */
    uint32_t getGroupMsgIdByGroupId(uint32_t groupId);

    /**
     * @brief getGroupMsgByGroupId
     * @param groupid
     * @return
     * 获取最近一小时的消息
     */
    QVector<QPair<uint32_t, YLMessage>> getRecentGroupMsgByGroupId(uint32_t groupid);

    QVector<QPair<uint32_t, YLMessage>> getGroupMsgByGroupId(uint32_t groupid, uint32_t page, uint32_t currentIndex);
private:
    void createFriendTable();
    void createMessageTable();
    void createFriendGroupTable();
    void createGroupTable();
    void createGroupMemberTable();
    void createGroupMessageTable();

private:


//    static YLDataBase* m_instance;
    static bool m_first;
    QSqlDatabase m_database;

    static int i;
};

#endif // YLDATABASE_H
