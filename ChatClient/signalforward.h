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
    void forwardInviteGroupSelected(uint32_t friId);
    void forwardAddSendFileItem(uint32_t userId, const QString &taskId);
    void forwardAddRecvFileItem(uint32_t userId, const QString &taskId);
    void forwardUpdateProgressBar(uint32_t userId, const QString &taskId ,uint32_t currentProgress);
    void forwardTransferComplete(uint32_t userId, const QString &taskId);
    void forwardCancelFileTransfer(uint32_t userId, const QString &taskId);
    void forwardRefuseFileTransfer(uint32_t userId, const QString &taskId);

//    void updateProgressBar(uint32_t userId, const QString &taskId ,uint32_t currentProgress);
//    void transferComplete(uint32_t userId, const QString &taskId);


signals:
    void updateSession(const YLSession &);
    void ignoreAll();
    void readAll();
    void readOne(uint32_t friendId);
    void inviteGroupSelected(uint32_t friId);
private:
    explicit SignalForward(QObject *parent = nullptr);
    static SignalForward *s_signamlForward;
};

#endif // SIGNALFORWARD_H
