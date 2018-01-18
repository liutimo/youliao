#include "ylrecentchatview.h"
#include "ylfriendlistitem.h"

YLRecentChatView::YLRecentChatView(QWidget *parent) : QListWidget(parent)
{
    setObjectName("YLRecentChatView");
    setStyleSheet(qss_this);
}

void YLRecentChatView::setData(const QMap<int, YLFriend> &data)
{
    data_ = data;
    updateList();
}

void YLRecentChatView::updateList()
{
    for (int i = 0; i < data_.size(); ++i)
    {
        QListWidgetItem *item = new QListWidgetItem;
        addItem(item);
        item->setSizeHint(QSize(width(), 46));
        YLFriendListItem *item_widget = new YLFriendListItem(YLFriendListItem::RECENTTLYCHATITEM);
        item_widget->setData(data_[i]);
        setItemWidget(item, item_widget);
    }
}
