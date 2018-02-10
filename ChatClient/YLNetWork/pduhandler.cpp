#include "pduhandler.h"
#include <list>

//全局PDU list
//主线程产生的所有pdu都会放入这个list中
//子线程循环冲list读数据发送到消息服务器
//如果list为空,则子线程休眠
std::list<BasePdu*> g_pdu_list;
Condition           g_condition;


PduHandler::PduHandler(QObject *parent) : QThread(parent)
{

}

void PduHandler::run()
{
    for(;;)
    {
        g_condition.lock();

        if (g_pdu_list.empty())
            g_condition.wait();

        BasePdu *basePdu = g_pdu_list.front();
        g_pdu_list.pop_front();
        g_condition.unlock();

        _HandleBasePdu(basePdu);
        delete basePdu;
    }
}

void PduHandler::_HandleBasePdu(BasePdu *pdu)
{

}
