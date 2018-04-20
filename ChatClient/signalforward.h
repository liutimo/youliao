#ifndef SIGNALFORWARD_H
#define SIGNALFORWARD_H

#include <QObject>
#include <YLEntityObject/ylsession.h>
class SignalForward : public QObject
{
    Q_OBJECT
public:
    SignalForward(const SignalForward&) = delete;
    SignalForward& operator=(const SignalForward&) = delete;

    static SignalForward* instance();

    void forwordUpdateSession(const YLSession &);

signals:
    void updateSession(const YLSession &);

private:
    explicit SignalForward(QObject *parent = nullptr);
    static SignalForward *s_signamlForward;
};

#endif // SIGNALFORWARD_H
