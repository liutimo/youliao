#include "ylrecentchatview.h"
#include "yllistitem.h"
#include "YLNetWork/pduhandler.h"
#include "YLNetWork/ylbusiness.h"
#include "globaldata.h"
#include <QMouseEvent>
#include <QScrollBar>
#include <QDebug>
#include "signalforward.h"
YLRecentChatView::YLRecentChatView(QWidget *parent) : QListWidget(parent)
{
    setObjectName("YLRecentChatView");
    setStyleSheet(qss_this + qss_scroll_bar);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::NoFocus);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    connect(SignalForward::instance(), &SignalForward::readOne, this, &YLRecentChatView::readComplete);

    connect(PduHandler::instance(), &PduHandler::sessions, this, [this](const QList<base::SessionInfo> &lists)
    {
        for (base::SessionInfo session : lists)
        {
            YLSession s;
            s.setSessionId(session.session_id());
            s.setOtherId(session.other_id());
            s.setSessionLastChatMessage(session.last_message_data().c_str());
            s.setSessionTop(session.session_top());
            s.setSessionType(session.session_type());
            s.setSessionLastChatTime(session.session_update());

            if (s.sessionTop())
                m_top_data.push_back(s);
            m_data.push_back(s);
        }
        GlobalData::setSessions(m_data);
        updateList();
    });

    connect(PduHandler::instance(), &PduHandler::newSession, this, &YLRecentChatView::newSession);
    connect(PduHandler::instance(), &PduHandler::unReadMessage, this, [this](uint32_t friendId, const QString&message){
        for (YLSession &session : m_data)
        {
            if (session.getOtherId() == friendId)
            {
                session.addUnReadMsgCount();
                session.setSessionLastChatMessage(message);
                break;
            }
        }

        for (YLSession &session : m_top_data)
        {
            if (session.getOtherId() == friendId)
            {
                session.addUnReadMsgCount();
                session.setSessionLastChatMessage(message);
                break;
            }
        }

        GlobalData::setSessions(m_data);
        updateList();
    });
}

void YLRecentChatView::add(const YLSession &session, int pos)
{
    QListWidgetItem *item = new QListWidgetItem;
    insertItem(pos, item);
    item->setSizeHint(QSize(width() - 30, 56));
    YLListItem *item_widget = new YLListItem(YLListItem::RECENTTLYCHATITEM);
    connect(item_widget, &YLListItem::moveToTop,      this, &YLRecentChatView::on_move_to_top);
    connect(item_widget, &YLListItem::deleteFromList, this, &YLRecentChatView::on_del_from_list);
    connect(item_widget, &YLListItem::readCompleted, this, &YLRecentChatView::readComplete);

    item_widget->setData(GlobalData::getFriendById(session.getOtherId()), session);

    setItemWidget(item, item_widget);
}

void YLRecentChatView::addItem(const YLSession &session)
{
    for (auto iter = m_data.begin(); iter != m_data.end(); ++iter)
    {
        if (session == *iter)
        {
            m_data.erase(iter);
            break;
        }
    }

    for (auto &s : m_top_data)
    {
        if (s == session)
        {
            s = session;
            break;
        }
    }

    m_data.push_front(session);
    updateList();
}


void YLRecentChatView::updateList()
{
    clear();
    int i = 0;

    for (auto elem : m_top_data)
    {
        add(elem, i);
        static_cast<YLListItem*>(itemWidget(item(i++)))->setMarkTop(true);
    }

    for (auto &elem : m_data)
    {
        bool found = false;
        for (auto e : m_top_data)
        {
            if (e == elem)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            add(elem, i++);
        }

        qDebug() << m_data.size();
    }
}


void YLRecentChatView::mousePressEvent(QMouseEvent *event)
{
    auto item = itemAt(event->pos());
    if (item)
        item->setSelected(true);
    QListWidget::mousePressEvent(event);
}

void YLRecentChatView::on_move_to_top(YLSession &session)
{
    bool exist = false;

    for (auto iter = m_top_data.begin(); iter != m_top_data.end(); ++iter)
    {
        if (*iter == session)
        {
            (*iter).setSessionTop(false);
            m_top_data.erase(iter);
            exist = true;

            for (auto &s : m_data)
            {
                if (s == session)
                {
                    s.setSessionTop(false);
                    break;
                }
            }
            break;
        }
    }

    if (!exist)
    {
        m_top_data.push_front(session);
    }
    YLBusiness::topSession(GlobalData::getCurrLoginUserId(), session.getSessionId());
    updateList();
}

void YLRecentChatView::on_del_from_list(const YLSession &session)
{
    for (auto iter = m_top_data.begin(); iter != m_top_data.end(); ++iter)
    {
        if (*iter == session)
        {
            m_top_data.erase(iter);
            break;
        }
    }

    for (auto iter = m_data.begin(); iter != m_data.end(); ++iter)
    {
        if (*iter == session)
        {
            m_data.erase(iter);
            break;
        }
    }
    YLBusiness::deleteSession(GlobalData::getCurrLoginUserId(), session.getSessionId());
    updateList();
}

void YLRecentChatView::newSession(uint32_t otherId, uint32_t sessionId)
{
    for (auto &session : m_top_data)
    {
        if (session.getOtherId() == otherId)
        {
            session.setSessionId(sessionId);
            break;
        }
    }

    for (auto &session : m_data)
    {
        if (session.getOtherId() == otherId)
        {
            session.setSessionId(sessionId);
            break;
        }
    }

    GlobalData::setSessions(m_data);
    updateList();
}

void YLRecentChatView::readComplete(uint32_t friendId)
{

    for (YLSession &session : m_data)
    {
        if (session.getOtherId() == friendId)
        {
            session.clearUnReadMsgCount();
            break;
        }
    }

    for (YLSession &session : m_top_data)
    {
        if (session.getOtherId() == friendId)
        {
            session.clearUnReadMsgCount();
            break;
        }
    }

    GlobalData::setSessions(m_data);
    updateList();

}
