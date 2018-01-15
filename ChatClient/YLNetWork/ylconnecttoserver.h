#ifndef YLCONNECTTOSERVER_H
#define YLCONNECTTOSERVER_H

#include <QObject>
#include <QTcpSocket>

class YLConnectToServer : public QObject
{
    Q_OBJECT
    const QString ip_address_ = "127.0.0.1";
    const unsigned int port_  = 8000;
    explicit YLConnectToServer(QObject *parent = nullptr);

public:
    void start();

private slots:
    void on_error(QAbstractSocket::SocketError socketError);



private:
    QTcpSocket *sock_;
};

#endif // YLCONNECTTOSERVER_H
