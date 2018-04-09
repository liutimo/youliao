#ifndef YLFRIENDLISTVIEW_H
#define YLFRIENDLISTVIEW_H

#include <QListWidget>
#include "YLEntityObject/ylfriend.h"
#include "protobuf/youliao.friendlist.pb.h"
class QMenu;
class QLineEdit;

class YLFriendListView : public QListWidget
{
    Q_OBJECT
    const QString qss_this = "QListWidget{background:rgba(255, 255, 255, 200);}"
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
    YLFriendListView(QWidget *parent = nullptr);
    ~YLFriendListView();

private:
    void initMenu();
    void updateList();
protected:
    void mousePressEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void onAddGroupSlots();
    void updateFriendList(const QMap<int, QVector<YLFriend>> &, const QMap<int, QString>&);


private:
    QMenu       *m_blank_menu;
    QMenu       *m_group_menu;
    QMenu       *m_friend_menu;
    QLineEdit   *m_lineedit;

    const QListWidgetItem *m_current_press_item;

    QVector<QListWidgetItem*> m_group_item;
    QMap<int, QVector<YLFriend>> m_friends;
    QMap<int, QString> m_group;
    QMap<int, bool> m_group_show;
};

#endif // YLFRIENDLISTVIEW_H
