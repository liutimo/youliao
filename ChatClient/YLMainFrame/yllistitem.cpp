#include "yllistitem.h"
#include "YLCommonControl/ylheadframe.h"
#include <QLabel>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include "YLChatWidget/ylsinglechatwidget.h"
#include "YLCommonControl/ylmodifyremark.h"
#include "ylmainwidget.h"
#include "YLNetWork/http/httphelper.h"
#include <QDebug>
#include <QDateTime>
#include "YLNetWork/ylbusiness.h"
#include "globaldata.h"
#include "ylinfomationwidget.h"
#include "YLCommonControl/ylmessagebox.h"
#include "YLTray/ylcounterbubble.h"
#include "YLTray/ylmessagetip.h"
YLListItem::YLListItem(YLListItemType type, QWidget *parent) : QWidget(parent)
{
    item_type_ = type;
    init();
    initMenu();

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

    m_http_helper = new HttpHelper;
    connect(m_http_helper, &HttpHelper::downloadFinshed, this, [this](){
        head_frame_->setHeadFromLocal("./" + m_http_helper->getFilename(), friend_.friendIsOnline());
        friend_.setFriendImagePath(m_http_helper->getFilename());
    });
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
//    QAction *action_move_to       = new QAction("");
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
    second_menu_ = menu_->addMenu("移动好友至");
    menu_->addAction(aciton_delete);

    connect(action_send_msg, &QAction::triggered, this, &YLListItem::openChatWidget);

    connect(action_modify_remark, &QAction::triggered, this, [this](){
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
    });

    connect(action_show_info, &QAction::triggered, this, [this]()
    {
        YLInfomationWidget *w = new YLInfomationWidget;
        w->setFriendInfo(friend_);
        w->show();
    });

    connect(aciton_delete, &QAction::triggered, this, [this]()
    {
        YLMessageBox *messageBox = new YLMessageBox(BUTTON_CANNEL | BUTTON_OK, this);
        messageBox->setTitle("Warn");
        QString toolTip = friend_.friendRemark().isEmpty() ? friend_.friendNickName() : friend_.friendRemark();
        messageBox->setToolTip("Are you sure delete " + toolTip);
        BottonResult res = messageBox->exec();
        if (res == ID_OK)
        {
            emit deleteFriend(friend_.friendId());
        }
    });
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
        label_up_->setText(placeholder_text_1_1.arg(friend_.friendRemark().isEmpty() ? friend_.friendNickName() : friend_.friendRemark()));
        QDateTime dateTime;
        dateTime.setTime_t(session.getSessionLastChatTime());
        label_time_->setText(placeholder_text_3.arg(dateTime.toString("hh:mm")));
        QString msg = session.getSessionLastChatMessage();
        QRegExp re;
        re.setPattern("<img.*src='.*'.*>");
        re.setMinimal(true);
        msg.replace(re, "[Picture]");
        label_down_->setText(placeholder_text_2.arg(msg));
        head_frame_->setHeadFromLocal(friend_.friendImagePath());
        if (session.getUnReadMsgCount() > 0)
        {
            m_counter_bubble->show();
            m_counter_bubble->setNumber(session.getUnReadMsgCount());
        }
    }


    m_http_helper->download(friend_.friendImagePath());
}

void YLListItem::setData(const YLGroup &g, const YLSession &session)
{

}

void YLListItem::setData(const YLSession &session)
{
    if (item_type_ == REQUEST)
    {
        label_up_->setText("验证消息");
    }
}

void YLListItem::resizeEvent(QResizeEvent *event)
{
    int h = height();
    head_frame_->move(5, (h - head_frame_->height()) / 2);
    label_up_->move(50, head_frame_->y());
    label_down_->move(50, label_up_->y() + label_up_->height());
    label_time_->move(width() - 35, label_up_->y());
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
                    singleChatWidget->receiveMessage(friend_.friendId(), msg.getMsgContent());
                }

                GlobalData::removeMessageByFriendId(friend_.friendId());
                YLMessageTip::instance()->updateList();
                GlobalData::setLatestMsgId(friend_.friendId(), 0);
                emit readCompleted(friend_.friendId());
            }
            });
    }
    singleChatWidget->show();

}
