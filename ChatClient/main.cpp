#include "YLLoginPanel/ylloginpanel.h"
#include "YLMainFrame/ylmainwidget.h"
#include <QApplication>
#include <QDebug>
#include "YLMainFrame/ylfriendlistitem.h"
#include <QTcpSocket>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    YLLoginPanel w;
    YLFriendListItem w;
    w.resize(400, 50);
    w.show();



    return a.exec();
}
