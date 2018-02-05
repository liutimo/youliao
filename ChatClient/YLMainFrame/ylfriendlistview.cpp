#include "ylfriendlistview.h"

YLFriendListView::YLFriendListView(QWidget *parent) : QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(qss_this);
}


void YLFriendListView::setData(const QVector<QPair<QString, QVector<YLFriend> > > &data)
{
    data_ = data;
    updateList();
}


void YLFriendListView::updateList()
{
    QListWidgetItem *item = new QListWidgetItem("未命名");
    item->setSizeHint(QSize(width(), 30));
    addItem(item);

    //pair == QPair<QString, QVector<YLFriend> >
    for (auto pair : data_)
    {
        //pair.first 是 组名
        //pai.second 是 该组下好友的数量
    }
}
