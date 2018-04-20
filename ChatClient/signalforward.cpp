#include "signalforward.h"

SignalForward* SignalForward::s_signamlForward = nullptr;

SignalForward::SignalForward(QObject *parent) : QObject(parent)
{

}

SignalForward* SignalForward::instance()
{
    if (s_signamlForward == nullptr)
    {
        s_signamlForward = new SignalForward;
    }

    return s_signamlForward;
}

void SignalForward::forwordUpdateSession(const YLSession &session)
{
    emit updateSession(session);
}
