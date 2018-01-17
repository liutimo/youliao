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

    label_up_ = new QLabel("刘正(刘提莫)",this);


    label_down_ = new QLabel("我的青春遇见你", this);

    label_time_ = new QLabel("11:22", this);
}

void YLFriendListItem::resizeEvent(QResizeEvent *event)
{
    head_frame_->move(5, 3);
    label_up_->move(50, 3);
    label_down_->move(50, 23);
    label_time_->move(width() - 35, 10);
    QWidget::resizeEvent(event);
}
