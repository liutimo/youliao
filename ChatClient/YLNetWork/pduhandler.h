#ifndef PDUHANDLER_H
#define PDUHANDLER_H
#include <QThread>
#include "BasePdu.h"

using namespace youliao::pdu;

class PduHandler : public QThread
{
    Q_OBJECT
public:
    explicit PduHandler(QObject *parent = nullptr);
    void run() override;

signals:

private:
    void _HandleBasePdu(BasePdu *pdu);
};

#endif // PDUHANDLER_H
