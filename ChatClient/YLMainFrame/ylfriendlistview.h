#ifndef YLFRIENDLISTVIEW_H
#define YLFRIENDLISTVIEW_H

#include <QListWidget>
#include "YLEntityObject/ylfriend.h"

class QMenu;
class QLineEdit;

class YLFriendListView : public QListWidget
{
    Q_OBJECT
    const QString qss_this = "QListWidget{background:white;color:black;border:none;}"
                             "QListWidget::item{border:none; height: 54px;}"
                             "QListWidget::item:hover{background:rgb(252,240,193);}"
                             "QListWidget::item:selected{background:rgb(252,233,161);color:black;}";
public:
    YLFriendListView(QWidget *parent = nullptr);
    ~YLFriendListView();
    void setData(const QVector<QPair<QString, QVector<YLFriend>>>& data);

private:
    void initMenu();
    void updateList();

protected:
    void mousePressEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void onAddGroupSlots();



private:
    QMenu       *m_blank_menu;
    QMenu       *m_group_menu;
    QMenu       *m_friend_menu;
    QLineEdit   *m_lineedit;

    const QListWidgetItem *m_current_press_item;

    QVector<QListWidgetItem*> m_group_item;
    QVector<QPair<QString, QVector<YLFriend>>> data_;
};

#endif // YLFRIENDLISTVIEW_H
