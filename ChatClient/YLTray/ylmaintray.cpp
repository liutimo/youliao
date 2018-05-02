#include "ylmaintray.h"
#include "globaldata.h"
#include <QAction>
#include <QMenu>
#include <QUrl>
#include <QDesktopWidget>
#include <QApplication>
#include "ylmessagetip.h"
#include <QTimer>
#include "YLEntityObject/ylmessage.h"
YLMainTray *YLMainTray::m_instance = nullptr;

YLMainTray* YLMainTray::instance()
{
    if (nullptr == m_instance)
        m_instance = new YLMainTray;
    return m_instance;
}

YLMainTray::YLMainTray(QObject *parent) : QSystemTrayIcon(parent)
{
    m_icon_path = ":/res/imonline.ico";
    flag = false;
    initActions();
    initMenu();
    setIcon(QIcon(m_icon_path));

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        if (flag)
            setIcon(QIcon(m_icon_path));
        else
            setIcon(QIcon(""));
        flag = !flag;
    });


    connect(this, &YLMainTray::activated, this, [this](QSystemTrayIcon::ActivationReason reason){
        if (reason == QSystemTrayIcon::Trigger)
        {
            if(GlobalData::getMessages().size() > 0)
            {
                auto w = QApplication::desktop();
                YLMessageTip *ww = YLMessageTip::instance();
                ww->updateList();
                ww->move(QCursor::pos().x() - 150, w->availableGeometry().height() - ww->height());
                ww->show();
            }
            else
            {
                emit showMain();
            }
        }
    });
}

void YLMainTray::initActions()
{
    m_status_online = new QAction(QIcon(":/res/YLCommonControl/imonline.png"), "在线", this);
    m_status_offline = new QAction(QIcon(":/res/YLCommonControl/mute.png"), "离线", this);
    m_status_invisible = new QAction(QIcon(":/res/YLCommonControl/invisible.png"), "隐身", this);

    m_show_main = new QAction("打开主面板", this);
    connect(m_show_main, &QAction::triggered, this, [this](){ emit showMain(); });

    m_quit = new QAction("退出", this);
    connect(m_quit, &QAction::triggered, this, [this](){ emit quit(); });
}

void YLMainTray::initMenu()
{
    m_tray_menu = new QMenu();
    m_tray_menu->addAction(m_status_online);
    m_tray_menu->addAction(m_status_invisible);
    m_tray_menu->addAction(m_status_offline);
    m_tray_menu->addSeparator();
    m_tray_menu->addAction(m_show_main);
    m_tray_menu->addAction(m_quit);

    setContextMenu(m_tray_menu);
}


void YLMainTray::receiveMessage(const message::MessageData &content)
{
    uint32_t friendId = content.from_user_id();

    YLMessage msg;
    msg.setFriendId(friendId);
    msg.setMessageId(content.msg_id());
    msg.setMsgContent(content.message_data().c_str());
    msg.setCreateTime(content.create_time());

    GlobalData::addMessage(friendId, msg);

    m_icon_path = GlobalData::getFriendById(friendId).friendImageName();
    m_timer->start(300);

}



