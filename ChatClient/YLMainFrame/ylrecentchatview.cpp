#include "ylrecentchatview.h"
#include "ylfriendlistitem.h"
#include <QMouseEvent>
#include <QScrollBar>
#include <QDebug>
YLRecentChatView::YLRecentChatView(QWidget *parent) : QListWidget(parent)
{
    setObjectName("YLRecentChatView");
    setStyleSheet(qss_this + qss_scroll_bar);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::NoFocus);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

}

void YLRecentChatView::add(const YLFriend &fri, int pos)
{
    QListWidgetItem *item = new QListWidgetItem;
    insertItem(pos, item);
    item->setSizeHint(QSize(width() - 30, 56));
    YLFriendListItem *item_widget = new YLFriendListItem(YLFriendListItem::RECENTTLYCHATITEM);
    connect(item_widget, &YLFriendListItem::moveToTop,      this, &YLRecentChatView::on_move_to_top);
    connect(item_widget, &YLFriendListItem::deleteFromList, this, &YLRecentChatView::on_del_from_list);
    item_widget->setData(fri);
    setItemWidget(item, item_widget);
}

void YLRecentChatView::addItem(const YLFriend &fri)
{
    for (auto iter = m_data.begin(); iter != m_data.end(); ++iter)
    {
        if (fri == *iter)
        {
            m_data.erase(iter);
            break;
        }
    }

    for (auto &f : m_top_data)
    {
        if (f == fri)
        {
            f = fri;
            break;
        }
    }

    m_data.push_front(fri);
    updateList();
}


void YLRecentChatView::updateList()
{
    clear();
    int i = 0;

    for (auto elem : m_top_data)
    {
        add(elem, i);
        static_cast<YLFriendListItem*>(itemWidget(item(i++)))->setMarkTop(true);
    }

    for (auto elem : m_data)
    {
        bool found = false;
        for (auto e : m_top_data)
        {
            if (e == elem)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            add(elem, i++);
        }

        qDebug() << m_data.size();
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
    bool exist = false;

    for (auto iter = m_top_data.begin(); iter != m_top_data.end(); ++iter)
    {
        if (*iter == f)
        {
            m_top_data.erase(iter);
            exist = true;
            break;
        }
    }

    if (!exist)
        m_top_data.push_front(f);

    updateList();

}

void YLRecentChatView::on_del_from_list(const YLFriend &f)
{
    for (auto iter = m_top_data.begin(); iter != m_top_data.end(); ++iter)
    {
        if (*iter == f)
        {
            m_top_data.erase(iter);
            break;
        }
    }

    for (auto iter = m_data.begin(); iter != m_data.end(); ++iter)
    {
        if (*iter == f)
        {
            m_data.erase(iter);
            break;
        }
    }

    updateList();
}

