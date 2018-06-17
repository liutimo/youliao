#ifndef YLMESSAGE_H
#define YLMESSAGE_H
#include <QObject>
#include "protobuf/youliao.base.pb.h"
using namespace youliao::pdu;
class YLMessage : public QObject
{
    Q_OBJECT
public:
    explicit YLMessage(QObject *parent = nullptr);
    YLMessage(const YLMessage&);
    YLMessage& operator =(const YLMessage&);
    bool operator ==(const YLMessage&) const;

    void setSenderId(uint32_t);
    void setReceiverId(uint32_t);
    void setMessageId(uint32_t);
    void setGroupId(uint32_t);
    void setCreateTime(uint32_t);
    void setMsgContent(const QString &content);
    void setMessageType(base::MessageType type);

    uint32_t getSenderId() const;
    uint32_t getReceiverId() const;
    uint32_t getMessageId() const;
    uint32_t getGroupId() const;
    uint32_t getCreateTime() const;
    const QString getMsgContent() const;
    base::MessageType getMessageType() const;

private:
    uint32_t m_sender_id;
    uint32_t m_receiver_id;
    uint32_t m_group_id;                  //群组ＩＤ
    uint32_t m_message_id;
    uint32_t m_create_time;
    QString  m_message_data;
    base::MessageType m_message_type;    //消息类型
};

#endif // YLMESSAGE_H
