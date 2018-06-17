#ifndef YLGROUPMEMBER_H
#define YLGROUPMEMBER_H

#include <QObject>

class YLGroupMember : public QObject
{
    Q_OBJECT
public:
    explicit YLGroupMember(QObject *parent = nullptr);
    YLGroupMember(const YLGroupMember&);
    YLGroupMember& operator=(const YLGroupMember &);

    void setGroupId(uint32_t);
    void setMemberId(uint32_t);
    void setLastChatTime(uint32_t);
    void setGroupCard(const QString&);
    void setMemberType(uint8_t);
    void setMemberNick(const QString&);
    void setMemberHeader(const QString&);


    uint32_t getGroupId() const;
    uint32_t getMemberId() const;
    uint32_t getLastChatTime() const;
    QString getGroupCard() const;
    uint8_t getMemberType() const;
    QString getMemberNick() const;
    QString getMemberHeader() const;

private:
    uint32_t    m_group_id;
    uint32_t    m_member_id;
    uint32_t    m_last_chat_time;
    QString     m_group_card;
    uint8_t     m_type;
    QString     m_member_nick;
    QString     m_member_header;
};

#endif // YLGROUPMEMBER_H
