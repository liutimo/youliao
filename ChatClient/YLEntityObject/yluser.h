#ifndef YLUSER_H
#define YLUSER_H
#include <QObject>

class YLUser : public QObject
{
public:
    YLUser(QObject *parent = nullptr);

    YLUser(const QString &account, const QString &nickname, QObject *parent = nullptr);

    void setUserAccount(const QString &account);

    void setUserNickName(const QString &nickname);

    void setUserPassword(const QString &password);

    void setUserSignature(const QString &signature);

    void setUserImagePath(const QString &imagepath);

    QString getUserAccount() const;

    QString getUserNickName() const;

    QString getUserPassword() const;

    QString getUserSignature() const;

    QString getUserImagePath() const;

    QString getUserImageName() const;
private:
    QString user_account_;
    QString user_nickname_;
    QString user_password_;
    QString user_signature_;
    QString user_image_path;
};

#endif // YLUSER_H
