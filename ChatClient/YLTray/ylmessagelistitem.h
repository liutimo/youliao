#ifndef YLMESSAGELISTITEM_H
#define YLMESSAGELISTITEM_H

#include <QWidget>


QT_BEGIN_NAMESPACE
class YLHeadFrame;
class QLabel;
class YLCounterBubble;
QT_END_NAMESPACE

class YLMessageListItem : public QWidget
{
    Q_OBJECT
public:
    typedef enum{FRIEND = 1, REQUEST = 2} ItemType;
    explicit YLMessageListItem(QWidget *parent = nullptr);
    void setNickOrRemark(const QString &);
    void setHeadFrame(const QString &);
    void setCounterNumber(int num);
    void setFriendId(uint32_t friId) { m_friend_id = friId; }
    void setType(ItemType type) { m_type = type; }
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    void init();
    QLabel          *m_nick_or_remark;
    YLHeadFrame     *m_head_frame;
    YLCounterBubble *m_counter_bubble;
    uint32_t m_friend_id;
    ItemType m_type;
};

#endif // YLMESSAGELISTITEM_H
