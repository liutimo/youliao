#include "ylchatwidget.h"
#include <QPushButton>
#include "ylmessageview.h"
#include "ylquickbar.h"
#include "ylmessageeditwidget.h"
#include "ylemoticonwidget.h"
#include "YLNetWork/ylbusiness.h"
#include "YLNetWork/pduhandler.h"
#include "globaldata.h"
#include <QDebug>
#include <QDir>
YLChatWidget::YLChatWidget(QWidget *parent) : YLBasicWidget(parent)
{
    initTitleBar();
    initView();

    this->setObjectName("aaa");
    setStyleSheet("QWidget#aaa{background-color:rgb(181, 212, 240, 200);}");
}


void YLChatWidget::initTitleBar()
{
    m_max_button = new QPushButton(this);
    m_max_button->setFixedSize(32, 32);
    m_max_button->setObjectName("max_button");
    m_max_button->setStyleSheet(m_qss_max_button);
    connect(m_max_button, &QPushButton::clicked, this, &YLChatWidget::max);

    m_min_button = new QPushButton(this);
    m_min_button->setFixedSize(32, 32);
    m_min_button->setObjectName("min_button");
    m_min_button->setStyleSheet(m_qss_min_button);
    connect(m_min_button, &QPushButton::clicked, this, &YLChatWidget::min);

    m_nickname_button = new QPushButton(this);
    m_nickname_button->setFixedSize(200, 28);
    m_nickname_button->setObjectName("nickname_button");
    m_nickname_button->setStyleSheet("border:0px; font: 16px; text-align:center; background:rgba(255,255,255, 0);");
    //connect ... slot

    connect(PduHandler::instance(), &PduHandler::signleMessage, this, [this](uint32_t user_id, const QString &message){
        if (user_id == m_friend.getFriendId())
        {
            m_message_view->addRight(m_friend_header_path, message);
        }
    });
}

void YLChatWidget::initView()
{
    m_message_view = new YLMessageView(this);
    m_message_view->setStyleSheet(qss_scroll_bar);

    m_quick_bar = new YLQuickBar(this);
//    connect(m_quick_bar->getEmoticonWidget(), &YLEmoticonWidget::selected, m_message_edit_widget, &YLMessageEditWidget::addEmoticon);

    m_message_edit_widget = new YLMessageEditWidget(this);
    connect(m_message_edit_widget, &YLMessageEditWidget::enterPress, this, &YLChatWidget::sendMessage);

    m_send_button = new QPushButton("send", this);
    m_send_button->setFixedSize(90, 25);
    connect(m_send_button, &QPushButton::clicked, this, &YLChatWidget::sendMessage);

    m_close_button = new QPushButton("close", this);
    m_close_button->setFixedSize(90, 25);
    connect(m_close_button, &QPushButton::clicked, this, &YLChatWidget::close);

    updateSize();
}

void YLChatWidget::updatePosition()
{
    m_max_button->move(width() - 2 * 32, 0);
    m_min_button->move(width() - 3 * 32, 0);
    m_nickname_button->move((width() - m_nickname_button->width()) / 2, 2);


    m_message_view->move(0, 32);
    m_quick_bar->move(m_message_view->geometry().bottomLeft());
    m_message_edit_widget->move(m_quick_bar->geometry().bottomLeft());

    m_send_button->move(width() - 100, height() - 30);

    m_close_button->move(width() - 200, height() - 30);
}

void YLChatWidget::updateSize()
{
    int h = height() - 32;
    int w = width();
    m_message_view->resize(w, h / 5 * 3);
    m_quick_bar->resize(w, 26);
    m_message_edit_widget->resize(w, h / 5 * 2 - 55);
}

void YLChatWidget::resizeEvent(QResizeEvent *e)
{
    updateSize();
    updatePosition();
    YLBasicWidget::resizeEvent(e);
}

///public
void YLChatWidget::setFriend(const YLFriend&fri)
{
    m_friend = fri;
    m_nickname_button->setText(m_friend.getFriendNickName());
    m_friend_header_path = "file://" + QDir::currentPath() + "/" + m_friend.getFriendImagePath();
}

/// slot
void YLChatWidget::max()
{
    if (windowState() & Qt::WindowMaximized)
        setWindowState(Qt::WindowNoState);
    else
        setWindowState(Qt::WindowMaximized);
}

void YLChatWidget::min()
{
    setWindowState(Qt::WindowMinimized | windowState());
}

void YLChatWidget::sendMessage()
{
    QString content = m_message_edit_widget->getContent();
    m_message_edit_widget->clear();
    qDebug() << content;
    content.replace("\"", "'");
    m_message_view->addLeft(GlobalData::getCurrLoginUserIconPath(), content);
    YLBusiness::sendMessage(GlobalData::getCurrLoginUserId(), m_friend.getFriendId(), content);
}
