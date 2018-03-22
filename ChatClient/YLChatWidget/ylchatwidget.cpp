#include "ylchatwidget.h"
#include <QPushButton>
#include "ylmessageview.h"
#include "ylquickbar.h"
#include "ylmessageeditwidget.h"

#include <QDebug>

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
    m_nickname_button->setObjectName("nickname_button");
    //connect ... slot


}

void YLChatWidget::initView()
{
    m_message_view = new YLMessageView(this);
    m_quick_bar = new YLQuickBar(this);
    m_message_edit_widget = new YLMessageEditWidget(this);

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
}

void YLChatWidget::updateSize()
{
    int h = height() - 32;
    int w = width();
    m_message_view->resize(w, h / 5 * 3);
    m_quick_bar->resize(w, 26);
    m_message_edit_widget->resize(w, h / 5 * 2 - 26);
}

void YLChatWidget::resizeEvent(QResizeEvent *e)
{
    updateSize();
    updatePosition();
    YLBasicWidget::resizeEvent(e);
}

///public
void YLChatWidget::setNickName(const QString &title)
{
    m_nickname_button->setText(title);
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
