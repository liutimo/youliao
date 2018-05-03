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
    void forwordIgnoreAll();
    void forwordReadAll();
    void forwordReadOne(uint32_t friendId, int type);
signals:
    void updateSession(const YLSession &);
    void ignoreAll();
    void readAll();
    void readOne(uint32_t friendId);

private:
    explicit SignalForward(QObject *parent = nullptr);
    static SignalForward *s_signamlForward;
};

#endif // SIGNALFORWARD_H
