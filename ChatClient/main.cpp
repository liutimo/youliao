#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLLoginPanel/ylloginpanel.h"
#include "signalforward.h"
#include "YLDataBase/yldatabase.h"
#include "YLChatWidget/ylchatlistwidget.h"
#include "YLChatWidget/ylsinglechatwidget.h"
#include "YLChatWidget/ylgroupchatwidget.h"
#include "YLCommonControl/ylgroupmemberlistwidget.h"
#include "YLCommonControl/ylbutton.h"
#include <QMenu>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    a.setQuitOnLastWindowClosed(false);

    YLDataBase::instance();

    SignalForward::instance();

    YLLoginPanel w;
    w.resize(500, 400);
    w.show();

//    YLSingleChatWidget w;
//    w.show();

    return a.exec();
}
