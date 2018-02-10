#include "netlibservice.h"
#include "netlib.h"
#include "util.h"
#include "loginconn.h"
using namespace youliao::network;

NetlibService::NetlibService(QObject *parent) : QThread(parent)
{

}


void NetlibService::run()
{
    netlib_init();
    //连接登录服务器
    LoginConn *loginConn = new LoginConn;
    loginConn->connect("127.0.0.1", 8001);

    netlib_eventloop();
    netlib_destory();
}
