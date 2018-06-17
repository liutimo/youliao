#include "ylbasicwidget.h"

#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>

YLBasicWidget::YLBasicWidget(QWidget *parent) : QWidget(parent), drag_flag_(true), pressed_flag_(false)
{
//    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint);
    init();
    m_has_icon = false;
}

void YLBasicWidget::init()
{

    close_button_ = new QPushButton(this);
    close_button_->setFixedSize(32, 32);
    close_button_->move(width() - 32, 0);
    close_button_->setObjectName("close_button_");
    close_button_->setStyleSheet(qss_close_button);
    close_button_->setTabletTracking(true);
    connect(close_button_, &QPushButton::clicked, this, &YLBasicWidget::on_close);

    m_widget_icon = new QLabel(this);
    m_widget_icon->setFixedSize(14, 16);
    m_widget_icon->move(5, 9);

    m_title_label = new QLabel(this);
    m_title_label->setStyleSheet("font:13px; color:white");
    m_title_label->setFixedHeight(22);
    m_title_label->move(24, 5);
}

void YLBasicWidget::setWidgetDraged(bool flag)
{
    drag_flag_ = flag;
}

void YLBasicWidget::setWidgetTitle(const QString &title)
{
    m_title_label->setText(title);
}



void YLBasicWidget::setWidgetIcon(const QString fileName)
{
    m_has_icon = true;
    m_widget_icon->setPixmap(QPixmap(fileName).scaled(QSize(17, 20), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void YLBasicWidget::resizeEvent(QResizeEvent *event)
{
    close_button_->move(width() - 32, 0);
    if (!m_has_icon)
    {
        m_title_label->move(5, 5);
    }
    else
    {
        m_widget_icon->move(5, 9);
        m_title_label->move(24, 5);
    }
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

