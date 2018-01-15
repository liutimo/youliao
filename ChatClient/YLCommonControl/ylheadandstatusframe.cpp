#include "ylheadandstatusframe.h"

#include <QMenu>
#include <QToolButton>

YLHeadAndStatusFrame::YLHeadAndStatusFrame(QWidget *parent) : YLHeadFrame(parent)
{
    init();
}

void YLHeadAndStatusFrame::init()
{

    resize(120, 120);
    status_button_ = new QToolButton(this);
    status_button_->setFixedSize(28, 28);
    status_button_->setObjectName("status_button_");
    setStatusIcon(Online);
    connect(status_button_, &QToolButton::clicked, this, &YLHeadAndStatusFrame::on_status_button_click);

    initMenu();
}


void YLHeadAndStatusFrame::initMenu()
{
    status_menu_ = new QMenu();

    QAction *online     = new QAction(QIcon(":/res/YLCommonControl/imonline.png"),  str_online_);
    QAction *invisible  = new QAction(QIcon(":/res/YLCommonControl/invisible.png"), str_invisible_);
    QAction *offline    = new QAction(QIcon(":/res/YLCommonControl/mute.png"),      str_offline_);

    status_menu_->addAction(online);
    status_menu_->addAction(invisible);
    status_menu_->addAction(offline);
    status_menu_->setStyleSheet(qss_menu_);

    connect(online,    &QAction::triggered, this, &YLHeadAndStatusFrame::on_status_action_changed);
    connect(offline,   &QAction::triggered, this, &YLHeadAndStatusFrame::on_status_action_changed);
    connect(invisible, &QAction::triggered, this, &YLHeadAndStatusFrame::on_status_action_changed);

    //解决当点击菜单但是没有点击Action时，QToolButton一直处于hover状态。
    connect(status_menu_, &QMenu::aboutToHide, this, [this](){
        this->setStatusIcon(status_);
    });

}

void YLHeadAndStatusFrame::setStatusIcon(const Status status)
{
    status_ = status;
    QString path;

    switch (status) {
    case Online:
        path = ":/res/YLCommonControl/imonline.png";
        emit statusChanged(Online);
        break;
    case Offline:
        path = ":/res/YLCommonControl/mute.png";
        emit statusChanged(Offline);
        break;
    case Invisible:
        path = ":/res/YLCommonControl/invisible.png";
        emit statusChanged(Invisible);
        break;
    default:
        path = ":/res/YLCommonControl/imonline.png";
        emit statusChanged(Online);
        break;
    }

    QString qss = QString(qss_status_buttoon).arg(path);

    status_button_->setStyleSheet(qss);
}

void YLHeadAndStatusFrame::on_status_button_click()
{
    status_menu_->exec(mapToGlobal(QPoint(width() - 28, height())));
}

void YLHeadAndStatusFrame::on_status_action_changed()
{
    QAction *action = static_cast<QAction*>(sender());
    QString action_name = action->text();

    if (action_name == str_online_)
    {
        setStatusIcon(Online);
    }
    else if (action_name == str_offline_)
    {
        setStatusIcon(Offline);
    }
    else if (action_name == str_invisible_)
    {
        setStatusIcon(Invisible);
    }
}

void YLHeadAndStatusFrame::resizeEvent(QResizeEvent *e)
{
    status_button_->move(width() - 28, height() - 28);

    YLHeadFrame::resizeEvent(e);
}
