#ifndef YLRECENTCHATVIEW_H
#define YLRECENTCHATVIEW_H

#include <QListWidget>
#include "YLEntityObject/ylfriend.h"

class YLFriendListItem;

class YLRecentChatView : public QListWidget
{
    Q_OBJECT
    const QString qss_this = "QListWidget#YLRecentChatView::item:hover    {background: rgba(200, 200, 200, 1.0);}"
                             "QListWidget#YLRecentChatView::item:selected {background: rgba(217, 209, 206, 1.0);}";
public:
    YLRecentChatView(QWidget *parent = nullptr);

    //int 用来表示Rank。代表YLFriend在列表中的位置
    void setData(const QMap<int, YLFriend> &data);

protected:
    void mousePressEvent(QMouseEvent *event);


private slots:
    void on_move_to_top  (const YLFriend &);
    void on_del_from_list(const YLFriend &);
private:
    void updateList();

    QMap<int, YLFriend> data_;


};

#endif // YLRECENTCHATVIEW_H
