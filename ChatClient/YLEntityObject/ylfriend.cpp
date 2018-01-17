#include "ylfriend.h"
#include <QTime>
YLFriend::YLFriend(QObject *parent) : QObject(parent)
{

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

QString YLFriend::getFriendAccount()
{
    return friend_account_;
}

QString YLFriend::getFriendNickName()
{
    return friend_nickname_;
}

QString YLFriend::getFriendSigature()
{
    return friend_signature_;
}

QString YLFriend::getFriendRemark()
{
    return friend_remark_;
}

QString YLFriend::getFriendLastMessage()
{
    return friend_last_message_;
}

QString YLFriend::getFriendImagePath()
{
    return friend_image_path_;
}

QString YLFriend::getFriendGroup()
{
    return friend_group;
}

QString YLFriend::getFriendLastChatTime()
{
    return friend_last_chat_time_;
}
