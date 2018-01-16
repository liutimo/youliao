#include "ylbasicwidget.h"

#include <QPushButton>
#include <QMouseEvent>

YLBasicWidget::YLBasicWidget(QWidget *parent) : QWidget(parent), drag_flag_(true), pressed_flag_(false)
{
    init();
}

void YLBasicWidget::init()
{
    setWindowFlags(Qt::FramelessWindowHint);

    close_button_ = new QPushButton(this);
    close_button_->setFixedSize(32, 32);
    close_button_->move(width() - 32, 0);
    close_button_->setObjectName("close_button_");
    close_button_->setStyleSheet(qss_clost_button);
    close_button_->setTabletTracking(true);

    connect(close_button_, &QPushButton::clicked, this, &YLBasicWidget::on_close);
}

void YLBasicWidget::setWidgetDraged(bool flag)
{
    drag_flag_ = flag;
}

void YLBasicWidget::resizeEvent(QResizeEvent *event)
{
    close_button_->move(width() - 32, 0);

    QWidget::resizeEvent(event);
}

void YLBasicWidget::mousePressEvent(QMouseEvent *event)
{

    if (drag_flag_)

        setCursor(Qt::ClosedHandCursor);

    pressed_flag_ = true;
    begin_pos_    = event->pos();

    QWidget::mousePressEvent(event);
}

void YLBasicWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (drag_flag_)
        setCursor(Qt::ArrowCursor);

    pressed_flag_ = false;

    QWidget::mouseReleaseEvent(event);
}

void YLBasicWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (drag_flag_ && pressed_flag_)
    {
        QPoint curPos(QCursor::pos() - begin_pos_);
        move(curPos);
    }

    QWidget::mouseMoveEvent(event);
}
void YLBasicWidget::on_close()
{
    close();
}
