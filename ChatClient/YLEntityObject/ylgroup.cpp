#include "ylgroup.h"

YLGroup::YLGroup()
{

}

YLGroup::YLGroup(const YLGroup &group)
{

    m_group_id = group.m_group_id;
    m_group_name = group.m_group_name;
    m_creator = group.m_creator;
    m_capacity = group.m_capacity;
    m_managers = group.m_managers;
    m_members = group.m_members;
    m_group_name = group.m_group_name;
    m_head_url = group.m_head_url;
    m_created = group.m_created;
    m_verify_type = group.m_verify_type;
}

YLGroup &YLGroup::operator =(const YLGroup &group)
{
    m_group_id = group.m_group_id;
    m_group_name = group.m_group_name;
    m_creator = group.m_creator;
    m_capacity = group.m_capacity;
    m_managers = group.m_managers;
    m_members = group.m_members;
    m_group_name = group.m_group_name;
    m_head_url = group.m_head_url;
    m_created = group.m_created;
    m_verify_type = group.m_verify_type;
    return *this;

}

bool YLGroup::operator ==(const YLGroup &group) const
{
    if (m_group_id == group.m_group_id)
        return true;
    else
        return false;
}

bool YLGroup::operator <(const YLGroup &group) const
{
    if (m_group_id <= group.m_group_id)
        return true;
    else
        return false;
}

void YLGroup::setGroupId(uint32_t groupId)
{
    m_group_id = groupId;
}

void YLGroup::setGroupName(const QString &groupName)
{
    m_group_name = groupName;
}

void YLGroup::setGroupCreator(uint32_t creator)
{
    m_creator = creator;
}

void YLGroup::setGroupCapacity(uint32_t capacity)
{
    m_capacity = capacity;
}

void YLGroup::setGroupImage(const QString &url)
{
    m_head_url = url;
}

void YLGroup::addMember(uint32_t memberId)
{
    m_members.push_back(memberId);
}

void YLGroup::addManager(uint32_t managerId)
{
    m_managers.push_back(managerId);
}


void YLGroup::setCreateTime(uint32_t createTime)
{
    m_created = createTime;
}

void YLGroup::setVerifyType(uint32_t type)
{
    m_verify_type = type;
}

uint32_t YLGroup::getGroupId() const
{
    return m_group_id;
}

QString YLGroup::getGroupName() const
{
    return m_group_name;
}

uint32_t YLGroup::getGroupCreator() const
{
    return m_creator;
}

uint32_t YLGroup::getGroupCapacity() const
{
    return m_capacity;
}

QString YLGroup::getGroupImage() const
{
    return m_head_url;
}

QVector<uint32_t> YLGroup::getMembers() const
{
    return m_members;
}

QVector<uint32_t> YLGroup::getManagers() const
{
    return m_managers;
}

uint32_t YLGroup::getCreateTime() const
{
    return m_created;
}

uint32_t YLGroup::getVerifyType() const
{
    return m_verify_type;
}
