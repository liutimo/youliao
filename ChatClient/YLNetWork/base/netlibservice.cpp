#include "netlibservice.h"
#include "netlib.h"
#include "util.h"
#include "../login/loginconn.h"
using namespace youliao::network;

NetlibService::NetlibService(QObject *parent) : QThread(parent)
{

}


void NetlibService::run()
{
    netlib_init();
    //连接登录服务器
    LoginConn *loginConn = new LoginConn;
    if (loginConn->connect(m_login_server_ip.toStdString(), m_login_server_port))
    {
        emit loginServerConnectStatus(true);
        netlib_eventloop();
    }
    else
    {
        this->sleep(1);
        if  (m_times++ > 5)
        {
            emit loginServerConnectStatus(false);
            return;
        }
        run();
    }
    netlib_destory();
}
