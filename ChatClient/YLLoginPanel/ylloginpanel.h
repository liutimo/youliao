#ifndef YLLOGINPANEL_H
#define YLLOGINPANEL_H

#include "YLBasicWidget/ylbasicwidget.h"

class YLHeadAndStatusFrame;
class YLAccountListView;
class QLineEdit;
class QPushButton;
class YLLineEdit;
class QCheckBox;

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

    const QString qss_checkbox =      "QCheckBox {spacing: 5px; color: #818888;}\
                                       QCheckBox::indicator                     {width : 17px;height : 17px;}\
                                       QCheckBox::indicator:unchecked           {image: url(:/res/LoginPanel/checkbox_normal.png);}\
                                       QCheckBox::indicator:unchecked:hover     {image: url(:/res/LoginPanel/checkbox_hightlight.png);}\
                                       QCheckBox::indicator:unchecked:pressed   {image: url(:/res/LoginPanel/checkbox_pushed.png);}\
                                       QCheckBox::indicator:checked             {image: url(:/res/LoginPanel/checkbox_tick_normal1.png);}\
                                       QCheckBox::indicator:checked:hover       {image: url(:/res/LoginPanel/checkbox_tick_highlight1.png);}\
                                       QCheckBox::indicator:checked:pressed     {image: url(:/res/LoginPanel/checkbox_tick_pushed1.png);}";

public:
    explicit YLLoginPanel(QWidget *parent = nullptr);

private:
    void init();
    void initCheckBoxs();
    void connectToLoginServer();
private slots:
    void on_login();

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);


private:
//    YLLineEdit           *lineedit_useraccount_;
    QLineEdit            *lineedit_useraccount_;
    QLineEdit            *lineedit_passwd_;
    QPushButton          *pushbutton_login_;
    YLHeadAndStatusFrame *head_frame_;
    YLAccountListView    *account_listview_;

    QCheckBox *m_auto_login;
    QCheckBox *m_remember_pwd;

    std::string m_msgsvr_ip;
    std::string m_msgsvr_port;
    bool   m_connected;
};

#endif // YLLOGINPANEL_H
