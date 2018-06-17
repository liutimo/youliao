#include <QApplication>
#include "YLLoginPanel/ylloginpanel.h"
#include "signalforward.h"
#include "YLFileTransfer/ylfiletransferreceiver.h"
#include "YLFileTransfer/yltransferfile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    a.setQuitOnLastWindowClosed(false);

    //启动文件接收线程
    YLFileTransferReceiver::instance();
    SignalForward::instance();

    YLLoginPanel w;
    w.resize(500, 370);
    w.show();

    return a.exec();
}
