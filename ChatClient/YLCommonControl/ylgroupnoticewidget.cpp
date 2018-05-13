#include "ylgroupnoticewidget.h"
#include <QLabel>
#include <QListWidget>
YLGroupNoticeWidget::YLGroupNoticeWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(200, 165);
    init();
}

void YLGroupNoticeWidget::init()
{
    m_title = new QLabel("<p style='font:18px;'>群通知</p>", this);
    m_title->setAlignment(Qt::AlignVCenter);
    m_title->setFixedHeight(25);
    m_title->move(10, 0);

    m_list_widget = new QListWidget(this);
    m_list_widget->setFixedSize(200, 140);
    m_list_widget->move(0, 25);
    m_list_widget->setStyleSheet("background-color:transparent");
}
