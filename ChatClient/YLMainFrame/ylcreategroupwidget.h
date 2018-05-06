#ifndef YLCREATEGROUPWIDGET_H
#define YLCREATEGROUPWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QRadioButton;
class QButtonGroup;
QT_END_NAMESPACE

class YLCreateGroupWidget : public YLBasicWidget
{
    Q_OBJECT
    const QString qss_radio = " QRadioButton::indicator{width:17px;height:17px;}\
                                QRadioButton::indicator::unchecked{image:url(:/res/YLAddFriendWIdgets/radiobtn_normal.png);}\
                                QRadioButton::indicator:unchecked:hover{image:url(:/res/YLAddFriendWIdgets/radiobtn_highlight.png);}\
                                QRadioButton::indicator:unchecked:pressed{image:url(:/res/YLAddFriendWIdgets/radiobtn_pushed.png);}\
                                QRadioButton::indicator::checked{image:url(:/res/YLAddFriendWIdgets/radiobtn_tick_normal.png);}\
                                QRadioButton::indicator:checked:hover{image:url(:/res/YLAddFriendWIdgets/radiobtn_tick_highlight.png);}\
                                QRadioButton::indicator:checked:pressed{image:url(:/res/YLAddFriendWIdgets/radiobtn_tick_pushed.png);}";

public:
    explicit YLCreateGroupWidget(QWidget *parent = nullptr);

private:
    void init();
    void initLayout();
private slots:
    void enableCustom(int, bool);
private:
    QLabel *m_label_group_name;
    QLabel *m_label_group_count;
    QLabel *m_label_verify;

    QLineEdit *m_lineedit_group_name;
    QRadioButton *m_200;
    QRadioButton *m_500;
    QRadioButton *m_custom;
    QLineEdit *m_lineedit_custom_count;
    QRadioButton *m_all;
    QRadioButton *m_need_verify;
    QRadioButton *m_none_all;
    QButtonGroup *m_group1;

    QPushButton *m_before;
    QPushButton *m_next;


    QWidget *m_widget_1;
    QWidget *m_widget_2;

    QLabel *m_tip;
};

#endif // YLCREATEGROUPWIDGET_H
