#include "ylnetservice.h"
#include "base/netlib.h"
#include "login/loginconn.h"
#include "login/msgservconn.h"
using namespace youliao::network;

YLNetService* YLNetService::m_netservice = nullptr;

YLNetService::YLNetService(QObject *parent) : QThread(parent)
{
   netlib_init();
   m_reconnect_times = 0;
   start();
}

YLNetService* YLNetService::instance()
{
    if (m_netservice == nullptr)
        m_netservice = new YLNetService;
    return m_netservice;
}

void YLNetService::run()
{
    LoginConn *loginConn = new LoginConn;
    if (loginConn->connect("127.0.0.1", 5001))
    {
        m_reconnect_times = 0;
        emit connectLoginServerStatus(true);
        netlib_eventloop();
    }
    else
    {
        sleep(2);
        if (m_reconnect_times++ > 5)
        {
            emit connectLoginServerStatus(false);
            m_reconnect_times = 0;
            return;
        }
        else
            run();
    }

}
