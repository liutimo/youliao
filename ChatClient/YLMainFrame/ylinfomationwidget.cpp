#include "ylinfomationwidget.h"
#include "YLCommonControl/ylheadframe.h"
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
YLInfomationWidget::YLInfomationWidget(QWidget *parent) : YLBasicWidget(parent)
{
    resize(730, 530);
    initLeft();
    initRight();
}

void YLInfomationWidget::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::white);
    p.drawRect(360, 0, width() - 360, height());
}

void YLInfomationWidget::initLeft()
{
    m_header_icon = new QLabel(this);
    m_header_icon->setPixmap(QPixmap(":/res/1.jpeg"));
    m_header_icon->setFixedSize(360, 350);
    m_header_icon->move(0, 0);

    m_circle_header_icon = new YLHeadFrame(this);
    m_circle_header_icon->setHeadFromLocal(":/res/1.jpeg");
    m_circle_header_icon->setFixedSize(60, 60);
    m_circle_header_icon->move(80, 380);

    m_remark_or_nick = new QLabel(this);
    m_remark_or_nick->setText("<p style='font:16px; color:white;'>Demo</p>");
    m_remark_or_nick->move(150, 380);

    m_signature = new QLabel(this);
    m_signature->setText("come on now, follow my lead");
    m_signature->move(150, 410);

    m_send_btn = new QPushButton(this);
    m_send_btn->setText("Send Message");
    m_send_btn->setFixedSize(200, 35);
    m_send_btn->move(80, 450);
}


void YLInfomationWidget::initRight()
{
    m_icon_accout = new QLabel(this);
    m_icon_accout->setFixedSize(22, 22);
    m_icon_accout->move(380, 30);
    m_icon_accout->setPixmap(QPixmap(":/res/Info/account.png"));

    m_icon_nick = new QLabel(this);
    m_icon_nick->setFixedSize(22, 22);
    m_icon_nick->move(380, 65);
    m_icon_nick->setPixmap(QPixmap(":/res/Info/nick.png"));

    m_icon_remark = new QLabel(this);
    m_icon_remark->setFixedSize(22, 22);
    m_icon_remark->move(380, 100);
    m_icon_remark->setPixmap(QPixmap(":/res/Info/remark.png"));

    m_icon_group = new QLabel(this);
    m_icon_group->setFixedSize(22, 22);
    m_icon_group->move(380, 135);
    m_icon_group->setPixmap(QPixmap(":/res/Info/group.png"));

    m_icon_sex = new QLabel(this);
    m_icon_sex->setFixedSize(22, 22);
    m_icon_sex->move(380, 170);
    m_icon_sex->setPixmap(QPixmap(":/res/Info/sex_age.png"));

    m_icon_school = new QLabel(this);
    m_icon_school->setFixedSize(22, 22);
    m_icon_school->move(380, 205);
    m_icon_school->setPixmap(QPixmap(":/res/Info/school.png"));

    m_icon_email = new QLabel(this);
    m_icon_email->setFixedSize(22, 22);
    m_icon_email->move(380, 240);
    m_icon_email->setPixmap(QPixmap(":/res/Info/email.png"));

    m_account = new QLabel(this);
    m_account->setText("123456");
    m_account->move(410, 30);
    m_account->setTextInteractionFlags(Qt::TextSelectableByMouse);

    m_label_nick = new QLabel("昵称", this);
    m_label_nick->setFixedSize(30, 30);
    m_label_nick->move(410, 60);


    m_label_remark = new QLabel("备注", this);
    m_label_remark->setFixedSize(30, 30);
    m_label_remark->move(410, 95);

    m_label_group = new QLabel("分组", this);
    m_label_group->setFixedSize(30, 30);
    m_label_group->move(410, 130);

    m_label_sex = new QLabel("男", this);
    m_label_sex->setFixedSize(30, 30);
    m_label_sex->move(410, 165);

    m_label_school = new QLabel("学校", this);
    m_label_school->setFixedSize(30, 30);
    m_label_school->move(410, 200);

    m_label_email = new QLabel("邮箱", this);
    m_label_email->setFixedSize(30, 30);
    m_label_email->move(410, 235);

    m_nick = new QLabel(this);
    m_nick->setText("I'll be fine!");
    m_nick->move(450, 66);
    m_nick->setTextInteractionFlags(Qt::TextSelectableByMouse);

    m_remark = new QLabel(this);
    m_remark->setText("John");
    m_remark->move(450, 101);
    m_remark->setTextInteractionFlags(Qt::TextSelectableByMouse);


    m_group = new QLabel(this);
    m_group->setText("Friend");
    m_group->move(450, 136);
    m_group->setTextInteractionFlags(Qt::TextSelectableByMouse);


    m_school = new QLabel(this);
    m_school->setText("CSLGDX");
    m_school->move(450, 206);
    m_school->setTextInteractionFlags(Qt::TextSelectableByMouse);


    m_email = new QLabel(this);
    m_email->setText("779564531@qq.com");
    m_email->move(450, 241);
    m_email->setTextInteractionFlags(Qt::TextSelectableByMouse);
}


void YLInfomationWidget::setFriendInfo(const YLFriend &fri)
{
    m_friend_info = fri;

    m_account->setText(m_friend_info.friendAccount());
    m_nick->setText(m_friend_info.friendNickName());
    m_remark->setText(m_friend_info.friendRemark());
    m_group->setText(m_friend_info.friendGroup());
//    m_label_sex->setText(m_friend_info.friend);
//    m_email->setText(m_friend_info.friend);

    m_header_icon->setPixmap(QPixmap(m_friend_info.friendImageName()));
    m_circle_header_icon->setHeadFromLocal(m_friend_info.friendImageName());
    m_signature->setText(m_friend_info.friendSigature());
    m_remark_or_nick->setText(m_friend_info.friendRemark().isEmpty() ? m_friend_info.friendNickName() : m_friend_info.friendRemark());
}
