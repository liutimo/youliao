#ifndef YLHEADANDSTATUSFRAME_H
#define YLHEADANDSTATUSFRAME_H

/*
 * 在YLHeadFrame的基础上，增加了一个在线状态选择，用于登录界面和主界面头像显示
 */

#include "ylheadframe.h"

class YLHeadAndStatusFrame : public YLHeadFrame
{
    Q_OBJECT

    const QString str_online_        = "在线";
    const QString str_offline_       = "离线";
    const QString str_invisible_     = "隐身";
    const QString qss_menu_          = "QMenu {background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0, stop: 0 #EEEEEE, stop:0.25 #EEEEEE, stop:0.251 white,stop: 1 white);margin: 2px;}\
                                        QMenu::item {padding: 2px 30px 2px 20px;border: 1px solid transparent; }\
                                        QMenu::item:selected {background: rgba(100, 100, 100, 150);}";

    const QString qss_status_buttoon = "QToolButton#status_button_{border:0px;background-image:url(%1);}\
                                        QToolButton#status_button_:hover{border:0px;background-color:rgba(200, 200, 230, 125);background-image:url(%1);}";


public:
    typedef enum status{Online, Offline, Invisible}Status;
    YLHeadAndStatusFrame(QWidget *parent = nullptr);

private:
    void on_status_button_click();
    void on_status_action_changed();

    void init();
    void initMenu();
    void setStatusIcon(const Status status);

protected:
    void resizeEvent(QResizeEvent *e);
signals:
    void statusChanged(Status status);
private:
    Status status_;
    QMenu *status_menu_;
    QToolButton *status_button_;
};

#endif // YLHEADANDSTATUSFRAME_H
