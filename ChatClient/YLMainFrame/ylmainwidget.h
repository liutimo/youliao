#ifndef YLMAINWIDGET_H
#define YLMAINWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"

class QPushButton;
class QLabel;
class YLHeadAndStatusFrame;

class YLMainWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    YLMainWidget(QWidget *parent = nullptr);

private:
    const QString qss_min_button   = "QPushButton#min_button_        {border-image:url(:/res/MainFrame/sysbtn_min_normal.png);}\
                                      QPushButton#min_button_:hover  {border-image:url(:/res/MainFrame/sysbtn_min_hover.png);}\
                                      QPushButton#min_button_:pressed{border-image:url(:/res/MainFrame/sysbtn_min_down.png);}\
                                      ";

    const QString qss_skin_button   = "QPushButton#skin_button_        {border-image:url(:/res/MainFrame/sysbtn_skin_normal.png);}\
                                       QPushButton#skin_button_:hover  {border-image:url(:/res/MainFrame/sysbtn_Skin_highlight.png);}\
                                       QPushButton#skin_button_:pressed{border-image:url(:/res/MainFrame/sysbtn_Skin_down.png);}\
                                       ";

    const QString qss_logo_label   = "QLabel#logo_label_{border-image:url(:/res/MainFrame/logo.png);}";

    void init();


protected:
    void resizeEvent(QResizeEvent *event);

private:

    //窗口顶部按钮
    QPushButton *min_button_;
    QPushButton *skin_button_;
    QLabel *logo_label_;

    //窗口中上部(账号信息)
    YLHeadAndStatusFrame *head_status_frame_;


};

#endif // YLMAINWIDGET_H
