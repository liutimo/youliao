#ifndef YLFRIENDLISTITEM_H
#define YLFRIENDLISTITEM_H

#include <QWidget>

#include "YLEntityObject/ylfriend.h"
#include "YLEntityObject/ylsession.h"
class YLHeadFrame;
class QLabel;
class HttpHelper;
class QMenu;
class YLFriendListItem : public QWidget
{
    Q_OBJECT
public:
    typedef enum {RECENTTLYCHATITEM, FRIENDITEM} YLListItemType;


    explicit YLFriendListItem(YLListItemType type = FRIENDITEM,  QWidget *parent = nullptr);

    //set second menu
    void setSecondMenu(const QMap<int, QString> &groups, const QString &currGroupName);

    void setData(const YLFriend &f, const YLSession &session = YLSession());

    YLFriend getData() { return friend_;}
    void setMarkTop(bool flag = false);
private:
    //用于显示备注信息或者昵称
    const QString placeholder_text_1   =  "<span style=\"color:black;font:14px solid 黑体\">%1</span><span style=\"color:gray;font:14px solid 黑体\">(%2)</span>";
    //在最近聊天时显示好友昵称。
    const QString placeholder_text_1_1 =  "<span style=\"color:black;font:14px solid 黑体\">%1</span>";
    //用于显示个性签名或者最近一条聊天记录
    const QString placeholder_text_2   = "<span style=\"color:gray;font:12px solid 黑体\">%1</span>";
    //显示时间
    const QString placeholder_text_3   = "<span style=\"color:gray;font:12px solid 黑体\">%1</span>";

    void init();

    void initMenu();

protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);




signals:
    void moveToTop(YLSession &);
    void deleteFromList(const YLSession &);
    void moveFriendToGroup(uint32_t friendId, uint32_t oldGroupId, uint32_t newGroupId);
    void deleteFriend(uint32_t friendId);
    void modifyRemark(uint32_t friendId, const QString &newRemark);

private:
    YLHeadFrame *head_frame_;

    //up和down1表示相对位置
    QLabel      *label_up_;         //如果由备注则显示备注信息，否则显示昵称
    QLabel      *label_down_;       //显示个性签名 或者最后一条聊天记录
    QLabel      *label_time_;       //显示最后一次聊天的时间
    QMenu       *menu_;
    QMenu       *second_menu_;
    QAction     *action_on_top;
    YLListItemType item_type_;      //保存当前item的类型
    YLFriend friend_;
    YLSession session_;
    HttpHelper *m_http_helper;
};

#endif // YLFRIENDLISTITEM_H
