#ifndef YLRECENTCHATVIEW_H
#define YLRECENTCHATVIEW_H

#include <QListWidget>
#include "YLEntityObject/ylfriend.h"

class YLFriendListItem;

class YLRecentChatView : public QListWidget
{
    Q_OBJECT
    const QString qss_this = "QListWidget#YLRecentChatView::item:hover {background: rgba(217, 209, 206, 1.0);}";
public:
    YLRecentChatView(QWidget *parent = nullptr);

    //int 用来表示Rank。代表YLFriend在列表中的位置
    void setData(const QMap<int, YLFriend> &data);


private:
    void updateList();

    QMap<int, YLFriend> data_;

    QVector<YLFriendListItem *> vec;
};

#endif // YLRECENTCHATVIEW_H
