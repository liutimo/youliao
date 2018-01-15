#ifndef YLLOGINPANEL_H
#define YLLOGINPANEL_H

#include "YLBasicWidget/ylbasicwidget.h"

class YLHeadAndStatusFrame;
class YLAccountListView;
class QLineEdit;
class QPushButton;
class YLLineEdit;


class YLLoginPanel : public YLBasicWidget
{
    Q_OBJECT

    const QString qss_password_     = "QLineEdit#lineedit_passwd_      {font: 13px;border-image:url(:/res/LoginPanel/edit_frame_normal_passwd.png);}\
                                       QLineEdit#lineedit_passwd_:hover{font: 13px;border-image:url(:/res/LoginPanel/edit_frame_hove_passwd.png);}";

    const QString qss_useraccount_  = "QLineEdit#lineedit_useraccount_      {padding: 0 30 0 0;font: 13px;border-image:url(:/res/LoginPanel/edit_frame_normal_useraccount.png);}\
                                       QLineEdit#lineedit_useraccount_:hover{font: 13px;border-image:url(:/res/LoginPanel/edit_frame_hover_useraccount.png);}";

    const QString qss_login_button_ = "QPushButton#pushbutton_login_        {font: 13px;color:white;border-image:url(:/res/LoginPanel/button_login_normal.png);}\
                                       QPushButton#pushbutton_login_:hover  {font: 13px;color:white;border-image:url(:/res/LoginPanel/button_login_hover.png);}\
                                       QPushButton#pushbutton_login_:pressed{font: 13px;color:white;border-image:url(:/res/LoginPanel/button_login_down.png);}";
public:
    explicit YLLoginPanel(QWidget *parent = nullptr);

private:
    void init();

private slots:
    void on_login();
    void on_account_button_clicked();

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    YLLineEdit           *lineedit_useraccount_;
    QLineEdit            *lineedit_passwd_;
    QPushButton          *pushbutton_login_;
    YLHeadAndStatusFrame *head_frame_;
    YLAccountListView    *account_listview_;
};

#endif // YLLOGINPANEL_H
