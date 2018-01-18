#include "YLLoginPanel/ylloginpanel.h"
#include "YLMainFrame/ylmainwidget.h"
#include <QApplication>
#include <QDebug>
#include "YLMainFrame/ylfriendlistitem.h"
#include "YLEntityObject/ylfriend.h"
#include <QTcpSocket>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//
    YLLoginPanel w;
    w.resize(300, 400);
    w.show();

//    YLFriend y;
//    y.setFriendAccount("779564531");
//    y.setFriendImagePath(":/res/2.jpeg");
//    y.setFriendLastChatTime("11:22");
//    y.setFriendLastMessage("你好，我是刘正！");
//    y.setFriendNickName("刘提莫");
//    y.setFriendRemark("刘正");
//    y.setFriendSigature("我希望我的青春遇见你");

//    YLFriendListItem w1(YLFriendListItem::RECENTTLYCHATITEM);
//    w1.setData(y);
//    w1.resize(400, 50);
//    w1.show();

//    YLFriendListItem w2(YLFriendListItem::FRIENDITEM);
//    w2.setData(y);
//    w2.resize(400, 50);
//    w2.show();



    return a.exec();
}
