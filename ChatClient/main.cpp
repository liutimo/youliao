#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLNetWork/util.h"
#include "YLLoginPanel/ylloginpanel.h"
#include "YLMainFrame/ylmainwidget.h"
#include "YLChatWidget/ylchatwidget.h"
#include "YLChatWidget/ylquickbar.h"
#include "YLChatWidget/ylemoticonwidget.h"
#include "YLChatWidget/ylmessageview.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    YLQuickBar w;
    YLChatWidget w;
    w.resize(600, 400);
    w.show();

    return a.exec();

}
