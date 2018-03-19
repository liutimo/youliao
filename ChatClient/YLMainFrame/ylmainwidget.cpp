#include "ylmainwidget.h"
#include "YLCommonControl/ylheadandstatusframe.h"
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include "ylsearchlineedit.h"
#include "ylsignaturelineedit.h"
#include "ylnavigationbar.h"
#include "ylrecentchatview.h"
#include "protobuf/youliao.base.pb.h"
#include "YLNetWork/BasePdu.h"
#include "YLNetWork/pdusender.h"
#include "YLNetWork/pduhandler.h"
#include "YLNetWork/netlib.h"
#include <QTimer>

using namespace youliao::pdu;

YLMainWidget::YLMainWidget(QWidget *parent) : YLBasicWidget(parent)
{
    resize(400, 800);
    init();
    initListWidget();

    //30s发送一次心跳包
    m_timer = new QTimer(this);
//    m_timer->start(300);
    connect(m_timer, &QTimer::timeout, this, [this](){

        if (m_heartbeat_send_times - PduHandler::m_heartbeat_received_times > 3)
        {
            m_timer->stop();
            //表明连接断开
            return;
        }


        base::HeartBeat heartBeat;
        BasePdu *basePdu = new BasePdu;
        basePdu->setSID(base::SID_OTHER);
        basePdu->setCID(base::CID_OTHER_HEARTBEAT);
        basePdu->writeMessage(&heartBeat);
        qDebug() << "发送心跳包";
        ++m_heartbeat_send_times;
        PduSender::instance()->addMessage(basePdu);
    });
}

void YLMainWidget::init()
{
    min_button_ = new QPushButton(this);
    min_button_->resize(close_button_->size());
    min_button_->setObjectName("min_button_");
    min_button_->setStyleSheet(qss_min_button);

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
    signature_lineedit_->setText("我是谁！！！");
    signature_lineedit_->resize(width() - 145, 30);

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
}

void YLMainWidget::initListWidget()
{
    //[1] 消息列表
    YLRecentChatView *yl_recent_chat_view = new YLRecentChatView(this);

    yl_recent_chat_view->resize(width() - 1, height() - 250);
    yl_recent_chat_view->move(0, 220);
    vec.push_back(yl_recent_chat_view);

    //demo
    YLFriend y;
    y.setFriendImagePath(":/res/2.jpeg");
    y.setFriendLastChatTime("11:22");
    y.setFriendLastMessage("你好，我是刘正！");
    y.setFriendNickName("刘提莫");
    y.setFriendSigature("我希望我的青春遇见你");
    QMap<int, YLFriend> data;
    for (int i = 0; i < 100; ++i)
    {
        y.setFriendAccount(QString::number(10000 + i));
        y.setFriendRemark("刘提莫" + QString::number(i));
        data.insert(i, y);
    }

    yl_recent_chat_view->setData(data);
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

void YLMainWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromHsv(123, 122, 155, 122));
    p.drawRect(rect());
}

/************************/
void YLMainWidget::setUserInfo(UserInfo *userInfo)
{
    nickname_label_->setText(userInfo->user_nick().c_str());
    signature_lineedit_->setText(userInfo->user_sign_info().c_str());
}


