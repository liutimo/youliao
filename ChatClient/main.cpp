#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLLoginPanel/ylloginpanel.h"
#include "YLChatWidget/ylchatwidget.h"
#include "YLMainFrame/ylinfomationwidget.h"
#include "signalforward.h"
#include "YLNetWork/base/util.h"
#include "YLTray/ylmessagelistitem.h"
#include "YLDataBase/yldatabase.h"
#include "YLAddFriendWidgets/ylvalidatemessagewidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    YLDataBase::instance();

    SignalForward::instance();

    YLLoginPanel w;
//    YLChatWidget w;

    w.resize(500, 400);


    w.show();




    return a.exec();

}
