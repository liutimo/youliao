#ifndef PDUSENDER_H
#define PDUSENDER_H

#include <QThread>
#include <list>
#include <google/protobuf/message_lite.h>
#include "base/Lock.h"
#include "base/Thread.h"
#include "base/BasePdu.h"
#include "msgservconn.h"
using namespace youliao::thread;
using namespace youliao::pdu;
class PduSender : public Thread
{
public:
    void run() override;

    void addMessage(BasePdu*);
    void setMsgServConn(MsgServConn *conn) { m_msg_serv_conn = conn; }
    void connect() { m_connected = true; }
    static PduSender* instance();

private:
    PduSender();
    std::list<BasePdu *> m_message_list;
    Condition            m_condition;
    MsgServConn         *m_msg_serv_conn;
    static PduSender    *m_pdu_sender;
    bool m_connected;
};

#endif // PDUSENDER_H
