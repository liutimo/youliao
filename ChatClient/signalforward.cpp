#include "signalforward.h"
#include "globaldata.h"
#include "YLTray/ylmessagetip.h"
#include "YLNetWork/ylbusiness.h"
#include "YLDataBase/yldatabase.h"
#include "YLChatWidget/ylsinglechatwidget.h"
#include "YLFileTransfer/ylfiletransferreceiver.h"
#include "YLAddFriendWidgets/ylvalidatemessagewidget.h"
SignalForward* SignalForward::s_signamlForward = nullptr;

SignalForward::SignalForward(QObject *parent) : QObject(parent)
{
    connect(YLFileTransferReceiver::instance(), &YLFileTransferReceiver::addSendFileItem, this, &SignalForward::forwardAddSendFileItem);
    connect(YLFileTransferReceiver::instance(), &YLFileTransferReceiver::addRecvFileItem, this, &SignalForward::forwardAddRecvFileItem);
    connect(YLFileTransferReceiver::instance(), &YLFileTransferReceiver::updateProgressBar, this, &SignalForward::forwardUpdateProgressBar);
    connect(YLFileTransferReceiver::instance(), &YLFileTransferReceiver::transferComplete, this, &SignalForward::forwardTransferComplete);
    connect(YLFileTransferReceiver::instance(), &YLFileTransferReceiver::refuseFileTransfer, this, &SignalForward::forwardRefuseFileTransfer);
    connect(YLFileTransferReceiver::instance(), &YLFileTransferReceiver::cancelFileTransfer, this, &SignalForward::forwardCancelFileTransfer);
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

void SignalForward::forwordReadOne(uint32_t senderId, int type)
{
    if (type == 1)
    {
        YLFriend fri = GlobalData::getFriendById(senderId);
        YLSingleChatWidget *singleChatWidget = GlobalData::getSingleChatWidget(senderId);
        if (singleChatWidget == nullptr)
        {
            singleChatWidget = new YLSingleChatWidget;
            singleChatWidget->setFriend(fri);
            GlobalData::addSingleChatWidget(senderId, singleChatWidget);
        }

        singleChatWidget->show();
        connect(singleChatWidget, &YLSingleChatWidget::loadFinish, this, [this, singleChatWidget, senderId](){
            auto msgs = GlobalData::getMessagesByFriendId(senderId);

            for (YLMessage msg : msgs)
            {
                {
                    YLDataBase db;
                    db.saveMessage(msg);
                }
                singleChatWidget->receiveMessage(senderId, msg.getMsgContent());
                YLBusiness::sendMessageAck(senderId, GlobalData::getCurrLoginUserId(), msg.getMessageId());
            }

            GlobalData::removeMessageByFriendId(senderId);
            YLMessageTip::instance()->updateList();
            emit readOne(GlobalData::getSessionByFriendId(senderId).getSessionId());
        });
    }
    else if (type == 2)         // 群组消息
    {
        YLGroup group = GlobalData::getGroupByGroupId(senderId);
        YLGroupChatWidget *groupChatWidget = GlobalData::getGroupChatWidget(senderId);
        if (groupChatWidget == nullptr)
        {
            groupChatWidget = new YLGroupChatWidget;
            groupChatWidget->setGroup(group);
            GlobalData::addGroupChatWidget(senderId, groupChatWidget);
        }

        groupChatWidget->show();
        connect(groupChatWidget, &YLGroupChatWidget::loadFinish, this, [this, groupChatWidget, senderId](){
            auto msgs = GlobalData::getGroupMessagesByGroupId(senderId);

            for (YLMessage msg : msgs)
            {
                groupChatWidget->receiveMessage(senderId, msg.getMsgContent());
            }

            GlobalData::removeGroupMessageByGroupId(senderId);
            YLMessageTip::instance()->updateList();
        });
    }
    else if (type == 3)
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
    auto w = GlobalData::getSingleChatWidget(userId);
    if (w)
        w->addSendFileItem(taskId);
}


void SignalForward::forwardAddRecvFileItem(uint32_t userId, const QString &taskId)
{
    auto w = GlobalData::getSingleChatWidget(userId);
    if (w)
        w->addRecvFileItem(taskId);
}

void SignalForward::forwardUpdateProgressBar(uint32_t userId, const QString &taskId ,uint32_t currentProgress)
{
    auto w = GlobalData::getSingleChatWidget(userId);
    if (w)
        w->updateFileTransferProgressBar(taskId, currentProgress);
}

void SignalForward::forwardTransferComplete(uint32_t userId, const QString &taskId)
{
    auto w = GlobalData::getSingleChatWidget(userId);
    if (w)
        w->transferComplete(taskId);
}

void SignalForward::forwardCancelFileTransfer(uint32_t userId, const QString &taskId)
{
    auto w = GlobalData::getSingleChatWidget(userId);
    if (w)
        w->cancelFileTransfer(taskId);
}

void SignalForward::forwardRefuseFileTransfer(uint32_t userId, const QString &taskId)
{
    auto w = GlobalData::getSingleChatWidget(userId);
    if (w)
        w->refuseFileTransfer(taskId);
}
