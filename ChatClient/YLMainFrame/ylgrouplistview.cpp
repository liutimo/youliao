#include "ylgrouplistview.h"
#include "yllistitem.h"
#include "ylcreategroupwidget.h"
#include "globaldata.h"
#include <QMouseEvent>
#include <QScrollBar>
#include <QDebug>
#include <QMenu>

YLGroupListView::YLGroupListView(QWidget *parent) : QListWidget(parent)
{
    setObjectName("YLGroupListView");
    setStyleSheet(qss_this + qss_scroll_bar);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::NoFocus);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    initMenu();
}

void YLGroupListView::initMenu()
{
    m_menu = new QMenu(this);

    QAction *action_create = new QAction("创建群组", this);
    m_menu->addAction(action_create);
    connect(action_create, &QAction::triggered, this, [](){
        YLCreateGroupWidget *w = new YLCreateGroupWidget;
        w->show();
    });
}


void YLGroupListView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        m_menu->exec(mapToGlobal(event->pos()));
    }
    QListWidget::mousePressEvent(event);
}
