#include "ylsession.h"

YLSession::YLSession()
{
    m_unread_msg_count = 0;
}

YLSession::YLSession(const YLSession &session)
{
    *this = session;
}

YLSession &YLSession::operator =(const YLSession &session)
{
    m_session_id = session.getSessionId();
    m_other_id = session.getOtherId();
    m_session_type = session.getSessionType();
    m_session_top = session.getSessionTop();
    m_session_last_chat_time = session.getSessionLastChatTime();
    m_session_last_message = session.getSessionLastChatMessage();
    m_unread_msg_count = session.m_unread_msg_count;
}

bool YLSession::operator ==(const YLSession &session) const
{
    if (m_session_id == session.getSessionId() && m_other_id == session.getOtherId())
        return true;
    else
        return false;
}

bool YLSession::operator <(const YLSession &session) const
{
    if (m_session_last_chat_time < session.getSessionLastChatTime())
        return true;
    else
        return false;
}
