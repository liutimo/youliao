#include "ylfriendlistitem.h"

#include "YLEntityObject/ylfriend.h"
#include "YLCommonControl/ylheadframe.h"
#include <QLabel>

YLFriendListItem::YLFriendListItem(YLListItemType type, QWidget *parent) : QWidget(parent)
{
    item_type_ = type;
    init();
}

void YLFriendListItem::init()
{
    head_frame_ = new YLHeadFrame(this);
    head_frame_->resize(40, 40);

    label_up_ = new QLabel(this);
    label_down_ = new QLabel(this);
    label_time_ = new QLabel(this);
}

void YLFriendListItem::setData(const YLFriend &friend_)
{
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
    head_frame_->move(5, 3);
    label_up_->move(50, 3);
    label_down_->move(50, 23);
    label_time_->move(width() - 35, 5);
    QWidget::resizeEvent(event);
}
