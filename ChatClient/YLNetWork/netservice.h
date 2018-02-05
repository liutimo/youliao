#ifndef NETSERVICE_H
#define NETSERVICE_H

#include <QObject>

class NetService : public QObject
{
    Q_OBJECT
public:
    explicit NetService(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NETSERVICE_H