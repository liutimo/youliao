#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLNetWork/util.h"
#include "YLLoginPanel/ylloginpanel.h"
#include "YLNetWork/netlibservice.h"
#include "YLNetWork/pduhandler.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //启动网络线程
    NetlibService *netlib_service = new NetlibService;
    netlib_service->setLoginServerIP("127.0.0.1");
    netlib_service->setLoginServerPort(8001);
    netlib_service->start();

    YLLoginPanel w;
    w.resize(300, 400);
    w.show();


    return a.exec();
}
