#include "ylfriendlistview.h"
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include "ylfriendlistitem.h"

//network
#include "YLNetWork/pduhandler.h"



YLFriendListView::YLFriendListView(QWidget *parent) : QListWidget(parent),
    m_current_press_item(nullptr)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(qss_this + qss_scroll_bar);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    initMenu();
    connect(this, &YLFriendListView::itemDoubleClicked, this, [this](QListWidgetItem *item){
        if (qFind(m_group_item, item) != m_group_item.cend())
        {
            QString groupName = item->text().split(QRegExp("(\\(\\d/\\d\\))")).at(0);
            int groupId = m_group.key(groupName);
            m_group_show[groupId] = !m_group_show[groupId];
            updateFriendList(m_friends, m_group);
        }

    });

    connect(PduHandler::instance(), &PduHandler::friendlist, this, &YLFriendListView::updateFriendList);
}

YLFriendListView::~YLFriendListView()
{
    delete m_group_menu;
    delete m_blank_menu;
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


void YLFriendListView::updateFriendList(const QMap<int, QVector<YLFriend>> &friends, const QMap<int, QString> &groups)
{
    clear();
    m_group_item.clear();
    m_friends = friends;
    m_group = groups;
    for (auto elem : m_friends)
    {

        int groupId = m_friends.key(elem);
        QString groupName = m_group[groupId];
        auto iter = m_group_show.find(groupId);
        if (iter == m_group_show.end())
            m_group_show[groupId] = false;

        if (m_group_show[groupId] == true)
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/res/MainFrame/down.png"), groupName + QString("(%1/%1)").arg(elem.size()));
            item->setSizeHint(QSize(width() - 30, 35));
            addItem(item);
            m_group_item.push_back(item);
            for (auto fri : elem)
            {
                item = new QListWidgetItem;
                addItem(item);
                item->setSizeHint(QSize(width() - 30, 56));
                YLFriendListItem *item_widget = new YLFriendListItem(YLFriendListItem::FRIENDITEM);
                item_widget->setData(fri);
                setItemWidget(item, item_widget);
            }
        }
        else
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/res/MainFrame/right.png"), groupName + QString("(%1/%1)").arg(elem.size()));
            item->setSizeHint(QSize(width() - 30, 35));
            addItem(item);
            m_group_item.push_back(item);
        }
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
