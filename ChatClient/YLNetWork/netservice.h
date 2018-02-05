#ifndef NETSERVICE_H
#define NETSERVICE_H

#include <QObject>
#include <QTimer>
typedef enum{
    Connect2ServerFailed = 0
}YLNetServiceError;

class YLNetService : public QObject
{
    Q_OBJECT
    YLNetService(QObject *parent = nullptr);
public:
    static YLNetService* instance();


signals:
    void error(YLNetServiceError error);
public slots:
    void start();
private:
    static YLNetService *m_service;
    QTimer *timer;

};

void conn2server(void*callback_data, uint8_t msg, uint32_t fd, void* pParam);

#endif // NETSERVICE_H
