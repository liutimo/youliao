#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLLoginPanel/ylloginpanel.h"
#include "YLMainFrame/ylmainwidget.h"
#include "YLChatWidget/ylchatwidget.h"
#include "YLChatWidget/ylquickbar.h"
#include "YLChatWidget/ylemoticonwidget.h"
#include "YLChatWidget/ylmessageview.h"
#include "YLCommonControl/ylmodifyremark.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    YLQuickBar w;
//    YLChatWidget w;
//    YLLoginPanel w;
    YLMainWidget w;
//    YLModifyRemarkWidget w;
//    w.resize(500, 400);
    w.show();

    return a.exec();

}
