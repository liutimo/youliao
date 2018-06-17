#include "yllistitem.h"
#include "globaldata.h"
#include "ylmainwidget.h"
#include "ylinfomationwidget.h"
#include "YLTray/ylmessagetip.h"
#include "YLNetWork/ylbusiness.h"
#include "YLTray/ylcounterbubble.h"
#include "YLCommonControl/ylheadframe.h"
#include "YLCommonControl/ylmessagebox.h"
#include "YLMainFrame/ylgroupinfowidget.h"
#include "YLCommonControl/ylmodifyremark.h"
#include "YLCommonControl/ylbutton.h"
#include "YLAddFriendWidgets/ylvalidatemessagewidget.h"
#include "YLDataBase/yldatabase.h"

#include <QMenu>
#include <QLabel>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QDateTime>
#include <QMouseEvent>

YLListItem::YLListItem(YLListItemType type, QWidget *parent) : QWidget(parent)
{
    item_type_ = type;
    init();

    //因为要保证second_menu_ 在menu_之前初始化,所以将其初始化工作放在构造函数中
    second_menu_ = new QMenu("移动好友至", this);
}

void YLListItem::init()
{
    head_frame_ = new YLHeadFrame(this);
    head_frame_->resize(40, 40);

    m_counter_bubble = new YLCounterBubble(this);
    m_counter_bubble->hide();

    label_up_ = new QLabel(this);
    label_down_ = new QLabel(this);
    label_time_ = new QLabel(this);
    label_time_->setFixedWidth(100);
    label_time_->setAlignment(Qt::AlignRight);
}


void YLListItem::initMenu()
{
    menu_ = new QMenu(this);

    QAction *action_send_msg      = new QAction("发送即时消息");
    QAction *action_show_info     = new QAction("查看资料");
    QAction *action_msg_record    = new QAction("消息记录");
             action_on_top        = new QAction("会话置顶");
    QAction *action_remove        = new QAction("从回话列表移除");
    QAction *action_modify_remark = new QAction("修改备注姓名");
    QAction *aciton_delete        = new QAction("删除好友");

    menu_->addAction(action_send_msg);

    menu_->addSeparator();

    menu_->addAction(action_show_info);
    menu_->addAction(action_msg_record);

    menu_->addSeparator();

    if (item_type_ == RECENTTLYCHATITEM)
    {
        menu_->addAction(action_on_top);
        menu_->addAction(action_remove);
        connect(action_remove, &QAction::triggered, this, [this](){
            emit deleteFromList(session_);
        });

        connect(action_on_top, &QAction::triggered, this, [this](){
            emit moveToTop(session_);
        });
    }
    menu_->addAction(action_modify_remark);
    menu_->addMenu(second_menu_);
    menu_->addAction(aciton_delete);

    connect(action_send_msg, &QAction::triggered, this, &YLListItem::openChatWidget);
    connect(action_modify_remark, &QAction::triggered, this, &YLListItem::onModifyRemark);
    connect(action_show_info, &QAction::triggered, this, &YLListItem::onShowFriendInformationWidget);
    connect(aciton_delete, &QAction::triggered, this, &YLListItem::onDeleteFriend);
}

void YLListItem::initGroupMenu()
{
    menu_ = new QMenu(this);
    QAction *action_send_msg      = new QAction("发送即时消息");
    QAction *action_show_info     = new QAction("查看群资料");
    QAction *action_msg_record    = new QAction("查看消息记录");
             action_on_top        = new QAction("会话置顶");
    QAction *action_remove        = new QAction("从回话列表移除");
    QAction *action_modify_remark = new QAction("修改备注姓名");
    QAction *aciton_exit_group    = new QAction("退出该群");

    menu_->addAction(action_send_msg);
    menu_->addSeparator();
    menu_->addAction(action_show_info);
    menu_->addAction(action_msg_record);
    menu_->addSeparator();
    menu_->addAction(action_on_top);
    menu_->addAction(action_remove);
    menu_->addAction(action_modify_remark);
    menu_->addSeparator();
    menu_->addAction(aciton_exit_group);

    connect(aciton_exit_group,      &QAction::triggered, this, &YLListItem::onExitGroup);
    connect(action_modify_remark,   &QAction::triggered, this, &YLListItem::onModifyGroupRemark);
    connect(action_send_msg,        &QAction::triggered, this, &YLListItem::onOpenGroupChatWidget);
    connect(action_show_info,       &QAction::triggered, this, &YLListItem::onShowGroupInformationWidget);

    connect(action_remove,          &QAction::triggered, this, [this](){
        emit deleteFromList(session_);
    });

    connect(action_on_top,          &QAction::triggered, this, [this](){
        emit moveToTop(session_);
    });
}


