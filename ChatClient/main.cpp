#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLNetWork/util.h"
#include "YLLoginPanel/ylloginpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    YLLoginPanel w;
    w.resize(300, 400);
    w.show();


    return a.exec();
}
