#ifndef YLSESSION_H
#define YLSESSION_H

#include <QObject>
#include "protobuf/youliao.base.pb.h"

using namespace youliao::pdu;
class YLSession : public QObject
{
    Q_OBJECT
public:
    explicit YLSession();

    YLSession(const YLSession&);

    YLSession &operator =(const YLSession &);

    bool operator ==(const YLSession &) const;

    bool operator <(const YLSession &) const;

    void setSessionId(uint32_t sessionId) { m_session_id = sessionId; }

    void setOtherId(uint32_t otherId) { m_other_id = otherId; }

    void setSessionType(uint32_t sessionType) { m_session_type = sessionType; }

    void setSessionTop(uint32_t top) { m_session_top = top;}

    void setSessionTop(bool top)
    {
        if (top)
            m_session_top = base::SESSION_FLAG_ONTOP;
        else
            m_session_top = base::SESSION_FLAG_NORMAL;
    }

    void setSessionLastChatMessage(const QString &msg) { m_session_last_message = msg; }

    void setSessionLastChatTime(const uint32_t chatTime) { m_session_last_chat_time = chatTime;}

    void addUnReadMsgCount() { ++m_unread_msg_count; }

    uint32_t getSessionId() const {return m_session_id;}

    uint32_t getOtherId() const { return m_other_id; }

    uint32_t getSessionType() const { return m_session_type; }

    uint32_t getSessionTop() const { return m_session_top;}

    const QString& getSessionLastChatMessage() const{ return m_session_last_message; }

    uint32_t getSessionLastChatTime()const { return m_session_last_chat_time; }

    bool sessionTop() const{
        if (base::SessionFlag_IsValid(m_session_top))
        {
            if (base::SESSION_FLAG_ONTOP == m_session_top)
                return true;
        }
        return false;
    }

    uint32_t getUnReadMsgCount() const { return m_unread_msg_count; }

private:
    uint32_t m_session_id;
    uint32_t m_other_id;
    uint32_t m_session_type;
    uint32_t m_session_top;
    QString m_session_last_message;
    uint32_t m_session_last_chat_time;
    uint32_t m_unread_msg_count;
};

#endif // YLSESSION_H
