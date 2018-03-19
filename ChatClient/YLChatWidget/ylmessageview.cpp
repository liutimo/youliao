#include "ylmessageview.h"
#include <QWebChannel>
#include "test.h"
YLMessageView::YLMessageView(QWidget *parent) : QWebEngineView(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    load(QUrl("qrc:/res/YLChatWidget/bubble.html"));
    setContextMenuPolicy(Qt::NoContextMenu);

    Test *t = new Test();
    t->setPage(page());
    QWebChannel *channel = new QWebChannel(page());
    channel->registerObject("T", t);
    page()->setWebChannel(channel);
}

void YLMessageView::copy()
{

}
