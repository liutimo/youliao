#ifndef YLFRIEND_H
#define YLFRIEND_H

#include <QObject>




class YLFriend
{
public:
    YLFriend();

    YLFriend &operator =(const YLFriend &);

    bool operator ==(const YLFriend &) const;

    void setFriendId(uint32_t id) { friend_id_ = id; }

    void setFriendAccount(const QString &account);

    void setFriendNickName(const QString &nickname);

    void setFriendSigature(const QString &signature);

    void setFriendRemark(const QString &remark);

    void setFriendLastMessage(const QString &lastmsg);

    void setFriendImagePath(const QString &path);

    void setFriendGroup(const QString &group);

    void setFriendLastChatTime(const QString &lasttime);

    QString getFriendAccount() const;

    QString getFriendNickName() const;

    QString getFriendSigature() const;

    QString getFriendRemark() const;

    QString getFriendLastMessage() const;

    QString getFriendImagePath() const;

    QString getFriendGroup() const;

    QString getFriendLastChatTime() const;

    uint32_t getFriendId() const { return friend_id_; }

private:
    uint32_t friend_id_;
    //好友账号
    QString friend_account_;
    //好友昵称
    QString friend_nickname_;
    //好友个性签名
    QString friend_signature_;
    //好友备注
    QString friend_remark_;
    //与该好友的最后一条聊天消息
    QString friend_last_message_;
    //好友头像路径
    QString friend_image_path_;
    //好友分组，暂定为QString
    QString friend_group;
    //最后一条消息接收的时间
    QString friend_last_chat_time_;
};

#endif // YLFRIEND_H
