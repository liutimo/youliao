#include "ylmessagelistitem.h"
#include "YLCommonControl/ylheadframe.h"
#include "ylcounterbubble.h"
#include <QMouseEvent>
#include <QUrl>
#include "signalforward.h"
YLMessageListItem::YLMessageListItem(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300, 45);
    init();
}


void YLMessageListItem::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(35, 35);
    m_head_frame->move(10, 5);

    m_nick_or_remark = new QLabel(this);
    m_nick_or_remark->move(50, 10);

    m_counter_bubble = new YLCounterBubble(this);
    m_counter_bubble->move(270, 11);
}

void YLMessageListItem::setNickOrRemark(const QString &nick)
{
    m_nick_or_remark->setText(QString("<p style='font: 16px;'>%1</p>").arg(nick));
}

void YLMessageListItem::setHeadFrame(const QString &path)
{
    QUrl url(path);
    m_head_frame->setHeadFromLocal(url.fileName());
}

void YLMessageListItem::setCounterNumber(int num)
{
    m_counter_bubble->setNumber(num);
}


void YLMessageListItem::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        SignalForward::instance()->forwordReadOne(m_friend_id);
    }
    QWidget::mousePressEvent(e);
}

void YLMessageListItem::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        SignalForward::instance()->forwordReadOne(m_friend_id);
    }
    QWidget::mouseDoubleClickEvent(e);
}
