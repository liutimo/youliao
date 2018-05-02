#include "ylmessage.h"

YLMessage::YLMessage(QObject *parent) : QObject(parent)
{
    m_friend_id = 0;
    m_message_id = 0;
    m_create_time = 0;
}


YLMessage::YLMessage(const YLMessage &msg)
{
    m_friend_id = msg.m_friend_id;
    m_message_id = msg.m_message_id;
    m_create_time = msg.m_create_time;
    m_message_data = msg.m_message_data;
}


YLMessage& YLMessage::operator=(const YLMessage&msg)
{
    m_friend_id = msg.m_friend_id;
    m_message_id = msg.m_message_id;
    m_create_time = msg.m_create_time;
    m_message_data = msg.m_message_data;

    return *this;
}


bool YLMessage::operator ==(const YLMessage& msg) const
{
    if (m_message_id == msg.m_message_id && m_friend_id == msg.m_friend_id)
        return true;
    else
        return false;
}

void YLMessage::setFriendId(uint32_t friendId)
{
    m_friend_id = friendId;
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

uint32_t YLMessage::getFriendId() const
{
    return m_friend_id;
}

uint32_t YLMessage::getMessageId() const
{
    return m_message_id;
}

uint32_t YLMessage::getCreateTime() const
{
    return m_create_time;
}

const QString YLMessage::getMsgContent() const
{
    return m_message_data;
}
