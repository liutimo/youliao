#ifndef YLMAINWIDGET_H
#define YLMAINWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"
#include "protobuf/youliao.base.pb.h"
class QPushButton;
class YLSearchLineEdit;
class QLabel;
class YLSignatureLineEdit;
class YLHeadAndStatusFrame;
class YLNavigationBar;
class QTimer;

using namespace youliao::pdu::base;
class YLMainWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLMainWidget(QWidget *parent = nullptr);

    void setUserInfo(UserInfo *);

    static QPoint center;

private:
    const QString qss_min_button     = "QPushButton#min_button_        {border-image:url(:/res/MainFrame/sysbtn_min_normal.png);}\
                                        QPushButton#min_button_:hover  {border-image:url(:/res/MainFrame/sysbtn_min_hover.png);}\
                                        QPushButton#min_button_:pressed{border-image:url(:/res/MainFrame/sysbtn_min_down.png);}\
                                       ";

    const QString qss_skin_button    = "QPushButton#skin_button_        {border-image:url(:/res/MainFrame/sysbtn_skin_normal.png);}\
                                        QPushButton#skin_button_:hover  {border-image:url(:/res/MainFrame/sysbtn_Skin_highlight.png);}\
                                        QPushButton#skin_button_:pressed{border-image:url(:/res/MainFrame/sysbtn_Skin_down.png);}\
                                        ";

    const QString qss_logo_label     = "QLabel#logo_label_{border-image:url(:/res/MainFrame/logo.png);}";


    const QString qss_nickname_label = "QLabel#nickname_label_{color:white; font:32px sold Sans-serif;}";


    void init();

    void initListWidget();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    //窗口顶部按钮
    QPushButton *min_button_;
    QPushButton *skin_button_;
    QLabel      *logo_label_;

    //窗口中上部(账号信息)
    YLHeadAndStatusFrame *head_status_frame_;
    QLabel               *nickname_label_;
    YLSignatureLineEdit  *signature_lineedit_;

    //搜索框
    YLSearchLineEdit *search_lineedit_;

    //导航栏
    YLNavigationBar *navigation_bar_;

    //子窗口
    QVector<QWidget *> vec;
};

#endif // YLMAINWIDGET_H
