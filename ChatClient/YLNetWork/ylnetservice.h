#ifndef YLNETSERVICE_H
#define YLNETSERVICE_H

#include <QThread>
class LoginConn;
class YLNetService : public QThread
{
    Q_OBJECT
public:
    void connectToLoginServer(const QString&ip, quint16 port);
    static YLNetService* instance();
signals:
    void msgServerFull();
    void noMsgServer();
    void connectMsgServerSuccess();

protected:
    void run() override;

signals:
    void connectLoginServerStatus(bool);

public slots:

private:
    explicit YLNetService(QObject *parent = nullptr);

    static YLNetService* m_netservice;
    LoginConn *loginConn;
    uint m_reconnect_times;
};

#endif // YLNETSERVICE_H
