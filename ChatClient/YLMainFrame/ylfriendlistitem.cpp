#include "ylfriendlistitem.h"
#include "YLCommonControl/ylheadframe.h"
#include <QLabel>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include "YLChatWidget/ylchatwidget.h"
#include "YLCommonControl/ylmodifyremark.h"
#include "ylmainwidget.h"
#include "YLNetWork/http/httphelper.h"
#include <QDebug>
#include "YLNetWork/ylbusiness.h"
#include "globaldata.h"
#include "ylinfomationwidget.h"
#include "YLCommonControl/ylmessagebox.h"
YLFriendListItem::YLFriendListItem(YLListItemType type, QWidget *parent) : QWidget(parent)
{
    item_type_ = type;
    m_is_mark_top = false;
    init();
    initMenu();

}

void YLFriendListItem::init()
{
    head_frame_ = new YLHeadFrame(this);
    head_frame_->resize(40, 40);

    label_up_ = new QLabel(this);
    label_down_ = new QLabel(this);
    label_time_ = new QLabel(this);

    m_http_helper = new HttpHelper;
    connect(m_http_helper, &HttpHelper::downloadFinshed, this, [this](){
        head_frame_->setHeadFromLocal("./" + m_http_helper->getFilename(), friend_.friendIsOnline());
        friend_.setFriendImagePath(m_http_helper->getFilename());
    });
}


void YLFriendListItem::initMenu()
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

    menu_->addAction(action_on_top);
    menu_->addAction(action_remove);
    menu_->addAction(action_modify_remark);
    second_menu_ = menu_->addMenu("移动好友至");
    menu_->addAction(aciton_delete);

    connect(action_send_msg, &QAction::triggered, this, [this](){
        YLChatWidget *chatWidget = new YLChatWidget();
        chatWidget->resize(800, 600);
        chatWidget->setFriend(friend_);
        chatWidget->show();
    });

    connect(action_remove, &QAction::triggered, this, [this](){
        emit deleteFromList(friend_);
    });

    connect(action_on_top, &QAction::triggered, this, [this](){
        emit moveToTop(friend_);
    });

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

void YLFriendListItem::setSecondMenu(const QMap<int, QString> &groups, const QString &currGroupName)
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

void YLFriendListItem::setMarkTop(bool flag)
{
    m_is_mark_top = flag;

    if (m_is_mark_top)
    {
        action_on_top->setText("取消会话置顶");
    }
    else
    {
        action_on_top->setText("会话置顶");
    }
    update();
}


void YLFriendListItem::setData(const YLFriend &friend_)
{
    this->friend_ = friend_;
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
        label_time_->setText(placeholder_text_3.arg(friend_.friendLastChatTime()));
        label_down_->setText(placeholder_text_2.arg(friend_.friendLastMessage()));
        head_frame_->setHeadFromLocal(friend_.friendImagePath());
    }


    m_http_helper->download(friend_.friendImagePath());
}

void YLFriendListItem::resizeEvent(QResizeEvent *event)
{
    int h = height();
    head_frame_->move(5, (h - head_frame_->height()) / 2);
    label_up_->move(50, head_frame_->y());
    label_down_->move(50, label_up_->y() + label_up_->height());
    label_time_->move(width() - 35, label_up_->y());
    QWidget::resizeEvent(event);
}

void YLFriendListItem::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
    if (event->button() == Qt::RightButton)
        menu_->exec(QCursor::pos());
}

void YLFriendListItem::paintEvent(QPaintEvent *event)
{
    if (m_is_mark_top)
    {
        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(3, 3, 10, 10, QPixmap(":/res/MainFrame/aio_top_mark.png"));
    }

    QWidget::paintEvent(event);
}


