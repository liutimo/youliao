//
// Created by liuzheng on 18-3-25.
//

#include "DBProxyTask.h"

DBProxyTask::DBProxyTask(BasePdu *basePdu, uint32_t conn_uuid, pdu_handler_t pdu_handler)
{
    m_base_pdu = basePdu;
    m_conn_uuid = conn_uuid;
    m_handler = pdu_handler;
}

DBProxyTask::~DBProxyTask()
{
    if (m_base_pdu)
        delete m_base_pdu;
}

void DBProxyTask::run()
{
    if (!m_base_pdu)
    {
        //...
    }
    else
    {
        if (m_handler)
        {
            m_handler(m_base_pdu, m_conn_uuid);
        }

    }

}
