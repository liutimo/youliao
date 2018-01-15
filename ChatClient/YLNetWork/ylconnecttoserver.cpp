#include "ylconnecttoserver.h"
#include <QDebug>
YLConnectToServer::YLConnectToServer(QObject *parent) : QObject(parent)
{
    sock_ = new QTcpSocket(this);
    connect(sock_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(on_error(QAbstractSocket::SocketError)));
}

void YLConnectToServer::start()
{
    sock_->connectToHost(ip_address_, port_);
}

void YLConnectToServer::on_error(QAbstractSocket::SocketError socketError)
{
    qDebug() << socketError;
//    switch (socketError) {
//    case QAbstractSocket::ConnectionRefusedError:

//        break;
//    default:
//        break;
//    }
}
