#ifndef YLVALIDATEMESSAGEWIDGET_H
#define YLVALIDATEMESSAGEWIDGET_H
#include "YLBasicWidget/ylbasicwidget.h"
#include "YLEntityObject/yladdrequest.h"
QT_BEGIN_NAMESPACE
class QPushButton;
class QToolButton;
class YLHeadFrame;
QT_END_NAMESPACE

class YLValidateMessageWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLValidateMessageWidget(QWidget *parent = nullptr);

private:
    void initTop();

public slots:

private:
    QPushButton *m_friend_message;
    QPushButton *m_group_message;

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
    void setAddRequest(const YLAddRequest &);
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
};

#endif // YLVALIDATEMESSAGEWIDGET_H
