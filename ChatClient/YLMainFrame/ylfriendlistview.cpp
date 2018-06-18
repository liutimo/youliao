#include "ylfriendlistview.h"
#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include "yllistitem.h"
#include "ylmainwidget.h"
#include "globaldata.h"
#include "YLCommonControl/ylmessagebox.h"
//network
#include "YLNetWork/pduhandler.h"
#include "YLNetWork/ylbusiness.h"


YLFriendListView::YLFriendListView(QWidget *parent) : QListWidget(parent),
    m_current_press_item(nullptr), m_online(false), m_flag(false), m_type(0)
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
            QString groupName = item->text().split(QRegExp("(\\(\\d+/\\d+\\))")).at(0);
            int groupId = m_group.key(groupName);
            m_group_show[groupId] = !m_group_show[groupId];
            updateList();
        }

    });

    connect(PduHandler::instance(), &PduHandler::friendgroups, this, [this](const QMap<int, QString> &groups){
       m_group = groups;
       GlobalData::setGroup(m_group);
    });
    connect(PduHandler::instance(), &PduHandler::friendlist, this, &YLFriendListView::updateFriendList);
    connect(PduHandler::instance(), &PduHandler::addFriendSuccess, this, &YLFriendListView::refreshFriendList);
    connect(PduHandler::instance(), &PduHandler::friendStatusChange, this, &YLFriendListView::friendStatusChanged);
    connect(PduHandler::instance(), &PduHandler::friendSignatureChange, this, &YLFriendListView::friendSignatureChanged);
    connect(PduHandler::instance(), &PduHandler::friendGroup, this, [this](uint32_t groupId, const QString &groupName)
    {
        m_group[groupId] = groupName;
        GlobalData::setGroup(m_group);
    });
    connect(PduHandler::instance(), &PduHandler::deleteFriend, this, &YLFriendListView::deleteFriend);
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

    action_rename = new QAction("重命名");
    QAction *action_delete = new QAction("删除该组");
    m_group_menu = new QMenu();
    m_group_menu->addAction(action_refresh);
    m_group_menu->addAction(action_show_all_or_online);
    m_group_menu->addSeparator();
    m_group_menu->addAction(action_add_group);
    m_group_menu->addAction(action_rename);
    m_group_menu->addAction(action_delete);


    connect(action_rename, &QAction::triggered, this, &YLFriendListView::renameGroup);
    connect(action_delete, &QAction::triggered, this, &YLFriendListView::deleteGroup);
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
                YLListItem *item_widget = new YLListItem(YLListItem::FRIENDITEM);
                connect(item_widget, &YLListItem::moveFriendToGroup, this, &YLFriendListView::moveFriendToGroup);
                connect(item_widget, &YLListItem::modifyRemark, this, &YLFriendListView::modifyRemark);
                connect(item_widget, &YLListItem::deleteFriend, this, &YLFriendListView::deleteFriend);

                fri.setFriendGroup(elem);
                item_widget->setData(fri);
                item_widget->setSecondMenu(m_group, elem);
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
    {
        QString name = m_current_press_item->text().split(QRegExp("(\\(\\d/\\d\\))")).at(0);
        if (name == "我的好友")
            action_rename->setEnabled(false);
        m_group_menu->exec(QCursor::pos());
    }
    event->accept();
}



//slots
void YLFriendListView::updateFriendList(const QMap<int, QVector<YLFriend>> &friends)
{
    m_friends = friends;
    GlobalData::setFriends(m_friends);
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

    GlobalData::setFriends(m_friends);

    emit updateSessions();
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

    m_type = 1;
    m_flag = true;
}

void YLFriendListView::renameGroup()
{
    QRect r = visualItemRect(m_current_press_item);
    QString oldName = m_current_press_item->text().split(QRegExp("(\\(\\d/\\d\\))")).at(0);
    m_lineedit->setText(oldName);
    m_lineedit->setGeometry(r.left() + 20,r.top() + 1, r.width() - 30, r.height() - 2);//出现的位置
    m_lineedit->show();
    m_lineedit->setFocus();
    m_lineedit->selectAll();

    m_group_id = m_group.key(oldName);
    m_type = 2;
    m_flag = true;
}


