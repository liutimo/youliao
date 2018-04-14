#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLLoginPanel/ylloginpanel.h"

#include "YLMainFrame/ylinfomationwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    YLLoginPanel w;
    w.resize(500, 400);



//    YLInfomationWidget w;
//    w.resize(730, 530);
    w.show();




    return a.exec();

}
