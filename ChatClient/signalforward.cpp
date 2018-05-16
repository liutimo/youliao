#include "signalforward.h"
#include "globaldata.h"
#include "YLTray/ylmessagetip.h"
#include "YLChatWidget/ylsinglechatwidget.h"
#include "YLAddFriendWidgets/ylvalidatemessagewidget.h"
#include "YLFileTransfer/ylfiletransferreceiver.h"
SignalForward* SignalForward::s_signamlForward = nullptr;

SignalForward::SignalForward(QObject *parent) : QObject(parent)
{
    connect(YLFileTransferReceiver::instance(), &YLFileTransferReceiver::addSendFileItem, this, &SignalForward::forwardAddSendFileItem);
    connect(YLFileTransferReceiver::instance(), &YLFileTransferReceiver::addRecvFileItem, this, &SignalForward::forwardAddRecvFileItem);
    connect(YLFileTransferReceiver::instance(), &YLFileTransferReceiver::updateProgressBar, this, &SignalForward::forwardUpdateProgressBar);
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

void SignalForward::forwordIgnoreAll()
{
    emit ignoreAll();
}

void SignalForward::forwordReadAll()
{
    emit readAll();
}

void SignalForward::forwordReadOne(uint32_t friendId, int type)
{
    if (type == 1)
    {
        emit readOne(friendId);
        YLFriend fri = GlobalData::getFriendById(friendId);
        YLSingleChatWidget *singleChatWidget = GlobalData::getSingleChatWidget(friendId);
        if (singleChatWidget == nullptr)
        {
            singleChatWidget = new YLSingleChatWidget;
            singleChatWidget->setFriend(fri);
            GlobalData::addSingleChatWidget(friendId, singleChatWidget);
        }

        singleChatWidget->show();
        connect(singleChatWidget, &YLSingleChatWidget::loadFinish, this, [this, singleChatWidget, friendId](){
            auto msgs = GlobalData::getMessagesByFriendId(friendId);

            for (YLMessage msg : msgs)
            {
                singleChatWidget->receiveMessage(friendId, msg.getMsgContent());
            }

            GlobalData::removeMessageByFriendId(friendId);
            YLMessageTip::instance()->updateList();
        });
    }
    else if (type == 2)
    {
        YLValidateMessageWidget *w = new YLValidateMessageWidget;
        w->show();
        GlobalData::clearAllRequest();
        YLMessageTip::instance()->updateList();
    }

}


void SignalForward::forwardInviteGroupSelected(uint32_t friId)
{
    emit inviteGroupSelected(friId);
}

void SignalForward::forwardAddSendFileItem(uint32_t userId, const QString &taskId)
{
    GlobalData::getSingleChatWidget(userId)->addSendFileItem(taskId);
}


void SignalForward::forwardAddRecvFileItem(uint32_t userId, const QString &taskId)
{

    GlobalData::getSingleChatWidget(userId)->addRecvFileItem(taskId);
}

void SignalForward::forwardUpdateProgressBar(uint32_t userId, const QString &taskId ,uint32_t currentProgress)
{
    GlobalData::getSingleChatWidget(userId)->updateFileTransferProgressBar(taskId, currentProgress);
}

void SignalForward:: forwardTransferComplete(uint32_t userId, const QString &taskId)
{

}
