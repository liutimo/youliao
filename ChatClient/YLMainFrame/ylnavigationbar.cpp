#include "ylnavigationbar.h"
#include <QToolButton>
YLNavigationBar::YLNavigationBar(QWidget *parent) : QWidget(parent)
{
    init();
}

void YLNavigationBar::init()
{
    toolbutton_message_ = new QToolButton(this);
    toolbutton_message_->setText("消息");
    toolbutton_message_->setStyleSheet(qss_no_selected);

    toolbutton_friend_ = new QToolButton(this);
    toolbutton_friend_->setText("好友");
    toolbutton_friend_->setStyleSheet(qss_selected);

    toolbutton_group_ = new QToolButton(this);
    toolbutton_group_->setText("群组");
    toolbutton_group_->setStyleSheet(qss_no_selected);

    connect(toolbutton_message_, &QToolButton::clicked, this, &YLNavigationBar::on_clicked);
    connect(toolbutton_friend_ , &QToolButton::clicked, this, &YLNavigationBar::on_clicked);
    connect(toolbutton_group_  , &QToolButton::clicked, this, &YLNavigationBar::on_clicked);
}


void YLNavigationBar::resizeEvent(QResizeEvent *event)
{
    int w = width();
    int h = height();
    toolbutton_message_->resize(w / 3, h);
    toolbutton_message_->move(0, 0);

    toolbutton_friend_->resize(w / 3, h);
    toolbutton_friend_->move(w / 3, 0);

    toolbutton_group_->resize(w / 3, h);
    toolbutton_group_->move(w / 3 * 2, 0);
}

void YLNavigationBar::on_clicked()
{
    QToolButton *object = static_cast<QToolButton*>(sender());

    int index = 2;

    if (object == toolbutton_message_)
    {
        index = 1;
        toolbutton_message_->setStyleSheet(qss_selected);
        toolbutton_friend_->setStyleSheet(qss_no_selected);
        toolbutton_group_->setStyleSheet(qss_no_selected);
    }
    else if (object == toolbutton_friend_)
    {
        index = 2;
        toolbutton_message_->setStyleSheet(qss_no_selected);
        toolbutton_friend_->setStyleSheet(qss_selected);
        toolbutton_group_->setStyleSheet(qss_no_selected);
    }
    else if (object == toolbutton_group_)
    {
        index = 3;
        toolbutton_message_->setStyleSheet(qss_no_selected);
        toolbutton_friend_->setStyleSheet(qss_no_selected);
        toolbutton_group_->setStyleSheet(qss_selected);
    }
    else
        index = -1;

    emit click_index(index);
}
