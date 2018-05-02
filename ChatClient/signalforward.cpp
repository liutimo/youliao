#include "signalforward.h"
#include "globaldata.h"
#include "YLTray/ylmessagetip.h"
#include "YLChatWidget/ylchatwidget.h"
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

void SignalForward::forwordIgnoreAll()
{
    emit ignoreAll();
}

void SignalForward::forwordReadAll()
{
    emit readAll();
}

void SignalForward::forwordReadOne(uint32_t friendId)
{
    emit readOne(friendId);
    YLFriend fri = GlobalData::getFriendById(friendId);
    YLChatWidget *chatWidget = GlobalData::getChatWidget(friendId);
    if (chatWidget == nullptr)
    {
        chatWidget = new YLChatWidget;
        chatWidget->resize(800, 600);
        chatWidget->setFriend(fri);
        GlobalData::addChatWidget(friendId, chatWidget);
    }

    chatWidget->show();
    connect(chatWidget, &YLChatWidget::loadFinish, this, [this, chatWidget, friendId](){
        auto msgs = GlobalData::getMessagesByFriendId(friendId);

        for (YLMessage msg : msgs)
        {
            chatWidget->receiveMessage(friendId, msg.getMsgContent());
        }

        GlobalData::removeMessageByFriendId(friendId);
        YLMessageTip::instance()->updateList();
    });


}
