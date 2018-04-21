#ifndef YLFRIENDINFOWIDGET_H
#define YLFRIENDINFOWIDGET_H

#include <QWidget>
#include "protobuf/youliao.base.pb.h"
#include "YLEntityObject/ylfriend.h"

class YLHeadFrame;
class QPushButton;
class QLabel;
class HttpHelper;
class YLFriendInfoWidget : public QWidget
{
    Q_OBJECT
    const QString qss_add_friend = "  QPushButton        {border-image:url(:/res/YLAddFriendWIdgets/addfriend_normal.png);}\
                                      QPushButton:hover  {border-image:url(:/res/YLAddFriendWIdgets/addfriend_hover.png);}\
                                      QPushButton:pressed{border-image:url(:/res/YLAddFriendWIdgets/addfriend_down.png);}\
                                      ";
public:
    explicit YLFriendInfoWidget(QWidget *parent = nullptr);
    void setType(youliao::pdu::base::SearchType type) { m_type = type; }
    void setFriend(const YLFriend &fri);
signals:

public slots:

private:
    void init();

    YLHeadFrame *m_head_frame;
    QPushButton *m_add_friend;
    QLabel *m_friend_info;
    QLabel *m_sex;

    youliao::pdu::base::SearchType m_type;
    YLFriend m_friend;

    HttpHelper *m_http_helper;
};

#endif // YLFRIENDINFOWIDGET_H