void YLListItem::initValidateMsgMenu()
{
    menu_ = new QMenu(this);

    QAction *action_open_widget   = new QAction("打开验证窗口");
             action_on_top        = new QAction("会话置顶");
    QAction *action_remove        = new QAction("从回话列表移除");

    menu_->addAction(action_open_widget);
    menu_->addSeparator();
    menu_->addAction(action_on_top);
    menu_->addAction(action_remove);


    connect(action_remove,          &QAction::triggered, this, [this](){
        emit deleteFromList(session_);
    });

    connect(action_on_top,          &QAction::triggered, this, [this](){
        emit moveToTop(session_);
    });

    connect(action_open_widget, &QAction::triggered, this, &YLListItem::onOpenValidateWidget);

}

void YLListItem::setSecondMenu(const QMap<int, QString> &groups, const QString &currGroupName)
{
    for (QString actionName : groups)
    {
        int newGroupId = groups.key(actionName);
        int oldGroupId = groups.key(currGroupName);
        if (currGroupName == actionName)
            continue;

        QAction *action = new QAction(actionName);
        second_menu_->addAction(action);
        connect(action, &QAction::triggered, this, [this, oldGroupId, newGroupId](){
            emit moveFriendToGroup(friend_.friendId(), oldGroupId, newGroupId);
        });
    }
}

void YLListItem::setMarkTop(bool flag)
{
    session_.setSessionTop(flag);

    if (session_.sessionTop())
    {
        action_on_top->setText("取消会话置顶");
    }
    else
    {
        action_on_top->setText("会话置顶");
    }
    update();
}


void YLListItem::setData(const YLFriend &friend_, const YLSession &session)
{
    this->friend_ = friend_;
    session_ = session;
    if (item_type_ == FRIENDITEM)  //作为好友列表中的item
    {
        initMenu();
        //有备注:  备注(昵称)
        //没备注:  昵称(账号)
        if (friend_.friendRemark().isEmpty())
            label_up_->setText(placeholder_text_1.arg(friend_.friendNickName(), friend_.friendAccount()));
        else
            label_up_->setText(placeholder_text_1.arg(friend_.friendRemark(), friend_.friendNickName()));

        label_down_->setText(placeholder_text_2.arg(friend_.friendSigature()));
    }
    else if (item_type_ == RECENTTLYCHATITEM)   //作为最近聊天记录列表中的item
    {

        initMenu();

        label_up_->setText(placeholder_text_1_1.arg(friend_.friendRemark().isEmpty() ? friend_.friendNickName() : friend_.friendRemark()));


        //处理时间显示格式
        label_time_->setText(placeholder_text_3.arg(handleTime(session_.getSessionLastChatTime())));

//        QDateTime dateTime;
//        dateTime.setTime_t(session.getSessionLastChatTime());
//        label_time_->setText(placeholder_text_3.arg(dateTime.toString("hh:mm")));

        QString msg = session.getSessionLastChatMessage();
        QRegExp re;
        re.setPattern("<img.*src='.*'.*>");
        re.setMinimal(true);
        msg.replace(re, "[图片]");
        label_down_->setText(placeholder_text_2.arg(msg));
        if (session.getUnReadMsgCount() > 0)
        {
            m_counter_bubble->show();
            m_counter_bubble->setNumber(session.getUnReadMsgCount());
        }
    }

    head_frame_->setHeadFromUrl(friend_.friendImagePath(), friend_.friendIsOnline());
}

