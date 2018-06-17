#include "ylgrouplistview.h"
#include "yllistitem.h"
#include "ylcreategroupwidget.h"
#include "YLCommonControl/ylheadframe.h"
#include "ylgroupinfowidget.h"
#include "YLNetWork/ylbusiness.h"
#include "YLNetWork/pduhandler.h"
#include "YLChatWidget/ylgroupchatwidget.h"
#include "globaldata.h"
#include <QMouseEvent>
#include <QScrollBar>
#include <QDebug>
#include <QMenu>
#include <QLabel>
#include "YLCommonControl/ylmessagebox.h"
YLGroupListView::YLGroupListView(QWidget *parent) : QListWidget(parent)
{
    setObjectName("YLGroupListView");
    setStyleSheet(qss_this + qss_scroll_bar);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::NoFocus);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    initMenu();
    connect(PduHandler::instance(), &PduHandler::newGroup, this, &YLGroupListView::addGroupItem);
    connect(PduHandler::instance(), &PduHandler::groupList, this, &YLGroupListView::updateList);
    connect(PduHandler::instance(), &PduHandler::exitGroupResult, this, &YLGroupListView::exitGroupResult);
}

void YLGroupListView::initMenu()
{
    m_menu = new QMenu(this);

    QAction *action_create = new QAction("创建群组", this);
    m_menu->addAction(action_create);
    connect(action_create, &QAction::triggered, this, [this](){
        YLCreateGroupWidget *w = new YLCreateGroupWidget;
        connect(w, &YLCreateGroupWidget::createComplete, this, &YLGroupListView::createGroupComplete);
        w->show();
    });
}


void YLGroupListView::addGroupItem(const YLGroup &group)
{
    YLGroupListItem *w = new YLGroupListItem;
    w->setGroup(group);

    QListWidgetItem *item = new QListWidgetItem;
    addItem(item);
    item->setSizeHint(QSize(width() - 30, 56));
    setItemWidget(item, w);
}

void YLGroupListView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        m_menu->exec(mapToGlobal(event->pos()));
    }
    QListWidget::mousePressEvent(event);
}


void YLGroupListView::createGroupComplete(const QString &groupName)
{
}


void YLGroupListView::updateList()
{
    clear();
    auto groups = GlobalData::getGroups();
    for (auto group : groups)
    {
        addGroupItem(group);
    }

    //请求session列表
    YLBusiness::getSessions(GlobalData::getCurrLoginUserId());
}

void YLGroupListView::exitGroupResult(uint32_t groupId, uint32_t resultCode)
{

    YLGroup group = GlobalData::getGroupByGroupId(groupId);


    YLMessageBox *m = new YLMessageBox(BUTTON_OK, this);
    m->setWidgetTitle("提示");
    m->setIcon(":/res/MessageBox/sysmessagebox_inforFile.png");
    if (resultCode == 0)
    {
        GlobalData::remGroupByGroupId(groupId);
        m->setToolTip(QString("你已成功退出群:%1(%2)。").arg(group.getGroupName()).arg(group.getGroupId()));
    }
    else
        m->setToolTip(QString("退出群组失败!!!"));

    m->show();
    m->exec();

    updateList();
}

/****************************************************/

YLGroupListItem::YLGroupListItem(QWidget *parent) : QWidget(parent)
{
    init();
    initMenu();
}


void YLGroupListItem::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->resize(40, 40);

    m_group_name = new QLabel(this);
    m_group_name->setFixedHeight(40);
    m_group_name->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void YLGroupListItem::initMenu()
{
    m_menu = new QMenu(this);

    QAction *action_send_msg = new QAction("发送群消息", this);
    QAction *action_cat_info = new QAction("查看群资料", this);
    QAction *action_msg_record = new QAction("查看消息记录", this);
    QAction *action_exit_group = new QAction("退出该群", this);

    m_menu->addAction(action_send_msg);
    m_menu->addAction(action_cat_info);
    m_menu->addAction(action_msg_record);
    m_menu->addAction(action_exit_group);

    connect(action_send_msg, &QAction::triggered, this, [this](){
        YLGroupChatWidget *w = new YLGroupChatWidget;
        w->setGroup(m_group);
        GlobalData::addGroupChatWidget(m_group.getGroupId(), w);
        w->show();
    });

    connect(action_cat_info, &QAction::triggered, this, [this]()
    {
        YLGroupInfoWidget *w = new YLGroupInfoWidget;
        w->setGroup(m_group);
        w->show();
    });

    connect(action_exit_group, &QAction::triggered, this, [this](){

        YLMessageBox *m = new YLMessageBox(BUTTON_OK | BUTTON_CANNEL, this);
        m->setWidgetTitle("提示");
        m->setIcon(":/res/MessageBox/sysmessagebox_inforFile.png");
        m->setToolTip("你真的要退出该群吗？(退群通知仅群管理员可见)");
        m->show();
        BottonResult br =  m->exec();

        if (br == BUTTON_OK)
            YLBusiness::exitGroup(m_group.getGroupId());
    });

}

void YLGroupListItem::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        m_menu->exec(mapToGlobal(event->pos()));
        event->accept();
    }
    else
        QWidget::mousePressEvent(event);
}


void YLGroupListItem::resizeEvent(QResizeEvent *event)
{
     m_head_frame->move(5, (height() - m_head_frame->height()) / 2);
     m_group_name->move(10 + m_head_frame->width(), (height() - m_head_frame->height()) / 2);
     QWidget::resizeEvent(event);
}


void YLGroupListItem::setGroup(const YLGroup &group)
{
    m_group = group;
    m_head_frame->setHeadFromUrl(m_group.getGroupImage());
    m_group_name->setText(m_group.getGroupName());
}

