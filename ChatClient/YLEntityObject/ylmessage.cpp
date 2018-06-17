#include "ylmessage.h"

YLMessage::YLMessage(QObject *parent) : QObject(parent)
{
    m_sender_id = 0;
    m_group_id = 0;
    m_message_id = 0;
    m_create_time = 0;
}


YLMessage::YLMessage(const YLMessage &msg)
{
    m_group_id      = msg.m_group_id;
    m_receiver_id   = msg.m_receiver_id;
    m_sender_id     = msg.m_sender_id;
    m_message_id    = msg.m_message_id;
    m_create_time   = msg.m_create_time;
    m_message_data  = msg.m_message_data;
    m_message_type  = msg.m_message_type;

}


YLMessage& YLMessage::operator=(const YLMessage&msg)
{
    m_group_id      = msg.m_group_id;
    m_sender_id     = msg.m_sender_id;
    m_receiver_id   = msg.m_receiver_id;
    m_message_id    = msg.m_message_id;
    m_create_time   = msg.m_create_time;
    m_message_data  = msg.m_message_data;
    m_message_type  = msg.m_message_type;
    return *this;
}


bool YLMessage::operator ==(const YLMessage& msg) const
{
    if (m_message_id == msg.m_message_id && m_sender_id == msg.m_sender_id)
        return true;
    else
        return false;
}

void YLMessage::setSenderId(uint32_t senderId)
{
    m_sender_id = senderId;
}


void YLMessage::setReceiverId(uint32_t receiverId)
{
    m_receiver_id = receiverId;
}

void YLMessage::setGroupId(uint32_t groupId)
{
    m_group_id = groupId;
}

void YLMessage::setMessageId(uint32_t messageId)
{
    m_message_id = messageId;
}

void YLMessage::setCreateTime(uint32_t createTime)
{
    m_create_time = createTime;
}

void YLMessage::setMsgContent(const QString &content)
{
    m_message_data = content;
}

void YLMessage::setMessageType(base::MessageType type)
{
    m_message_type = type;
}

uint32_t YLMessage::getSenderId() const
{
    return m_sender_id;
}

uint32_t YLMessage::getReceiverId() const
{
    return m_receiver_id;
}

uint32_t YLMessage::getMessageId() const
{
    return m_message_id;
}


uint32_t YLMessage::getGroupId() const
{
    return m_group_id;
}

uint32_t YLMessage::getCreateTime() const
{
    return m_create_time;
}

const QString YLMessage::getMsgContent() const
{
    return m_message_data;
}

base::MessageType YLMessage::getMessageType() const
{
    return m_message_type;
}