void YLListItem::setData(const YLGroup &group, const YLSession &session)
{
    m_group     = group;
    session_    = session;

    label_up_->setText(placeholder_text_1_1.arg(m_group.getGroupName()));
    QDateTime dateTime;
    dateTime.setTime_t(session.getSessionLastChatTime());
    label_time_->setText(placeholder_text_3.arg(dateTime.toString("hh:mm")));
    QString msg = session.getSessionLastChatMessage();
    QRegExp re;
    re.setPattern("<img.*src='.*'.*>");
    re.setMinimal(true);
    msg.replace(re, "[图片]");

    label_down_->setText(placeholder_text_2.arg(msg));

    initGroupMenu();

    if (session.getUnReadMsgCount() > 0)
    {
        m_counter_bubble->show();
        m_counter_bubble->setNumber(session.getUnReadMsgCount());
    }

    head_frame_->setHeadFromUrl(m_group.getGroupImage(), true);
}

void YLListItem::setData(const YLSession &session)
{
    initValidateMsgMenu();
    session_ = session;
    head_frame_->setHeadFromLocal(":/res/YLAddFriendWIdgets/AddBuddy/SessionNode.png");
    label_up_->setText(placeholder_text_1_1.arg("验证消息"));
    label_down_->setText(placeholder_text_2.arg(session.getSessionLastChatMessage()));
    if (session.getUnReadMsgCount() > 0)
    {
        m_counter_bubble->show();
        m_counter_bubble->setNumber(session.getUnReadMsgCount());
    }
}

void YLListItem::resizeEvent(QResizeEvent *event)
{
    int h = height();
    head_frame_->move(5, (h - head_frame_->height()) / 2);
    label_up_->move(50, head_frame_->y());
    label_down_->move(50, label_up_->y() + label_up_->height());
    label_time_->move(width() - 105, label_up_->y());
    m_counter_bubble->move(width() - 29, label_time_->y() + label_time_->height());
    QWidget::resizeEvent(event);
}

void YLListItem::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if (event->button() == Qt::RightButton)
        menu_->exec(QCursor::pos());
}

void YLListItem::paintEvent(QPaintEvent *event)
{
    if (session_.sessionTop())
    {
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(3, 3, 10, 10, QPixmap(":/res/MainFrame/aio_top_mark.png"));
    }

    QWidget::paintEvent(event);
}



void YLListItem::openChatWidget()
{
    YLSingleChatWidget *singleChatWidget = GlobalData::getSingleChatWidget(friend_.friendId());
    if (singleChatWidget == nullptr)
    {
        singleChatWidget = new YLSingleChatWidget;
        singleChatWidget->setFriend(friend_);
        GlobalData::addSingleChatWidget(friend_.friendId(), singleChatWidget);
        connect(singleChatWidget, &YLSingleChatWidget::loadFinish, this, [this, singleChatWidget](){
            //未读计数显示则说明有未读消息
            if (m_counter_bubble->isVisible())
            {
                auto msgs = GlobalData::getMessagesByFriendId(friend_.friendId());

                for (const YLMessage &msg : msgs)
                {
                    {
                        YLDataBase db;
                        db.saveMessage(msg);
                    }

                    singleChatWidget->receiveMessage(friend_.friendId(), msg.getMsgContent());
                    YLBusiness::sendMessageAck(msg.getSenderId(), GlobalData::getCurrLoginUserId(), msg.getMessageId());
                }

                GlobalData::removeMessageByFriendId(friend_.friendId());
                YLMessageTip::instance()->updateList();
                emit readCompleted(/*friend_.friendId()*/session_.getSessionId());
            }
            });
    }
    singleChatWidget->show();
}


void YLListItem::onModifyRemark()
{
    YLModifyRemarkWidget w(this);
    w.setDefalutText(friend_.friendRemark());
    auto p = YLMainWidget::center;
    w.move(mapToGlobal(p) - mapToGlobal(w.rect().center()));
    BottonResult res = w.exec();

    if (res == ID_OK )
    {
        QString newRemark = w.getText();
        if (newRemark != friend_.friendRemark())
        {
            emit modifyRemark(friend_.friendId(), newRemark);
        }
    }
}

void YLListItem::onShowFriendInformationWidget()
{
    YLInfomationWidget *w = new YLInfomationWidget;
    w->setFriendInfo(friend_);
    w->show();
}

