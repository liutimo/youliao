#include "ylmainwidget.h"

#include <YLCommonControl/ylheadandstatusframe.h>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
YLMainWidget::YLMainWidget(QWidget *parent) : YLBasicWidget(parent)
{
    resize(400, 800);
    init();
}


void YLMainWidget::init()
{
    min_button_ = new QPushButton(this);
    min_button_->resize(close_button_->size());
    min_button_->setObjectName("min_button_");
    min_button_->setStyleSheet(qss_min_button);

    skin_button_ = new QPushButton(this);
    skin_button_->resize(close_button_->size());
    skin_button_->setObjectName("skin_button_");
    skin_button_->setStyleSheet(qss_skin_button);

    logo_label_ = new QLabel(this);
    logo_label_->setObjectName("logo_label_");
    logo_label_->setStyleSheet(qss_logo_label);
    logo_label_->resize(QSize(21, 24));
    logo_label_->move(8, 8);

    head_status_frame_  = new YLHeadAndStatusFrame(this);
    head_status_frame_->resize(80, 80);
    head_status_frame_->move(25, 50);
}


void YLMainWidget::resizeEvent(QResizeEvent *event)
{
    //因为要使用close_button的位置，此处需要先调用父类的resizeEvent
    YLBasicWidget::resizeEvent(event);
    min_button_->move(close_button_->x() - close_button_->width(), 0);
    skin_button_->move(min_button_->x() - min_button_->width(), 0);
}
