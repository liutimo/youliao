#ifndef SIGNALFORWARD_H
#define SIGNALFORWARD_H

#include <QObject>
#include <YLEntityObject/ylfriend.h>
class SignalForward : public QObject
{
    Q_OBJECT
public:
    SignalForward(const SignalForward&) = delete;
    SignalForward& operator=(const SignalForward&) = delete;

    static SignalForward* instance();

    void forwordUpdateSession(const YLFriend &);

signals:
    void updateSession(const YLFriend &);

private:
    explicit SignalForward(QObject *parent = nullptr);
    static SignalForward *s_signamlForward;
};

#endif // SIGNALFORWARD_H