void YLListItem::onDeleteFriend()
{
    YLMessageBox *messageBox = new YLMessageBox(BUTTON_CANNEL | BUTTON_OK, this);
    messageBox->setWidgetTitle("删除好友");
    messageBox->setIcon(":/res/MessageBox/sysmessagebox_questionFile.png");
    QString toolTip = friend_.friendRemark().isEmpty() ? friend_.friendNickName() : friend_.friendRemark();
    messageBox->setToolTip("你是否确认删除<span style='color:#FF6666'>" + toolTip + "</span>?(删除后,你将从对方的联系人列表中消息,且以后不在接收此人的会话消息。)");
    BottonResult res = messageBox->exec();
    if (res == ID_OK)
    {
        emit deleteFriend(friend_.friendId());
    }
}


void YLListItem::onOpenGroupChatWidget()
{
    uint32_t groupId = m_group.getGroupId();
    YLGroupChatWidget *groupChatWidget = GlobalData::getGroupChatWidget(groupId);
    if (groupChatWidget == nullptr)
    {
        groupChatWidget = new YLGroupChatWidget;
        groupChatWidget->setGroup(m_group);
        GlobalData::addGroupChatWidget(groupId, groupChatWidget);
        connect(groupChatWidget, &YLGroupChatWidget::loadFinish, this, [this, groupChatWidget, groupId](){
            //未读计数显示则说明有未读消息
            if (m_counter_bubble->isVisible())
            {
                auto msgs = GlobalData::getGroupMessagesByGroupId(groupId);

                for (const YLMessage &msg : msgs)
                {
                    groupChatWidget->receiveMessage(msg.getSenderId(), msg.getMsgContent());
                }

                GlobalData::removeGroupMessageByGroupId(groupId);
                YLMessageTip::instance()->updateList();
                //下面的信号用于清除气泡
                emit readCompleted(session_.getSessionId());
            }
            }
        );
    }
    groupChatWidget->show();
}

void YLListItem::onModifyGroupRemark()
{

}

void YLListItem::onShowGroupInformationWidget()
{
    YLGroupInfoWidget *w = new YLGroupInfoWidget;
    w->setGroup(m_group);
    w->show();
}

void YLListItem::onExitGroup()
{
    YLMessageBox *m = new YLMessageBox(BUTTON_OK | BUTTON_CANNEL, this);
    m->setWidgetTitle("提示");
    m->setIcon(":/res/MessageBox/sysmessagebox_inforFile.png");

    //群组退出则表示解散该群
    if (m_group.getGroupCreator() == GlobalData::getCurrLoginUserId())
        m->setToolTip("你真的要退出该群吗？(你是群主,你的退出将解散该群)");
    else
        m->setToolTip("你真的要退出该群吗？(退群通知仅群管理员可见)");
    BottonResult br =  m->exec();

    if (br == BUTTON_OK)
        YLBusiness::exitGroup(m_group.getGroupId());
}

void YLListItem::onOpenValidateWidget()
{
    YLValidateMessageWidget *w = new YLValidateMessageWidget;
    w->show();
    GlobalData::clearAllRequest();
    YLMessageTip::instance()->updateList();


    emit readCompleted(/*friend_.friendId()*/session_.getSessionId());
}


QString YLListItem::handleTime(uint32_t timeStamp)
{
    //接收时间是今天显示 时:分
    //昨天显示昨天
    //昨天之前显示年月日
    QString timeStr;
    uint32_t now = QDateTime::currentDateTime().toTime_t();
    uint32_t toDayTimeStamp = now - (now + 8 * 3600) % (60 * 60 * 24);
    uint32_t yesterdayTimeStamp = toDayTimeStamp - 24 * 3600;


    QDateTime dateTime;
    dateTime.setTime_t(timeStamp);

    if (timeStamp > toDayTimeStamp)
    {
        timeStr = dateTime.toString("hh:mm");
    }
    else if(timeStamp >= yesterdayTimeStamp)
    {
        timeStr = "昨天";
    }
    else
    {
        timeStr = dateTime.toString("yyyy-MM-dd");
    }

    return timeStr;
}
