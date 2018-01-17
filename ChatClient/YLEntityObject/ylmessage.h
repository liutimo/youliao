#ifndef YLMESSAGE_H
#define YLMESSAGE_H
#include <QObject>

class YLMessage : public QObject
{
public:
    YLMessage(QObject *parent = nullptr);
};

#endif // YLMESSAGE_H
