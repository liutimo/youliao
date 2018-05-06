#ifndef YLCREATEGROUPWIDGET_H
#define YLCREATEGROUPWIDGET_H
#include <QListWidget>
#include "YLBasicWidget/ylbasicwidget.h"
#include "YLEntityObject/ylfriend.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QRadioButton;
class QButtonGroup;
class YLHeadFrame;
class FriendListWidget;
class SelectedFriendListWidget;
class QHBoxLayout;
class QVBoxLayout;
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
    ~YLCreateGroupWidget();
private:
    void init();
    void initLayout();
    void updateInfo();
private slots:
    void enableCustom(int, bool);
    void addSelectedItem(uint32_t friId);

private:
    //widget1
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

    //widget2
    FriendListWidget *m_friend_list_widget;
    QLineEdit *m_search_line_edit;

    //widget3
    SelectedFriendListWidget *m_selected_friend_list_widget;
    QLabel *m_label_selected;
    QLabel *m_label_selected_count;
    //commom
    QPushButton *m_before;
    QPushButton *m_next;


    QHBoxLayout *h1;
    QHBoxLayout *h2;
    QHBoxLayout *h3;
    QVBoxLayout *v;
    QVBoxLayout *v2;
    QVBoxLayout *v3;
    QHBoxLayout *h4;

    QWidget *m_widget_1;
    QWidget *m_widget_2;
    QWidget *m_widget_3;

    QLabel *m_tip;
};


class FriendListWidget : public QListWidget
{
    Q_OBJECT
    const QString qss_this =   "QListWidget{background:rgba(255, 255, 255, 200);}"
                               "QListWidget::item:hover    {background: rgba(200, 200, 200, 1.0);}"
                               "QListWidget::item:selected {background: rgba(217, 209, 206, 1.0);}";

    const QString qss_scroll_bar = "QScrollBar:vertical {border: 0px solid grey;background: transparent;width: 12px;margin: 12px 0 12px 0;}\
                                    QScrollBar::handle:vertical {border-radius:6px;background:gray;}\
                                    QScrollBar::add-line:vertical {border: 0px ; border-image: url(:/res/MainFrame/scrollbar_arrowdown_normal.png);height: 12px; subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_highlight.png);height: 12px;subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_down.png);height: 12px;subcontrol-position: bottom;ubcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical {border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_normal.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin; }\
                                    QScrollBar::sub-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_highlight.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_down.png);height: 12px;subcontrol-position: top;ubcontrol-origin: margin;}";

public:
    explicit FriendListWidget(QWidget *parent = nullptr);
    ~FriendListWidget();
    void loadFriendList();
private:
    void init();
    void addGroupItem(const QString &groupName, bool isExpand = false);
    void addFriendItem(const YLFriend &fri, bool hide = true);

private:
    QMap<int, bool> m_group_show;
};

class SelectedFriendListWidget : public QListWidget
{
    Q_OBJECT
    const QString qss_this =   "QListWidget{background:rgba(255, 255, 255, 200);}"
                               "QListWidget::item:hover    {background: rgba(200, 200, 200, 1.0);}"
                               "QListWidget::item:selected {background: rgba(217, 209, 206, 1.0);}";

    const QString qss_scroll_bar = "QScrollBar:vertical {border: 0px solid grey;background: transparent;width: 12px;margin: 12px 0 12px 0;}\
                                    QScrollBar::handle:vertical {border-radius:6px;background:gray;}\
                                    QScrollBar::add-line:vertical {border: 0px ; border-image: url(:/res/MainFrame/scrollbar_arrowdown_normal.png);height: 12px; subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_highlight.png);height: 12px;subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_down.png);height: 12px;subcontrol-position: bottom;ubcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical {border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_normal.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin; }\
                                    QScrollBar::sub-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_highlight.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_down.png);height: 12px;subcontrol-position: top;ubcontrol-origin: margin;}";

public:
    explicit SelectedFriendListWidget(QWidget *parent = nullptr);
    ~SelectedFriendListWidget();
    void addSelf();
    void loadSelectedList();
    void addOne(uint32_t friendId, bool first = false);
    void removeOne(uint32_t friendId);

private:
    void init();
    bool isSelected(uint32_t friId);

signals:
    void remove();
private:
    QVector<uint32_t> *m_selected_member;
};

class FriendItem : public QWidget
{
    Q_OBJECT
public:
    explicit FriendItem(QWidget *parent = nullptr);
    void setFriendId(uint32_t friId);
    void setHeadIcon(const QString &path);
    void setFriendInfo(const QString &nickOrRemark, const QString &account);
    void hideDeleteButton();
private:
    void init();

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void selected(uint32_t id);
    void deleted(uint32_t id);
private:
    YLHeadFrame *m_head_frame;
    QLabel *m_label_info;
    QPushButton *m_delete;
    uint32_t m_friend_id;
};

class FriendGroupItem : public QWidget
{
    Q_OBJECT
    const QString qss_add_all = "QPushButton        {border-image:url(:/res/MainFrame/addFriend_btn_normal.png);}\
                                 QPushButton:hover  {border-image:url(:/res/MainFrame/addFriend_btn_hover.png);}\
                                 ";
public:
    explicit FriendGroupItem(QWidget *parent = nullptr);
    void init();
    void setGroupName(const QString &groupName);
    QString getGroupName() const { return m_group_name; }
    void setExpand(bool flag);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void isExpand(bool flag);
private:
    QLabel *m_icon;
    QLabel *m_label_group_name;
    QPushButton *m_add_all;
    bool m_is_expand;
    QString m_group_name;
};

#endif // YLCREATEGROUPWIDGET_H
