#ifndef NETLIBSERVICE_H
#define NETLIBSERVICE_H

#include <QObject>
#include <QThread>
class NetlibService : public QThread
{
    Q_OBJECT
public:
    explicit NetlibService(QObject *parent = nullptr);

    void setLoginServerIP(const QString &ip) {m_login_server_ip = ip;}
    void setLoginServerPort(quint16 port) {m_login_server_port = port;}

    void run();
signals:

public slots:

private:
    QString m_login_server_ip;
    quint16 m_login_server_port;
};

#endif // NETLIBSERVICE_H
