#include "ylfriend.h"
#include <QTime>
YLFriend::YLFriend()
{

}

YLFriend & YLFriend::operator =(const YLFriend &f)
{
    friend_id_ = f.friend_id_;

    friend_account_ = f.friend_account_;

    friend_nickname_ = f.friend_nickname_;

    friend_signature_ = f.friend_signature_;

    friend_remark_ = f.friend_remark_;

    friend_last_message_ = f.friend_last_message_;

    friend_image_path_ = f.friend_image_path_;

    friend_group = f.friend_group;

    friend_last_chat_time_ = f.friend_last_chat_time_;
}

bool YLFriend::operator ==(const YLFriend &f1) const
{
    if (f1.getFriendAccount() == this->getFriendAccount())
        return true;
    else
        return false;
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

void YLFriend::setFriendLastMessage(const QString &lastmsg)
{
    friend_last_message_  = lastmsg;
}

void YLFriend::setFriendImagePath(const QString &path)
{
    friend_image_path_ = path;
}

void YLFriend::setFriendGroup(const QString &group)
{
    friend_group = group;
}
void YLFriend::setFriendLastChatTime(const QString &lasttime)
{
    friend_last_chat_time_ = lasttime;
}

QString YLFriend::getFriendAccount() const
{
    return friend_account_;
}

QString YLFriend::getFriendNickName() const
{
    return friend_nickname_;
}

QString YLFriend::getFriendSigature() const
{
    return friend_signature_;
}

QString YLFriend::getFriendRemark() const
{
    return friend_remark_;
}

QString YLFriend::getFriendLastMessage() const
{
    return friend_last_message_;
}

QString YLFriend::getFriendImagePath() const
{
    return friend_image_path_;
}

QString YLFriend::getFriendGroup() const
{
    return friend_group;
}

QString YLFriend::getFriendLastChatTime() const
{
    return friend_last_chat_time_;
}
