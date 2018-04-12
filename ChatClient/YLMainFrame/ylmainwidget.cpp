#include "ylmainwidget.h"
#include "YLCommonControl/ylheadandstatusframe.h"
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include "globaldata.h"
#include "ylsearchlineedit.h"
#include "ylsignaturelineedit.h"
#include "ylnavigationbar.h"
#include "ylrecentchatview.h"
#include "ylfriendlistview.h"
#include "YLCommonControl/ylmessagebox.h"
#include "YLNetWork/http/httpdownloader.h"
#include "YLNetWork/ylbusiness.h"
#include <QTimer>

using namespace youliao::pdu;

QPoint YLMainWidget::center = QPoint();

YLMainWidget::YLMainWidget(QWidget *parent) : YLBasicWidget(parent)
{
    resize(400, 800);
    init();
    initListWidget();
    center = geometry().center();
}

void YLMainWidget::init()
{
    min_button_ = new QPushButton(this);
    min_button_->resize(close_button_->size());
    min_button_->setObjectName("min_button_");
    min_button_->setStyleSheet(qss_min_button);

    connect(min_button_, &QPushButton::clicked, this, [this](){
        hide();
    });


    skin_button_ = new QPushButton(this);
    skin_button_->resize(close_button_->size());
    skin_button_->setObjectName("skin_button_");
    skin_button_->setStyleSheet(qss_skin_button);

    logo_label_ = new QLabel(this);
    logo_label_->setObjectName("logo_label_");
    logo_label_->setStyleSheet(qss_logo_label);
    logo_label_->resize(QSize(21, 24));

    head_status_frame_  = new YLHeadAndStatusFrame(this);
    head_status_frame_->resize(80, 80);

    nickname_label_ = new QLabel(this);
    nickname_label_->setText("hahaha");
    nickname_label_->setObjectName("nickname_label_");
    nickname_label_->setStyleSheet(qss_nickname_label);

    signature_lineedit_ = new YLSignatureLineEdit(this);
    signature_lineedit_->resize(width() - 145, 30);
    connect(signature_lineedit_, &YLSignatureLineEdit::editFinished, this, [this](){
        YLBusiness::modifySignature(GlobalData::getCurrLoginUserId(), signature_lineedit_->text());
    });


    search_lineedit_ = new YLSearchLineEdit(this);
    search_lineedit_->resize(width() - 1, 40);

    navigation_bar_ = new YLNavigationBar(this);
    navigation_bar_->resize(width() - 1, 40);
    connect(navigation_bar_, &YLNavigationBar::click_index, this, [this](int index){
        for (int i = 0; i < vec.size(); ++i)
        {
            if (i == index - 1)
                vec[i]->show();
            else
                vec[i]->hide();
        }
    });

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        YLBusiness::heartBeat();
    });


    m_http_dowloader = new HttpDownloader;
    connect(m_http_dowloader, &HttpDownloader::downloadFinshed, this, [this](){
        head_status_frame_->setHeadFromLocal("./" + m_http_dowloader->getFilename());
    }, Qt::QueuedConnection);

}

void YLMainWidget::initListWidget()
{
    //[1] 消息列表
    YLRecentChatView *yl_recent_chat_view = new YLRecentChatView(this);
    yl_recent_chat_view->resize(width() - 1, height() - 250);
    yl_recent_chat_view->move(0, 220);
    yl_recent_chat_view->hide();
    vec.push_back(yl_recent_chat_view);


    //[2] frient list
    YLFriendListView *yl_friendlist_view = new YLFriendListView(this);
    yl_friendlist_view->resize(width() - 1, height() - 250);
    yl_friendlist_view->move(0, 220);
    vec.push_back(yl_friendlist_view);

//    //demo
//    YLFriend y;
//    y.setFriendImagePath(":/res/1.PNG");
//    y.setFriendLastChatTime("11:22");
//    y.setFriendLastMessage("你好，我是刘正！");
//    y.setFriendNickName("刘提莫");
//    y.setFriendSigature("我希望我的青春遇见你");

//    for (int i = 0; i < 100; ++i)
//    {
//        y.setFriendAccount(QString::number(10000 + i));
//        y.setFriendRemark("刘提莫" + QString::number(i));
//        yl_recent_chat_view->addItem(y);
//    }
}

void YLMainWidget::startHeartBeat()
{
    m_timer->start(2000);
}

void YLMainWidget::resizeEvent(QResizeEvent *event)
{
    //因为要使用close_button的位置，此处需要先调用父类的resizeEvent
    YLBasicWidget::resizeEvent(event);
    min_button_->move(close_button_->x() - close_button_->width(), 0);
    skin_button_->move(min_button_->x() - min_button_->width(), 0);
    logo_label_->move(8, 8);
    head_status_frame_->move(25, 50);
    nickname_label_->move(115, 50);
    signature_lineedit_->move(115, 90);
    search_lineedit_->move(0, 140);
    navigation_bar_->move(0, 180);

}

void YLMainWidget::mousePressEvent(QMouseEvent *event)
{
    min_button_->setFocus();
    YLBasicWidget::mousePressEvent(event);
}

void YLMainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    center = geometry().center();
    YLBasicWidget::mouseReleaseEvent(event);
}

void YLMainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(40, 138, 221, 122));
    p.drawRect(rect());
}

void YLMainWidget::closeEvent(QCloseEvent *event)
{
    YLBusiness::loginOut(m_user_info->user_id());

    YLBasicWidget::closeEvent(event);
}

/************************/
void YLMainWidget::setUserInfo(UserInfo *userInfo)
{
    m_user_info = userInfo;
    GlobalData::setCurrLoginUser(*m_user_info);
    nickname_label_->setText(m_user_info->user_nick().c_str());
    signature_lineedit_->setText(m_user_info->user_sign_info().c_str());

    YLBusiness::getFriendGroupsRequest(m_user_info->user_id());
    YLBusiness::getFriendListRequest(m_user_info->user_id());

    m_http_dowloader->start(m_user_info->user_header_url().c_str());
}

