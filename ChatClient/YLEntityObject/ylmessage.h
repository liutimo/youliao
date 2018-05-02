#ifndef YLMESSAGE_H
#define YLMESSAGE_H
#include <QObject>


class YLMessage : public QObject
{
    Q_OBJECT
public:
    explicit YLMessage(QObject *parent = nullptr);
    YLMessage(const YLMessage&);
    YLMessage& operator =(const YLMessage&);
    bool operator ==(const YLMessage&) const;

    void setFriendId(uint32_t);
    void setMessageId(uint32_t);
    void setCreateTime(uint32_t);
    void setMsgContent(const QString &content);

    uint32_t getFriendId() const;
    uint32_t getMessageId() const;
    uint32_t getCreateTime() const;
    const QString getMsgContent() const;

private:
    uint32_t m_friend_id;
    uint32_t m_message_id;
    uint32_t m_create_time;
    QString  m_message_data;
};

#endif // YLMESSAGE_H
