#include "yluser.h"

YLUser::YLUser(QObject *parent) : QObject(parent)
{

}

YLUser::YLUser(const QString &account, const QString &nickname, QObject *parent) : QObject(parent)
{
    user_account_  = account;
    user_nickname_ = nickname;
}

void YLUser::setUserAccount(const QString &account)
{
    user_account_ = account;
}

void YLUser::setUserNickName(const QString &nickname)
{
    user_nickname_ = nickname;
}

void YLUser::setUserPassword(const QString &password)
{
    user_password_ = password;
}

void YLUser::setUserSignature(const QString &signature)
{
    user_signature_ = signature;
}

void YLUser::setUserImagePath(const QString &imagepath)
{
    user_image_path = imagepath;
}

QString YLUser::getUserAccount() const
{
    return user_account_;
}

QString YLUser::getUserNickName() const
{
    return user_nickname_;
}
QString YLUser::getUserPassword() const
{
    return user_password_;
}

QString YLUser::getUserSignature() const
{
    return user_signature_;
}

QString YLUser::getUserImagePath() const
{
    return user_image_path;
}