void YLFriendListView::deleteGroup()
{
    QString groupName = m_current_press_item->text().split(QRegExp("(\\(\\d/\\d\\))")).at(0);
    m_group_id = m_group.key(groupName);
    m_group.remove(m_group_id);
    m_friends[1].append(m_friends[m_group_id]);
    m_friends.remove(m_group_id);
    updateList();
    GlobalData::setGroup(m_group);
    YLBusiness::deleteFriendGroup(GlobalData::getCurrLoginUserId(), m_group_id);
}

void YLFriendListView::editFinshed()
{
    if(!m_flag)
        return;
    m_flag = false;

    m_lineedit->hide();
    QString newName = m_lineedit->text();

    for (auto elem : m_group)
    {
        if(elem == newName)
        {
            YLMessageBox *messageBox = new YLMessageBox(BUTTON_OK, parentWidget());
            messageBox->setWidgetTitle("Error");
            messageBox->setToolTip("this group is exist!");
            auto p = YLMainWidget::center;
            messageBox->move(mapToGlobal(p) - mapToGlobal(messageBox->rect().center()));
            messageBox->exec();
            updateList();
            return;
        }
    }

    if (m_type == 1)
    {
        m_current_edit_item->setText(newName + "(0/0)");
        YLBusiness::addNewFriendGroup(GlobalData::getCurrLoginUserId(), newName);
    }
    else if (m_type == 2)
    {
        m_group[m_group_id] = newName;
        updateList();
        YLBusiness::renameFriendGroup(GlobalData::getCurrLoginUserId(), m_group_id, newName);
    }

    GlobalData::setGroup(m_group);
}

void YLFriendListView::moveFriendToGroup(uint32_t friendId, uint32_t oldGroupId, uint32_t newGroupId)
{
    YLBusiness::moveFriendToGroup(GlobalData::getCurrLoginUserId(), friendId, newGroupId);

    QVector<YLFriend> &vec = m_friends[oldGroupId];

    for (auto iter = vec.begin(); iter != vec.end(); ++iter)
    {
        if (iter->friendId() == friendId)
        {
            m_friends[newGroupId].push_back(*iter);
            vec.erase(iter);
            break;
        }
    }

    updateList();
}

void YLFriendListView::deleteFriend(uint32_t friendId)
{
    YLBusiness::deleteFriend(GlobalData::getCurrLoginUserId(), friendId);

    for (auto &vec : m_friends)
    {
        for (auto iter = vec.begin(); iter != vec.end(); ++iter)
        {
            if (iter->friendId() == friendId)
            {
                vec.erase(iter);
                updateList();
                break;
            }
        }
    }

    auto &m_top_sessions    = GlobalData::getTopSessions();
    auto &m_sessions        = GlobalData::getSessions();

    for (auto iter = m_top_sessions.begin(); iter != m_top_sessions.end(); ++iter)
    {
        if (iter->getOtherId() == friendId && iter->getSessionType() == base::SESSION_TYPE_SINGLE)
        {
            m_top_sessions.erase(iter);
            break;
        }
    }

    for (auto iter = m_sessions.begin(); iter != m_sessions.end(); ++iter)
    {
        if (iter->getOtherId() == friendId && iter->getSessionType() == base::SESSION_TYPE_SINGLE)
        {
            m_sessions.erase(iter);
            break;
        }
    }

    emit updateSessions();
}

void YLFriendListView::modifyRemark(uint32_t friendId, const QString &newRemark)
{
    YLBusiness::modifyFriendRemark(GlobalData::getCurrLoginUserId(), friendId, newRemark);

    for (auto &vec : m_friends)
    {
        for (auto iter = vec.begin(); iter != vec.end(); ++iter)
        {
            if (iter->friendId() == friendId)
            {
                iter->setFriendRemark(newRemark);
                updateList();
                return;
            }
        }
    }

}
