#include "ylfriend.h"
#include <QTime>
YLFriend::YLFriend()
{
    friend_id_ = 0;
    relate_id_ = 0;
}

YLFriend& YLFriend::operator =(const YLFriend &f)
{
    relate_id_ = f.relate_id_;

    friend_id_ = f.friend_id_;

    friend_account_ = f.friend_account_;

    friend_nickname_ = f.friend_nickname_;

    friend_signature_ = f.friend_signature_;

    friend_remark_ = f.friend_remark_;

    friend_image_path_ = f.friend_image_path_;

    friend_group = f.friend_group;

    friend_sex_ = f.friend_sex_;

    friend_is_online_ = f.friend_is_online_;
    return *this;
}

bool YLFriend::operator ==(const YLFriend &f1) const
{
    if (f1.friendAccount() == this->friendAccount())
        return true;
    else
        return false;
    return true;
}


bool YLFriend::operator <(const YLFriend &f1) const
{
    if (f1.friendIsOnline() && !friendIsOnline())
        return false;
    else
        return true;
}

void YLFriend::setFriendAccount(const QString &account)
{
    friend_account_ = account;
}

void YLFriend::setFriendNickName(const QString &nickname)
{
    friend_nickname_ = nickname;
}

void YLFriend::setFriendSigature(const QString &signature)
{
    friend_signature_ = signature;
}

void YLFriend::setFriendRemark(const QString &remark)
{
    friend_remark_ = remark;
}

void YLFriend::setFriendImagePath(const QString &path)
{
    friend_image_path_ = path;
}

void YLFriend::setFriendGroup(const QString &group)
{
    friend_group = group;
}

void YLFriend::setFriendSex(uint32_t sex)
{
     if (sex == 1)
         friend_sex_ = "男";
     else if (sex == 2)
         friend_sex_ = "女";
     else
         friend_sex_ = "未知";
}

QString YLFriend::friendAccount() const
{
    return friend_account_;
}

QString YLFriend::friendNickName() const
{
    return friend_nickname_;
}

QString YLFriend::friendSigature() const
{
    return friend_signature_;
}

QString YLFriend::friendRemark() const
{
    return friend_remark_;
}


QString YLFriend::friendImagePath() const
{
    return friend_image_path_;
}

QString YLFriend::friendGroup() const
{
    return friend_group;
}


QString YLFriend::friendImageName() const
{
    QUrl url(friend_image_path_);
    if (url.isValid())
        return url.fileName();
    else
        return QString();
}
