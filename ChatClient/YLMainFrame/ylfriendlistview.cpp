#include "ylfriendlistview.h"
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QMouseEvent>
#include <QContextMenuEvent>
YLFriendListView::YLFriendListView(QWidget *parent) : QListWidget(parent)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(qss_this);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    m_current_press_item = nullptr;

    initMenu();
    updateList();
}

YLFriendListView::~YLFriendListView()
{
    delete m_group_menu;
    delete m_blank_menu;
}

void YLFriendListView::setData(const QVector<QPair<QString, QVector<YLFriend> > > &data)
{
    data_ = data;
    updateList();
}

void YLFriendListView::initMenu()
{
    QAction *action_refresh             = new QAction("刷新好友列表");
    QAction *action_show_all_or_online  = new QAction("显示全部联系人");
    QAction *action_add_group           = new QAction("添加分组");
    connect(action_add_group, &QAction::triggered, this, &YLFriendListView::onAddGroupSlots);
    m_blank_menu = new QMenu();
    m_blank_menu->addAction(action_refresh);
    m_blank_menu->addAction(action_show_all_or_online);
    m_blank_menu->addAction(action_add_group);

    QAction *action_rename = new QAction("重命名");
    QAction *action_delete = new QAction("删除该组");
    m_group_menu = new QMenu();
    m_group_menu->addAction(action_refresh);
    m_group_menu->addAction(action_show_all_or_online);
    m_group_menu->addSeparator();
    m_group_menu->addAction(action_add_group);
    m_group_menu->addAction(action_rename);
    m_group_menu->addAction(action_delete);

}

void YLFriendListView::updateList()
{
    QListWidgetItem *item = new QListWidgetItem("未命名(0/0)");
    item->setSizeHint(QSize(width(), 30));
    addItem(item);
    m_group_item.push_back(item);
    for (auto pair : data_)
    {
        //pair.first 是 组名
        //pai.second 是 该组下好友的数量
    }
}


void YLFriendListView::mousePressEvent(QMouseEvent *event)
{
    QListWidget::mousePressEvent(event);
    if (event->button() == Qt::RightButton)
    {
       m_current_press_item = itemAt(event->pos());
    }
}

void YLFriendListView::contextMenuEvent(QContextMenuEvent *event)
{
    if (m_current_press_item == nullptr)
        m_blank_menu->exec(QCursor::pos());
    else if (qFind(m_group_item, m_current_press_item) != m_group_item.cend())
        m_group_menu->exec(QCursor::pos());
    event->accept();
}

//slots
void YLFriendListView::onAddGroupSlots()
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setText("未命名(0/0)");
    lineEdit->show();
}
