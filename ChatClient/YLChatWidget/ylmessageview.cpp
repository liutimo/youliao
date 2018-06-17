#include "ylmessageview.h"
#include <QWebChannel>
#include <QDebug>
#include "test.h"
#include "globaldata.h"
#include <QAudioOutput>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include "YLDataBase/yldatabase.h"
#include <QDir>
YLMessageView::YLMessageView(QWidget *parent) : QWebEngineView(parent), m_current_page(0), m_current_index(0)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    load(QUrl("qrc:/res/YLChatWidget/bubble.html"));
    setContextMenuPolicy(Qt::NoContextMenu);


    m_player = new QMediaPlayer(this);

    Test *t = new Test();
    t->setView(this);
    channel = new QWebChannel(page());
    channel->registerObject("T", t);
    page()->setWebChannel(channel);

    connect(t, &Test::startPlayAudio, this, &YLMessageView::audio);

    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, [](QMediaPlayer::MediaStatus status){
        //判断状态
        //播放完成后停止气泡动画。
    });
}

void YLMessageView::loadMore()
{
    QVector<QPair<uint32_t, QString>> vec;
    {
        YLDataBase db;
        vec = db.getMoreMessage(m_friend_id, m_current_page, m_current_index);
    }

    if (vec.empty())
        return;

    ++m_current_page;

    for (QPair<uint32_t, QString> &pair : vec)
    {
        if (pair.first = m_friend_id)
        {
            loadLeft(m_friend_icon_path, pair.second);
        }
        else
        {
            loadRight(GlobalData::getCurrLoginUserIconPath(), pair.second);
        }
    }

    addLoadMore();
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
    ++m_current_index;
}

void YLMessageView::loadRight(const QString &head, const QString &content)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"afterBegin\",\"<div style='overflow:hidden;'><p class='divMyHead'><img src='%1' width='30px' height='30px' > </p><p id='1' class='triangle-right right' onmousedown='mouseDown(event)'>%2</p></div>\")").arg(head).arg(content) ;
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
    ++m_current_index;
}


void YLMessageView::addLeft(const QString &head, const QString &content)
{
    qDebug() << head;
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='divotherhead'><img src='%1' width='30px' height='30px' > </p><p class='triangle-left left' onmousedown='mouseDown(event)'>%2</p></div>\")").arg(head).arg(content) ;
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
    ++m_current_index;
}

void YLMessageView::addGroupLeft(const QString &icon, const QString &name, const QString &content)
{
    qDebug() << icon;
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='divOtherHead'><img src='%1' width='30px' height='30px' ></p> <div> <p class='group-name-left'>%2</p><p class='triangle-left left' onmousedown='mouseDown(event)'>%3</p> <div></div>\")").arg(icon).arg(name).arg(content);
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
    ++m_current_index;
}

void YLMessageView::loadLeft(const QString &head, const QString &content)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"afterBegin\",\"<div style='overflow:hidden;'><p class='divotherhead'><img src='%1' width='30px' height='30px' > </p><p class='triangle-left left' onmousedown='mouseDown(event)'>%2</p></div>\")").arg(head).arg(content) ;
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
    ++m_current_index;
}

void YLMessageView::addLeftAudio(const QString &head, uint32_t msgId, uint32_t duration)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='divotherhead'><img src='%1' width='30px' height='30px' > </p><p class='triangle-left left' onmousedown='mouseDown(event)'><span id='%2' onmousedown='audioLeftMouseDown(event)'><img src = 'qrc:/res/YLChatWidget/left.png' width='20px' height='20px'/> &nbsp&nbsp&nbsp&nbsp%3'</span></p></div>\")").arg(head).arg(msgId).arg(duration) ;
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::addCancelSend(const QString &fileName, const QString &fileSize)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div class='pfile'><div class='filetip'> <img src='qrc:/res/YLChatWidget/time.png'/> 您取消了“%1”(%2)的发送，文件传输失败。</div></div>\")").arg(fileName).arg(fileSize);
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::addCancelRecv(const QString &fileName, const QString &fileSize)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div class='pfile'><div class='filetip'> <img src='qrc:/res/YLChatWidget/time.png'/> 您取消接收“%1”(%2)，文件传输失败。</div></div>\")").arg(fileName).arg(fileSize);
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}


