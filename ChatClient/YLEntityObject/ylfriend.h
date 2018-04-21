#ifndef YLFRIEND_H
#define YLFRIEND_H

#include <QObject>
#include <QUrl>
class YLFriend
{
public:
    YLFriend();

    YLFriend &operator =(const YLFriend &);

    bool operator ==(const YLFriend &) const;

    bool operator <(const YLFriend &) const;

    void setFriendId(uint32_t id) { friend_id_ = id; }

    void setFriendAccount(const QString &account);

    void setFriendNickName(const QString &nickname);

    void setFriendSigature(const QString &signature);

    void setFriendRemark(const QString &remark);

    void setFriendImagePath(const QString &path);

    void setFriendGroup(const QString &group);

    void setFriendOnline(bool online) { friend_is_online_ = online; }

    void setFriendSex(uint32_t sex);

    QString friendAccount() const;

    QString friendNickName() const;

    QString friendSigature() const;

    QString friendRemark() const;

    QString friendImagePath() const;

    QString friendGroup() const;

    QString friendImageName() const;

    QString friendSex() const { return friend_sex_; }

    uint32_t friendId() const { return friend_id_; }

    bool friendIsOnline() const { return friend_is_online_; }

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
    //好友头像路径
    QString friend_image_path_;
    //好友分组，暂定为QString
    QString friend_group;

    //sex
    QString friend_sex_;

    bool friend_is_online_;
};

#endif // YLFRIEND_H
