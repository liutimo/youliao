#include "ylgroupmember.h"

YLGroupMember::YLGroupMember(QObject *parent) : QObject(parent)
{

}
YLGroupMember::YLGroupMember(const YLGroupMember&member)
{
    m_group_id = member.m_group_id;
    m_member_id = member.m_member_id;
    m_last_chat_time = member.m_last_chat_time;
    m_group_card = member.m_group_card;
    m_type = member.m_type;
    m_member_nick = member.m_member_nick;
    m_member_header = member.m_member_header;
}

YLGroupMember& YLGroupMember::operator=(const YLGroupMember &member)
{
    m_group_id = member.m_group_id;
    m_member_id = member.m_member_id;
    m_last_chat_time = member.m_last_chat_time;
    m_group_card = member.m_group_card;
    m_type = member.m_type;
    m_member_nick = member.m_member_nick;
    m_member_header = member.m_member_header;
    return *this;
}

void YLGroupMember::setGroupId(uint32_t groupId)
{
    m_group_id = groupId;
}

void YLGroupMember::setMemberId(uint32_t memberId)
{
    m_member_id = memberId;
}

void YLGroupMember::setLastChatTime(uint32_t lastTime)
{
    m_last_chat_time = lastTime;
}

void YLGroupMember::setGroupCard(const QString& card)
{
    m_group_card = card;
}

void YLGroupMember::setMemberType(uint8_t type)
{
    m_type = type;
}

void YLGroupMember::setMemberNick(const QString& nick)
{
    m_member_nick = nick;
}

void YLGroupMember::setMemberHeader(const QString& header)
{
    m_member_header = header;
}

uint32_t YLGroupMember::getGroupId() const
{
    return m_group_id;
}
uint32_t YLGroupMember::getMemberId() const
{
    return m_member_id;
}

uint32_t YLGroupMember::getLastChatTime() const
{
    return m_last_chat_time;
}

QString YLGroupMember::getGroupCard() const
{
    return m_group_card;
}

uint8_t YLGroupMember::getMemberType() const
{
    return m_type;
}

QString YLGroupMember::getMemberNick() const
{
    return m_member_nick;
}

QString YLGroupMember::getMemberHeader() const
{
    return m_member_header;
}