void YLMessageView::sendFileSuccess(const QString &head, const QString &fileName, const QString &fileSize)
{
    QString html = QString("<div style='overflow:hidden;'> <p class='divMyHead'> <img src='%1' width='30px' height='30px' /> </p>\
                    <div id='1' class='triangle-right right' onmousedown='mouseDown(event)' style='display:inline-block'> \
                    <div><div class='file' ><p class ='fileinfo'><span class='filename'>%2 </span><span class='filesize'> (%3) </span> </p>\
                    <p class='tipmsg'>成功发送文件</p><p class ='op'><a href='#' class='opendir'>打开文件夹</a><a href='#' class='openfile'>打开</a></p></div>\
                    <div class='fileicon' style='width:40px; position:relative; '><img src='qrc:/res/FileIcon/audio.png' width='100%' />\
                    <img src='file:///home/liuzheng/Desktop/cancel.png'  style='position:absolute; right:0; bottom:0;' /></div>\
                    </div></div></div>").arg(head).arg(fileName).arg(fileSize);

    qDebug() << html;
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\", \"%1\")").arg(html);
    qDebug() << script;
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::recvFileSuccess(const QString &head, const QString &fileName, const QString &fileSize)
{
    QString html = QString("<div style='overflow:hidden;'><p class='divOtherHead'><img src='%1' width='30px' height='30px' ></p>\
                    <div id='1' class='triangle-left left' onmousedown='mouseDown(event)' style='display:inline-block'>\
                    <div><div class='file' ><p class ='fileinfo'><span class='filename'>%2 </span><span class='filesize'> (%3) </span> </p>\
                    <p class='tipmsg'>成功接收文件</p><p class ='op'><a href='#' class='opendir'>打开文件夹</a><a href='#' class='openfile'>打开</a></p></div>\
                    <div class='fileicon' style='width:40px; position:relative; '><img src='qrc:/res/FileIcon/audio.png' width='100%' />\
                    <img src='file:///home/liuzheng/Desktop/cancel.png'  style='position:absolute; right:0; bottom:0;' /></div>\
                    </div></div></div>").arg(head).arg(fileName).arg(fileSize);

    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\", \"%1\")").arg(html);
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}


void YLMessageView::opponentCancalSend(const QString &fileName, const QString&fileSize)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div class='pfile'><div class='filetip'> <img src='qrc:/res/YLChatWidget/time.png'/> 对方取消了“%1”(%2)的发送。</div></div>\")").arg(fileName).arg(fileSize);
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::opponentCancalRecv(const QString &fileName, const QString&fileSize)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div class='pfile'><div class='filetip'> <img src='qrc:/res/YLChatWidget/time.png'/> 对方取消接收“%1”(%2)，文件发送失败。</div></div>\")").arg(fileName).arg(fileSize);
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::opponentRefuseRecv(const QString &fileName, const QString&fileSize)
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div class='pfile'><div class='filetip'> <img src='qrc:/res/YLChatWidget/time.png'/> 对方取消接收“%1”(%2)，文件发送失败。</div></div>\")").arg(fileName).arg(fileSize);
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::addLoadMore()
{
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"afterBegin\",\"<div id='more' class='more'><a href='javascript:;' onClick='loadmore1();'><img src='qrc:/res/YLChatWidget/time.png'/>查看更多消息</a></div>\")");
    page()->runJavaScript(script);
    script = QString("keepOnBottom()");
    page()->runJavaScript(script);
}

void YLMessageView::copy()
{

}


void YLMessageView::audio(uint32_t msgId)
{
    QString key = QString::number(m_friend_id) + "_" + QString::number(msgId);

    QString fileName = QDir::currentPath() + "/" + GlobalData::getAudio(key);

    m_player->setMedia(QUrl::fromLocalFile(fileName));
    m_player->play();
}

void YLMessageView::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();
    QWebEngineView::mousePressEvent(event);
}
