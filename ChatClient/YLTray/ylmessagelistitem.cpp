#include "ylmessagelistitem.h"
#include "YLCommonControl/ylheadframe.h"
#include "ylcounterbubble.h"
#include <QMouseEvent>
#include <QUrl>
#include "signalforward.h"
YLMessageListItem::YLMessageListItem(QWidget *parent) : QWidget(parent)
{
    m_type = FRIEND;
    setFixedSize(300, 45);
    init();
}


void YLMessageListItem::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(35, 35);
    m_head_frame->move(10, 5);

    m_nick_or_remark = new QLabel(this);
    m_nick_or_remark->setMinimumWidth(200);
    m_nick_or_remark->move(50, 10);

    m_counter_bubble = new YLCounterBubble(this);
    m_counter_bubble->move(270, 11);
}

void YLMessageListItem::setName(const QString &name)
{
    m_nick_or_remark->setText(QString("<p style='font: 16px;'>%1</p>").arg(name));
}

void YLMessageListItem::setHeadFrame(const QString &path)
{
    QUrl url(path);
    if (url.isValid())
        m_head_frame->setHeadFromUrl(url);
    else
        m_head_frame->setHeadFromLocal(path);

}

void YLMessageListItem::setCounterNumber(int num)
{
    m_counter_bubble->setNumber(num);
}


void YLMessageListItem::mousePressEvent(QMouseEvent *e)
{

    if (e->button() == Qt::LeftButton)
    {
        if (m_type == GROUP)
            SignalForward::instance()->forwordReadOne(m_group_id, m_type);
        else
            SignalForward::instance()->forwordReadOne(m_sender_id, m_type);
    }
    QWidget::mousePressEvent(e);
}

void YLMessageListItem::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        if (m_type == GROUP)
            SignalForward::instance()->forwordReadOne(m_group_id, m_type);
        else
            SignalForward::instance()->forwordReadOne(m_sender_id, m_type);
    }
    QWidget::mouseDoubleClickEvent(e);
}
