#ifndef YLVALIDATEMESSAGEWIDGET_H
#define YLVALIDATEMESSAGEWIDGET_H
#include "YLBasicWidget/ylbasicwidget.h"
#include "YLEntityObject/yladdrequest.h"
QT_BEGIN_NAMESPACE
class QPushButton;
class QToolButton;
class YLHeadFrame;
class QScrollArea;
QT_END_NAMESPACE

class YLValidateMessageWidget : public YLBasicWidget
{
    Q_OBJECT
    const QString qss_selected = "QPushButton{color:white;border:0px;font: 16px solid 黑体;"
                                 "background:qlineargradient(spread:reflect, x1:1, y1:0.977, x2:1, y2:0, "
                                 "stop:0 rgba(218, 235, 249, 255), stop:1 rgba(40, 138, 221, 255));"
                                 "font: 16px solid 黑体;}";

    const QString qss_no_selected = "QPushButton{background:#288ADD;border:0px;color:white;font: 16px solid 黑体;}"
                                    "QPushButton:hover{color:white;border:0px;"
                                    "background:qlineargradient(spread:reflect, x1:1, y1:0.977, x2:1, y2:0, "
                                    "stop:0 rgba(153, 200, 239, 255), "
                                    "stop:1 rgba(40, 138, 221, 255));"
                                    "border:0px;color:white;font: 16px solid 黑体;}";

public:
    explicit YLValidateMessageWidget(QWidget *parent = nullptr);

private:
    void initTop();
    void showFriendWidget();
    void showGroupWidget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPushButton *m_friend_message;
    QPushButton *m_group_message;

    QScrollArea *m_friend_widget;
    QScrollArea *m_group_widget;

    QLabel *m_no_msg;
};

class ValidateInfomationWidget : public QWidget
{
    Q_OBJECT
    const QString qss_close_button = "QPushButton        {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/delbutton_normal.png);}\
                                      QPushButton:hover  {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/delbutton_highlight.png);}\
                                      QPushButton:pressed{border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/delbutton_down.png);}\
                                      ";
    const QString qss_ignore_button =  "QPushButton        {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btn_focus_normal.png);}\
                                        QPushButton:hover  {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btn_focus_highlight.png);}\
                                        QPushButton:pressed{border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btn_focus_down.png);}\
                                        ";
    const QString qss_left_button =    "QPushButton        {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btnleft_normal.png);}\
                                        QPushButton:hover  {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btnleft_highlight.png);}\
                                        QPushButton:pressed{border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btnleft_down.png);}\
                                        ";
    const QString qss_right_button =    "QPushButton        {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btnright_normal.png);}\
                                         QPushButton:hover  {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btnright_highlight.png);}\
                                         QPushButton:pressed{border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btnright_down.png);}\
                                        ";

public:
    explicit ValidateInfomationWidget(QWidget *parent = nullptr);
    ~ValidateInfomationWidget();
    void setAddRequest(const YLAddRequest &, bool isGroup = false);
    void setConfirmed(bool isConfirmed = false);
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    void init();
    void initRight();
    void showRight();
    void hideRight();
    void acceptRequest();
    void refuseRequest();

    YLHeadFrame *m_head_frame;
    QLabel *m_nick;
    QLabel *m_infomation;
    QLabel *m_attach_msg;

    QPushButton *m_close;

    QPushButton *m_left_button;
    QPushButton *m_right_button;
    QPushButton *m_ignore_button;

    QLabel *m_op_text;
    YLAddRequest m_request;
    bool m_is_group;
};

#endif // YLVALIDATEMESSAGEWIDGET_H
