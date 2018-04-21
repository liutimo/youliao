#ifndef YLADDFRIENDWIDGET_H
#define YLADDFRIENDWIDGET_H
#include "YLEntityObject/ylfriend.h"
#include "YLBasicWidget/ylbasicwidget.h"
#include <QVector>

class QLineEdit;
class QRadioButton;
class QTableWidget;
class QLabel;

class YLAddFriendWidget : public YLBasicWidget
{
    Q_OBJECT
    const QString qss_radio = " QRadioButton::indicator{width:17px;height:17px;}\
                                QRadioButton::indicator::unchecked{image:url(:/res/YLAddFriendWIdgets/radiobtn_normal.png);}\
                                QRadioButton::indicator:unchecked:hover{image:url(:/res/YLAddFriendWIdgets/radiobtn_highlight.png);}\
                                QRadioButton::indicator:unchecked:pressed{image:url(:/res/YLAddFriendWIdgets/radiobtn_pushed.png);}\
                                QRadioButton::indicator::checked{image:url(:/res/YLAddFriendWIdgets/radiobtn_tick_normal.png);}\
                                QRadioButton::indicator:checked:hover{image:url(:/res/YLAddFriendWIdgets/radiobtn_tick_highlight.png);}\
                                QRadioButton::indicator:checked:pressed{image:url(:/res/YLAddFriendWIdgets/radiobtn_tick_pushed.png);}";

    const QString qss_table_widget = "QTableWidget{background:rgba(255, 255, 255, 0);}";


public:
    explicit YLAddFriendWidget(QWidget *parent = nullptr);
signals:

private slots:
    void friends(const QVector<YLFriend> &fris);

private:
    void init();
    void init_table_widget();

    void showNoResultTip(bool show = true);

    QLineEdit *m_search_lineedit;
    QPushButton *m_search_button;
    QRadioButton *m_search_by_account;
    QRadioButton *m_search_by_nickname;
    QTableWidget *m_table_widget;

    QLabel *m_label_icon;
    QLabel *m_label_tips;

};

#endif // YLADDFRIENDWIDGET_H
