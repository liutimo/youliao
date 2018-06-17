#ifndef YLINFOMATIONWIDGET_H
#define YLINFOMATIONWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"
#include "YLEntityObject/ylfriend.h"
#include "YLEntityObject/yluser.h"

class QLabel;
class YLHeadFrame;
class QPushButton;

class YLInfomationWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLInfomationWidget(QWidget *parent = nullptr);
    void setFriendInfo(const YLFriend &);
    void setUserInfo();
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *e);

private:
    void initLeft();
    void initRight();

private:
    QLabel *m_header_icon;
    QLabel *m_remark_or_nick;
    QLabel *m_signature;
    YLHeadFrame *m_circle_header_icon;
    QPushButton *m_send_btn;

    QLabel *m_icon_accout;
    QLabel *m_icon_nick;
    QLabel *m_icon_remark;
    QLabel *m_icon_group;
    QLabel *m_icon_sex;
    QLabel *m_icon_school;
    QLabel *m_icon_email;
    QLabel *m_icon_phone;
    QLabel *m_icon_homeland;
    QLabel *m_icon_location;

    QLabel *m_account;
    QLabel *m_label_nick;
    QLabel *m_label_remark;
    QLabel *m_label_group;
    QLabel *m_label_sex;
    QLabel *m_label_school;
    QLabel *m_label_email;
    QLabel *m_label_phone;
    QLabel *m_label_homeland;
    QLabel *m_label_location;

    QLabel *m_nick;
    QLabel *m_remark;
    QLabel *m_group;
    QLabel *m_school;
    QLabel *m_email;
    QLabel *m_phone;
    QLabel *m_homeland;
    QLabel *m_location;

    YLFriend m_friend_info;

};

#endif // YLINFOMATIONWIDGET_H
