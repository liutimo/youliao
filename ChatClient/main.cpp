#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLLoginPanel/ylloginpanel.h"
#include "signalforward.h"
#include "YLDataBase/yldatabase.h"
#include "YLAddFriendWidgets/ylvalidategroupwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    YLDataBase::instance();

    SignalForward::instance();

    YLLoginPanel w;
    w.resize(500, 400);
    w.show();

    return a.exec();
}
