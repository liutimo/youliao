#include <QApplication>
#include <QDebug>
#include <QThread>
#include "YLLoginPanel/ylloginpanel.h"
#include "signalforward.h"
#include "YLDataBase/yldatabase.h"
#include "YLFileTransfer/ylfiletransferreceiver.h"
#include "YLFileTransfer/yltransferfile.h"
#include "YLChatWidget/ylsinglechatwidget.h"
#include "YLCommonControl/ylrecordaudiowidget.h"

#include <QMenu>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);

    //启动文件接收线程
    YLFileTransferReceiver::instance();
    SignalForward::instance();

    YLLoginPanel w;
    w.resize(500, 400);
    w.show();


    return a.exec();
}
