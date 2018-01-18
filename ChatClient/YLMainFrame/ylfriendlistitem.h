#ifndef YLFRIENDLISTITEM_H
#define YLFRIENDLISTITEM_H

#include <QWidget>

class YLFriend;
class YLHeadFrame;
class QLabel;

class YLFriendListItem : public QWidget
{
    Q_OBJECT
public:
    typedef enum {RECENTTLYCHATITEM, FRIENDITEM} YLListItemType;


    explicit YLFriendListItem(YLListItemType type = FRIENDITEM,  QWidget *parent = nullptr);

    void setData(const YLFriend &f);
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

protected:
    void resizeEvent(QResizeEvent *event);

signals:

public slots:

private:
    YLHeadFrame *head_frame_;

    //up和down1表示相对位置
    QLabel      *label_up_;         //如果由备注则显示备注信息，否则显示昵称
    QLabel      *label_down_;       //显示个性签名 或者最后一条聊天记录
    QLabel      *label_time_;       //显示最后一次聊天的时间


    YLListItemType item_type_;      //保存当前item的类型

};

#endif // YLFRIENDLISTITEM_H
