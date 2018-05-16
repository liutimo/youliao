#include "ylmessageview.h"
#include <QWebChannel>
#include <QDebug>
#include "test.h"
YLMessageView::YLMessageView(QWidget *parent) : QWebEngineView(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    load(QUrl("qrc:/res/YLChatWidget/bubble.html"));
    setContextMenuPolicy(Qt::NoContextMenu);

    Test *t = new Test();
    t->setPage(page());
    channel = new QWebChannel(page());
    channel->registerObject("T", t);
    page()->setWebChannel(channel);
}

YLMessageView::~YLMessageView()
{
    if (channel)
        delete channel;
    qDebug() << "~YLMessageView()";
}

void YLMessageView::addRight(const QString &head, const QString &content)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='divMyHead'><img src='%1' width='30px' height='30px' > </p><p id='1' class='triangle-right right' onmousedown='mouseDown(event)'>%2</p></div>\")").arg(head).arg(content) ;
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::addLeft(const QString &head, const QString &content)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='divotherhead'><img src='%1' width='30px' height='30px' > </p><p class='triangle-left left' onmousedown='mouseDown(event)'>%2</p></div>\")").arg(head).arg(content) ;
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}


void YLMessageView::addCancelSend(const QString &fileName, const QString &fileSize)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div class='pfile'><div class='filetip'> <img src='qrc:/res/YLChatWidget/time.png'/> 您取消接收文件“%1” (%2)的发送，文件传输失败。</div></div>\")").arg(fileName).arg(fileSize);
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::addCancelRecv(const QString &fileName, const QString &fileSize)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div class='pfile'><div class='filetip'> <img src='qrc:/res/YLChatWidget/time.png'/> 对方取消接收“%1”(%2)，文件发送失败</div></div>\")").arg(fileName).arg(fileSize);
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::copy()
{

}

void YLMessageView::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();
    QWebEngineView::mousePressEvent(event);
}
