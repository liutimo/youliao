//
// Created by liuzheng on 18-3-25.
//

#ifndef DBSERVER_DBPROXYTASK_H
#define DBSERVER_DBPROXYTASK_H

#include "thread/task.h"
#include "pdu/BasePdu.h"
using namespace youliao::thread;
using namespace youliao::pdu;

typedef void (*pdu_handler_t)(BasePdu* pPdu, uint32_t conn_uuid);

class DBProxyTask : public Task
{
public:
    DBProxyTask(BasePdu *, uint32_t, pdu_handler_t);
    ~DBProxyTask();

    void run() override ;

private:
    BasePdu      *m_base_pdu;
    uint32_t      m_conn_uuid;
    pdu_handler_t m_handler;

};


#endif //DBSERVER_DBPROXYTASK_H
