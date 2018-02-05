#ifndef YLFRIENDLISTVIEW_H
#define YLFRIENDLISTVIEW_H

#include <QListWidget>
#include "YLEntityObject/ylfriend.h"


class YLFriendListView : public QListWidget
{
    Q_OBJECT
    const QString qss_this = "QListWidget{background:white;color:black;border:none;}"
                             "QListWidget::item{border:none; height: 54px;}"
                             "QListWidget::item:hover{background:rgb(252,240,193);}"
                             "QListWidget::item:selected{background:rgb(252,233,161);color:black;}";
public:
    YLFriendListView(QWidget *parent = nullptr);

    void setData(const QVector<QPair<QString, QVector<YLFriend>>>& data);

private:
    void updateList();

    QVector<QPair<QString, QVector<YLFriend>>> data_;
};

#endif // YLFRIENDLISTVIEW_H
