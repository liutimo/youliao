#include <QApplication>
#include <QDebug>
#include <QThread>

#include "YLNetWork/netservice.h"
#include "YLLoginPanel/ylloginpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QThread *background = new QThread;

    if (YLNetService::instance() == nullptr)
        return -1;
    else
    {
        YLNetService::instance()->moveToThread(background);
    }
    background->start();
    YLLoginPanel w;

    w.resize(300, 400);
    w.show();


    return a.exec();
}
