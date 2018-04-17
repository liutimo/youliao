#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLLoginPanel/ylloginpanel.h"
#include "YLChatWidget/ylchatwidget.h"
#include "YLMainFrame/ylinfomationwidget.h"
#include "YLNetWork/http/httphelper.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    YLLoginPanel w;
//    YLChatWidget w;

    w.resize(500, 400);



//    YLInfomationWidget w;
//    w.resize(730, 530);
    w.show();




    return a.exec();

}
