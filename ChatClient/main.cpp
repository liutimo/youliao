#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLLoginPanel/ylloginpanel.h"
#include "YLChatWidget/ylchatwidget.h"
#include "signalforward.h"
#include "YLDataBase/yldatabase.h"
#include "YLChatWidget/yltransferfiletasklistwidget.h"
#include "YLMainFrame/ylcreategroupwidget.h"
#include "YLMainFrame/ylgroupinfowidget.h"
#include "YLCommonControl/ylmemberlistwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    YLDataBase::instance();

    SignalForward::instance();

//    YLGroupInfoWidget w;

    YLLoginPanel w;

    w.resize(500, 400);
    w.show();

    return a.exec();
}
