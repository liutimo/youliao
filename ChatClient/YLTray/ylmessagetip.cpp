#include "ylmessagetip.h"
#include <QPushButton>
#include <QResizeEvent>
#include <QLabel>
#include <QListWidget>
#include <QScrollBar>
#include "ylmessagelistitem.h"
#include "globaldata.h"
#include "signalforward.h"

YLMessageTip * YLMessageTip::m_instance = nullptr;

YLMessageTip * YLMessageTip::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = new YLMessageTip();
        m_instance->hide();
    }
    return m_instance;
}

YLMessageTip::YLMessageTip(QWidget *parent) : QWidget(parent)
{
    init();
    initTop();
    initMiddle();
    initBottom();
    installEventFilter(this);
    setStyleSheet("QWidget{background:white;}");
}


void YLMessageTip::init()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumHeight(70);
    setMaximumHeight(400);
}


void YLMessageTip::initTop()
{
    m_title = new QLabel("<p style='font:16px; color:black;'>HAHAH</p>", this);
}

void YLMessageTip::initMiddle()
{
    m_list_widget = new QListWidget(this);
    m_list_widget->move(0, 30);
    m_list_widget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_list_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_list_widget->setFocusPolicy(Qt::NoFocus);
    m_list_widget->setSelectionMode(QAbstractItemView::NoSelection);
    m_list_widget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

void YLMessageTip::initBottom()
{
    m_show_all = new QPushButton("查看全部", this);
    m_show_all->setFixedSize(80, 20);
    m_show_all->setStyleSheet(qss_button);
    connect(m_show_all, &QPushButton::clicked, this, [](){ SignalForward::instance()->forwordReadAll(); });

    m_ignore_all = new QPushButton("忽略全部", this);
    m_ignore_all->setFixedSize(80, 20);
    m_ignore_all->setStyleSheet(qss_button);
    connect(m_ignore_all, &QPushButton::clicked, this, [](){ SignalForward::instance()->forwordIgnoreAll(); });
}


void YLMessageTip::resizeEvent(QResizeEvent *event)
{
    m_title->move(5, 5);
    m_show_all->move(width() - 90, height() - 25);
    m_ignore_all->move(10, height() - 25);
}

bool YLMessageTip::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::WindowDeactivate)
    {
        if (watched == this)
        {
            hide();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}


void YLMessageTip::updateList()
{
    m_list_widget->clear();
    auto messages = GlobalData::getMessages();
    for (auto elem : messages)
    {
        QListWidgetItem *item = new QListWidgetItem(m_list_widget);
        m_list_widget->addItem(item);
        item->setSizeHint(QSize(300, 45));
        YLMessageListItem *w = new YLMessageListItem;
        m_list_widget->setItemWidget(item, w);

        uint32_t friendId = messages.key(elem);
        YLFriend fri = GlobalData::getFriendById(friendId);

        w->setNickOrRemark(fri.friendRemark().isEmpty() ? fri.friendNickName() : fri.friendRemark());
        w->setHeadFrame(fri.friendImagePath());
        w->setCounterNumber(elem.size());
        w->setFriendId(friendId);
    }

    auto requests = GlobalData::getAddRequests();
    if (requests.size() > 0)
    {
        const YLAddRequest &latestRequest = requests.back();

        QListWidgetItem *item = new QListWidgetItem(m_list_widget);
        m_list_widget->addItem(item);
        item->setSizeHint(QSize(300, 45));
        YLMessageListItem *w = new YLMessageListItem;
        m_list_widget->setItemWidget(item, w);
        w->setType(YLMessageListItem::REQUEST);
        w->setNickOrRemark("验证消息");
        w->setHeadFrame(":/res/YLAddFriendWIdgets/AddBuddy/horn@2x.png");
        w->setCounterNumber(requests.size());
    }


    m_list_widget->resize(QSize(300, 45 * m_list_widget->count()));

    resize(300, 45 * m_list_widget->count() + 60);
}
