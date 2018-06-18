#include "ylmaintray.h"
#include "globaldata.h"
#include <QAction>
#include <QMenu>
#include <QUrl>
#include <QDesktopWidget>
#include <QApplication>
#include "ylmessagetip.h"
#include <QTimer>
#include "YLNetWork/pduhandler.h"
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
            if (GlobalData::getMessages().size() > 0
                || GlobalData::getAddRequests().size() > 0
                || GlobalData::getGroupMessages().size() > 0
                || GlobalData::getGroupAddRequests().size() > 0)
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

    connect(PduHandler::instance(), &PduHandler::newAddRequest, this, &YLMainTray::newAddRequest);
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
    //需要区分消息类型
    base::MessageType msgType = content.message_type();

    YLMessage msg;
    msg.setSenderId(content.from_user_id());
    msg.setMessageId(content.msg_id());
    msg.setMsgContent(content.message_data().c_str());
    msg.setCreateTime(content.create_time());
    msg.setMessageType(msgType);
    msg.setReceiverId(content.to_id());

    if (msgType == base::MESSAGE_TYPE_GROUP_TEXT || msgType == base::MESSAGE_TYPE_GROUP_AUDIO)
    {
        //群组消息
        uint32_t groupId = content.to_id();
//        msg.setSenderId(content.to_user_id());
        msg.setGroupId(groupId);

        //获取群组头像
        m_icon_path = GlobalData::getGroupByGroupId(groupId).getGroupImage();

        //放入内存
        GlobalData::addGroupMessage(groupId, msg);
    }
    else if (msgType == base::MESSAGE_TYPE_SINGLE_AUDIO || msgType == base::MESSAGE_TYPE_SINGLE_TEXT)
    {
        //个人消息
        uint32_t friendId = content.from_user_id();

        //放入内存
        GlobalData::addMessage(friendId, msg);

        m_icon_path = GlobalData::getFriendById(friendId).friendImageName();
    }
}

void YLMainTray::newAddRequest()
{
    YLMessageTip::instance()->updateList();
}


