#include "ylrecentchatview.h"
#include "ylfriendlistitem.h"
#include <QMouseEvent>
YLRecentChatView::YLRecentChatView(QWidget *parent) : QListWidget(parent)
{
    setObjectName("YLRecentChatView");
    setStyleSheet(qss_this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::NoFocus);
}

void YLRecentChatView::setData(const QMap<int, YLFriend> &data)
{
    data_ = data;
    updateList();
}

void YLRecentChatView::updateList()
{
    clear();

    for (int i = 0; i < data_.size(); ++i)
    {
        QListWidgetItem *item = new QListWidgetItem;
        addItem(item);
        item->setSizeHint(QSize(width() - 30, 56));
        YLFriendListItem *item_widget = new YLFriendListItem(YLFriendListItem::RECENTTLYCHATITEM);
        connect(item_widget, &YLFriendListItem::moveToTop,      this, &YLRecentChatView::on_move_to_top);
        connect(item_widget, &YLFriendListItem::deleteFromList, this, &YLRecentChatView::on_del_from_list);
        item_widget->setData(data_[i]);
        setItemWidget(item, item_widget);
    }

}

void YLRecentChatView::mousePressEvent(QMouseEvent *event)
{
    auto item = itemAt(event->pos());
    if (item)
        item->setSelected(true);
    QListWidget::mousePressEvent(event);
}

void YLRecentChatView::on_move_to_top(const YLFriend &f)
{
    int key = data_.key(f);

    for (int i = key; i > 0; --i)
    {
        data_[i] = data_[i - 1];
    }

    data_[0] = f;

    updateList();
}

void YLRecentChatView::on_del_from_list(const YLFriend &f)
{
    int key = data_.key(f);
    data_.remove(key);
    for (int i = key; i <= data_.size(); ++i)
    {
        data_[i] = data_[i + 1];
    }

    updateList();
}

