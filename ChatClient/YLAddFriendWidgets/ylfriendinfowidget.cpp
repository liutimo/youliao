#include "ylfriendinfowidget.h"
#include "YLCommonControl/ylheadframe.h"
#include "YLNetWork/http/httphelper.h"
#include "ylvalidatewidget.h"
#include <QPushButton>
#include <QLabel>


YLFriendInfoWidget::YLFriendInfoWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(200, 100);
    init();
    m_http_helper = new HttpHelper(this);
    connect(m_http_helper, &HttpHelper::downloadFinshed, this, [this](){
        m_head_frame->setHeadFromLocal(m_http_helper->getFilename());
    });
}

void YLFriendInfoWidget::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(64, 64);
    m_head_frame->move(10, 10);
    m_head_frame->setStyleSheet("QLabel:hover{border-image:url(:/res/head_bkg_highlight_100.png);}");
    m_friend_info = new QLabel(this);
    m_friend_info->move(79, 10);

    m_sex = new QLabel(this);
    m_sex->move(79, 30);

    m_add_friend = new QPushButton(this);
    m_add_friend->setStyleSheet(qss_add_friend);
    m_add_friend->setFixedSize(48, 11);
    m_add_friend->move(79, 55);
    connect(m_add_friend, &QPushButton::clicked, this, [this](){
        YLValidateWidget *w = new YLValidateWidget;
        w->setFriend(m_friend);
        w->show();
    });
}

void YLFriendInfoWidget::setFriend(const YLFriend &fri)
{
    m_friend = fri;
    if (m_type == youliao::pdu::base::SEARCH_TYPE_ACCOUNT)
        m_friend_info->setText(QString("<span>%1</span><span style='color:red;'>(%2)</span>").arg(m_friend.friendNickName()).arg(m_friend.friendAccount()));
    else
        m_friend_info->setText(QString("<span style='color:red;'>%1</span>").arg(m_friend.friendNickName()));
    m_sex->setText("<span style='color:#8C8C77'>" + m_friend.friendSex() + "</span>");


    m_http_helper->download(m_friend.friendImagePath());


}
