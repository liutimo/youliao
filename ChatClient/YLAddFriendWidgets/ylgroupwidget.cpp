#include "ylgroupwidget.h"
#include "YLCommonControl/ylheadframe.h"
#include "ylvalidategroupwidget.h"
#include <QLabel>
#include <QPainter>
#include <QPushButton>
YLGroupWidget::YLGroupWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(220, 130);
    init();
}


void YLGroupWidget::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(60, 60);
    m_head_frame->move(5, 5);

    m_group_name = new QLabel("测试群", this);
    m_group_name->setAlignment(Qt::AlignVCenter);
    m_group_name->setFixedHeight(20);
    m_group_name->move(70, 5);

    m_group_member_icon = new QLabel(this);
    m_group_member_icon->setFixedSize(21, 18);
    m_group_member_icon->setPixmap(QPixmap(":/res/YLAddFriendWIdgets/icon_group_selected.png"));
    m_group_member_icon->move(70, 30);

    m_group_member_count = new QLabel("(999/1000)", this);
    m_group_member_count->setFixedHeight(18);
    m_group_member_count->setAlignment(Qt::AlignVCenter);
    m_group_member_count->move(94, 30);

    m_group_intro = new QLabel(this);
    m_group_intro->setWordWrap(true);
    m_group_intro->setText("群介绍");
    m_group_intro->move(5, 65);
    m_group_intro->setFixedSize(200, 30);

    m_add_group = new QPushButton("加群", this);
    m_add_group->setFixedSize(45, 20);
    m_add_group->move(165, 105);
    connect(m_add_group, &QPushButton::clicked, this, [this](){
        YLValidateGroupWidget *w = new YLValidateGroupWidget;
        w->setGroup(m_group);
        w->show();
    });
}


void YLGroupWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, width(), 100);

    painter.setBrush(QColor::fromRgb(230, 230, 230));
    painter.drawRect(0, 100, width(), 30);
}


void YLGroupWidget::setGroup(const YLGroup &group)
{
    m_group = group;
    m_head_frame->setHeadFromUrl(m_group.getGroupImage());
    m_group_name->setText(m_group.getGroupName());
    m_group_member_count->setText(QString("(%1/%2)").arg(m_group.getCount()).arg(m_group.getGroupCapacity()));
}
