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
    close_button_->setStyleSheet(qss_close_button);
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
    QWidget::mousePressEvent(event);
    if (drag_flag_)

        setCursor(Qt::ClosedHandCursor);

    pressed_flag_ = true;
    begin_pos_    = event->pos();

}

void YLBasicWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);

    if (drag_flag_)
        setCursor(Qt::ArrowCursor);

    pressed_flag_ = false;

}

void YLBasicWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    if (drag_flag_ && pressed_flag_)
    {
        QPoint curPos(QCursor::pos() - begin_pos_);
        move(curPos);
    }
}
void YLBasicWidget::on_close()
{
    close();
}
