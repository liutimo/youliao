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
    typedef enum{FRIEND = 1, GROUP = 2, REQUEST = 3} ItemType;
    explicit YLMessageListItem(QWidget *parent = nullptr);
    void setName(const QString &);
    void setHeadFrame(const QString &);
    void setCounterNumber(int num);
    void setSenderId(uint32_t senderId) { m_sender_id = senderId; }
    void setGroupId(uint32_t groupId) { m_group_id = groupId; }
    void setType(ItemType type) { m_type = type; }
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);

private:
    void init();
    QLabel          *m_nick_or_remark;
    YLHeadFrame     *m_head_frame;
    YLCounterBubble *m_counter_bubble;
    uint32_t m_sender_id;
    uint32_t m_group_id;

    ItemType m_type;
};

#endif // YLMESSAGELISTITEM_H
