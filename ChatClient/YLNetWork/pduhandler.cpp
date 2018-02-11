#include "pduhandler.h"
#include <list>
#include "protobuf/youliao.base.pb.h"
#include "protobuf/youliao.login.pb.h"
//全局PDU list
//主线程产生的所有pdu都会放入这个list中
//子线程循环冲list读数据发送到消息服务器
//如果list为空,则子线程休眠
std::list<BasePdu*> g_pdu_list;
Condition           g_condition;


PduHandler* PduHandler::m_pdu_handler = nullptr;

PduHandler::PduHandler(QObject *parent) : QThread(parent)
{

}

PduHandler* PduHandler::instance()
{
    if (m_pdu_handler == nullptr)
    {
        m_pdu_handler = new PduHandler;
        m_pdu_handler->start();
    }

    return m_pdu_handler;
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
    switch (pdu->getCID()) {
    case base::CID_LOGIN_RESPONE_USERLOGIN:
        _HandleUserLoginRespone(pdu);
        break;
    case base::CID_OTHER_HEARTBEAT:
        _HandleHeartBeat();
        break;
    default:
        break;
    }
}

void PduHandler::_HandleUserLoginRespone(BasePdu *pdu)
{
    login::UserLoginRespone respone;
    respone.ParseFromString(pdu->getMessage());
    if (respone.result_code() == base::NONE)
    {
        base::UserInfo *userInfo = new base::UserInfo(respone.user_info());
        emit loginStatus(true, userInfo);
    }
    else
        emit loginStatus(false);
}

void PduHandler::_HandleHeartBeat()
{
    ++m_heartbeat_received_times;
}
