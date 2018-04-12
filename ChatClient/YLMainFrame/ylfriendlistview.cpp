#include "ylfriendlistview.h"
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include "ylfriendlistitem.h"
#include "globaldata.h"
//network
#include "YLNetWork/pduhandler.h"
#include "YLNetWork/ylbusiness.h"


YLFriendListView::YLFriendListView(QWidget *parent) : QListWidget(parent),
    m_current_press_item(nullptr), m_online(false)
{
    setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet(qss_this + qss_scroll_bar);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);


    m_lineedit = new QLineEdit(this);
    m_lineedit->hide();
    connect(m_lineedit, &QLineEdit::editingFinished, this, &YLFriendListView::editFinshed);

    initMenu();
    connect(this, &YLFriendListView::itemDoubleClicked, this, [this](QListWidgetItem *item){
        if (qFind(m_group_item, item) != m_group_item.cend())
        {
            QString groupName = item->text().split(QRegExp("(\\(\\d/\\d\\))")).at(0);
            int groupId = m_group.key(groupName);
            m_group_show[groupId] = !m_group_show[groupId];
            updateList();
        }

    });

    connect(PduHandler::instance(), &PduHandler::friendgroups, this, [this](const QMap<int, QString> &groups){
       m_group = groups;
    });
    connect(PduHandler::instance(), &PduHandler::friendlist, this, &YLFriendListView::updateFriendList);
    connect(PduHandler::instance(), &PduHandler::friendStatusChange, this, &YLFriendListView::friendStatusChanged);
    connect(PduHandler::instance(), &PduHandler::friendSignatureChange, this, &YLFriendListView::friendSignatureChanged);
}

YLFriendListView::~YLFriendListView()
{
    delete m_group_menu;
    delete m_blank_menu;
}


void YLFriendListView::initMenu()
{
    QAction *action_refresh             = new QAction("刷新好友列表");
    QAction *action_show_all_or_online  = new QAction("显示在线好友");
    QAction *action_add_group           = new QAction("添加分组");
    m_blank_menu = new QMenu();
    m_blank_menu->addAction(action_refresh);
    m_blank_menu->addAction(action_show_all_or_online);
    m_blank_menu->addAction(action_add_group);

    connect(action_refresh, &QAction::triggered, this, &YLFriendListView::refreshFriendList);
    connect(action_show_all_or_online, &QAction::triggered, this, &YLFriendListView::showFriendsModel);
    connect(action_add_group, &QAction::triggered, this, &YLFriendListView::addGroup);

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
    m_group_item.clear();
    clear();
    //sort by online status
    QMap<int, QPair<int, int>> online_users;
    for (auto& elem : m_friends)
    {
        int groupId = m_friends.key(elem);
        online_users[groupId].first = elem.size();

        qSort(elem.begin(), elem.end());

        for (YLFriend fri : elem)
        {
            if (fri.friendIsOnline())
                ++online_users[groupId].second;
        }
    }

    for (auto elem : m_group)
    {
        int groupId = m_group.key(elem);
        auto pair = online_users[groupId];

        if (m_group_show[groupId] == true)
        {
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/res/MainFrame/down.png"), elem + QString("(%1/%2)").arg(pair.second).arg(pair.first));
            item->setSizeHint(QSize(width() - 30, 35));
            addItem(item);
            m_group_item.push_back(item);


            for (YLFriend fri : m_friends[groupId])
            {
                if (m_online && !fri.friendIsOnline())
                    continue;

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
            QListWidgetItem *item = new QListWidgetItem(QIcon(":/res/MainFrame/right.png"), elem + QString("(%1/%2)").arg(pair.second).arg(pair.first));
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
void YLFriendListView::updateFriendList(const QMap<int, QVector<YLFriend>> &friends)
{
    m_friends = friends;
    updateList();
}

void YLFriendListView::friendStatusChanged(uint32_t friendId, uint32_t status)
{
    for (auto &groupFriend : m_friends)
    {
        for (int i = 0; i < groupFriend.size(); ++i)
        {
            auto &fri = groupFriend[i];
            if (fri.friendId() == friendId)
            {
                fri.setFriendOnline(status == 1);
            }
        }
    }
    updateList();
}


void YLFriendListView::friendSignatureChanged(uint32_t friendId, const QString &signature)
{
    for (auto &groupFriend : m_friends)
    {
        for (int i = 0; i < groupFriend.size(); ++i)
        {
            auto &fri = groupFriend[i];
            if (fri.friendId() == friendId)
            {
                fri.setFriendSigature(signature);
            }
        }
    }
    updateList();
}

void YLFriendListView::refreshFriendList()
{
    YLBusiness::getFriendGroupsRequest(GlobalData::getCurrLoginUserId());
    YLBusiness::getFriendListRequest(GlobalData::getCurrLoginUserId());
}

void YLFriendListView::showFriendsModel()
{
    QAction *pSender = static_cast<QAction*>(sender());

    if (pSender->text() == "显示在线好友")
    {
        pSender->setText("显示全部联系人");
        m_online = true;
        updateList();
    }
    else
    {
        pSender->setText("显示在线好友");
        m_online = false;
        updateList();
    }
}

void YLFriendListView::addGroup()
{
    QListWidgetItem *newItem = new QListWidgetItem(QIcon(":/res/MainFrame/right.png"), "未命名(0/0)");
    newItem->setSizeHint(QSize(width() - 30, 35));
    addItem(newItem);
    m_group_item.push_back(newItem);
    m_current_edit_item = newItem;

    QRect r = visualItemRect(newItem);
    m_lineedit->setText("未命名");
    m_lineedit->setGeometry(r.left() + 20,r.top() + 1, r.width() - 30, r.height() - 2);//出现的位置
    m_lineedit->show();
    m_lineedit->setFocus();
    m_lineedit->selectAll();
}

void YLFriendListView::renameGroup()
{



}

void YLFriendListView::editFinshed()
{
    m_lineedit->hide();
//    m_current_edit_item->setText(m_lineedit->text() + "(0/0)");
//    m_group[m_group.size() + 1] = m_lineedit->text() + "(0/0)";
    int i = 0;
    updateList();
}
