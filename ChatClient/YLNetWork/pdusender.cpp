#include "pdusender.h"

PduSender* PduSender::m_pdu_sender = nullptr;

PduSender::PduSender()
{

}


void PduSender::run()
{
    for (;;)
    {
        m_condition.lock();
        if (m_message_list.empty())
            m_condition.wait();
        BasePdu *pdu = m_message_list.front();
        m_message_list.pop_front();
        m_condition.unlock();

        //send pdu
       m_msg_serv_conn->sendBasePdu(pdu);
        delete pdu;
    }
}

void PduSender::addMessage(BasePdu *pdu)
{
    m_condition.lock();
    m_message_list.push_back(pdu);
    m_condition.signal();
    m_condition.unlock();
}

PduSender* PduSender::instance()
{
    if (m_pdu_sender == nullptr)
    {
        m_pdu_sender = new PduSender;
        m_pdu_sender->start();
    }

    return m_pdu_sender;
}
