#ifndef YLGROUP_H
#define YLGROUP_H
#include <QObject>
#include <QVector>
class YLGroup : public QObject
{
public:
    explicit YLGroup();

    YLGroup(const YLGroup &);

    YLGroup &operator =(const YLGroup &);

    bool operator ==(const YLGroup &) const;

    bool operator <(const YLGroup &) const;

    void setGroupId(uint32_t groupId);

    void setGroupName(const QString &groupName);

    void setGroupCreator(uint32_t creator);

    void setGroupCapacity(uint32_t capacity);

    void setGroupImage(const QString &url);

    void addMember(uint32_t memberId);

    void addManager(uint32_t managerId);

    void setCreateTime(uint32_t createTime);

    void setVerifyType(uint32_t type);

    uint32_t getGroupId() const;

    QString getGroupName() const;

    uint32_t getGroupCreator() const;

    uint32_t getGroupCapacity() const;

    QString getGroupImage() const;

    QVector<uint32_t> getMembers() const;

    QVector<uint32_t> getManagers() const;

    uint32_t getCreateTime() const;

    uint32_t getVerifyType() const;

    uint32_t getCount() const { return 1 + m_managers.size() + m_members.size(); }
private:
    uint32_t m_group_id;
    uint32_t m_creator;
    uint32_t m_capacity;
    uint32_t m_created;
    uint32_t m_verify_type;
    QVector<uint32_t> m_managers;
    QVector<uint32_t> m_members;
    QString m_group_name;
    QString m_head_url;
};

#endif // YLGROUP_H
