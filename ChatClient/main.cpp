#include "YLLoginPanel/ylloginpanel.h"

#include <QApplication>
#include <QDebug>
#include "YLCommonControl/yllineedit.h"
#include <QTcpSocket>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YLLoginPanel w;
    w.resize(400, 350);
    w.show();



    return a.exec();
}
