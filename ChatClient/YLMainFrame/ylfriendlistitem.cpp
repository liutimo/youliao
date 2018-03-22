#include "ylfriendlistitem.h"
#include "YLCommonControl/ylheadframe.h"
#include <QLabel>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include "YLChatWidget/ylchatwidget.h"

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
    QAction *action_move_to       = new QAction("移动好友至");
    QAction *aciton_delete        = new QAction("删除好友");

    menu_->addAction(action_send_msg);

    menu_->addSeparator();

    menu_->addAction(action_show_info);
    menu_->addAction(action_msg_record);

    menu_->addSeparator();

    menu_->addAction(action_on_top);
    menu_->addAction(action_remove);
    menu_->addAction(action_modify_remark);
    menu_->addAction(action_move_to);
    menu_->addAction(aciton_delete);


    connect(action_send_msg, &QAction::triggered, this, [this](){
        YLChatWidget *chatWidget = new YLChatWidget();
        chatWidget->resize(800, 600);
        chatWidget->setNickName(friend_.getFriendNickName());
        chatWidget->show();
    });

    connect(action_remove, &QAction::triggered, this, [this](){
        emit deleteFromList(friend_);
    });

    connect(action_on_top, &QAction::triggered, this, [this](){
        emit moveToTop(friend_);
    });
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
        if (friend_.getFriendRemark().isEmpty())
            label_up_->setText(placeholder_text_1.arg(friend_.getFriendNickName(), friend_.getFriendAccount()));
        else
            label_up_->setText(placeholder_text_1.arg(friend_.getFriendRemark(), friend_.getFriendNickName()));

        label_down_->setText(placeholder_text_2.arg(friend_.getFriendSigature()));

        head_frame_->setHeadFromLocal(friend_.getFriendImagePath());

    }
    else if (item_type_ == RECENTTLYCHATITEM)   //作为最近聊天记录列表中的item
    {
        label_up_->setText(placeholder_text_1_1.arg(friend_.getFriendRemark().isEmpty() ? friend_.getFriendNickName() : friend_.getFriendRemark()));
        label_time_->setText(placeholder_text_3.arg(friend_.getFriendLastChatTime()));
        label_down_->setText(placeholder_text_2.arg(friend_.getFriendLastMessage()));
        head_frame_->setHeadFromLocal(friend_.getFriendImagePath());
    }
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


