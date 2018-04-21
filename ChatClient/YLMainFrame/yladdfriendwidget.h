#ifndef YLADDFRIENDWIDGET_H
#define YLADDFRIENDWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"

class QLineEdit;
class QRadioButton;

class YLAddFriendWidget : public YLBasicWidget
{
    Q_OBJECT
    const QString qss_radio = " QRadioButton::indicator{width:17px;height:17px;}\
                                QRadioButton::indicator::unchecked{image:url(:/res/MainFrame/radiobtn_normal.png);}\
                                QRadioButton::indicator:unchecked:hover{image:url(:/res/MainFrame/radiobtn_highlight.png);}\
                                QRadioButton::indicator:unchecked:pressed{image:url(:/res/MainFrame/radiobtn_pushed.png);}\
                                QRadioButton::indicator::checked{image:url(:/res/MainFrame/radiobtn_tick_normal.png);}\
                                QRadioButton::indicator:checked:hover{image:url(:/res/MainFrame/radiobtn_tick_highlight.png);}\
                                QRadioButton::indicator:checked:pressed{image:url(:/res/MainFrame/radiobtn_tick_pushed.png);}";
public:
    explicit YLAddFriendWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    void init();

    QLineEdit *m_search_lineedit;
    QPushButton *m_search_button;
    QRadioButton *m_search_by_account;
    QRadioButton *m_search_by_nickname;
};

#endif // YLADDFRIENDWIDGET_H
