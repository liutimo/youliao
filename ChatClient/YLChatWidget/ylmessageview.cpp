#include "ylmessageview.h"
#include <QWebChannel>
#include <QDebug>
#include "test.h"
#include "globaldata.h"
#include <QAudioOutput>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include "YLDataBase/yldatabase.h"
YLMessageView::YLMessageView(QWidget *parent) : QWebEngineView(parent), m_current_page(0), m_current_index(0)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);
    load(QUrl("qrc:/res/YLChatWidget/bubble.html"));
    setContextMenuPolicy(Qt::NoContextMenu);

    Test *t = new Test();
    t->setView(this);
    channel = new QWebChannel(page());
    channel->registerObject("T", t);
    page()->setWebChannel(channel);

    connect(t, &Test::startPlayAudio, this, &YLMessageView::audio);

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
    QString script = QString("document.getElementById(\"content\").insertAdjacentHTML(\"beforeEnd\",\"<div style='overflow:hidden;'><p class='divotherhead'><img src='%1' width='30px' height='30px' > </p><p class='triangle-left left' onmousedown='mouseDown(event)'>%2</p></div>\")").arg(head).arg(content) ;
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
    QString html = QString("<div style='overflow:hidden;'><p class='divMyHead'><img src='%1' width='30px' height='30px' ></p>\
                    <div id='1' class='triangle-right right' onmousedown='mouseDown(event)' style='display:inline-block'>\
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
//    emit playAudio(msgId);

    QString key = QString::number(m_friend_id) + "_" + QString::number(msgId);

    QString fileName = GlobalData::getAudio(key);

    sourceFile.setFileName(fileName);
    sourceFile.open(QIODevice::ReadOnly);

    //[1]设置音频格式
    QAudioFormat format;
    format.setSampleRate(8000);                         //采样率
    format.setChannelCount(1);                          //单声道
    format.setSampleSize(8);                            //采样精度
    format.setCodec("audio/amrnb");                       //格式
    format.setByteOrder(QAudioFormat::LittleEndian);    //字节序
    format.setSampleType(QAudioFormat::UnSignedInt);    //采样类型

    //[2]获取音频设备信息
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format))
        format = info.nearestFormat(format);            //支持的最接近的format

    //[3] 初始化QAudioInput
    m_audio_output = new QAudioOutput(format, this);
    m_audio_output->setVolume(80);

    connect(m_audio_output, &QAudioOutput::stateChanged, this, [this] (QAudio::State newState){
        switch (newState) {
                  case QAudio::IdleState:
                      // Finished playing (no more data)
                      m_audio_output->stop();
                      sourceFile.close();
                      delete m_audio_output;
                      break;

                  case QAudio::StoppedState:
                      // Stopped for other reasons
                      if (m_audio_output->error() != QAudio::NoError) {
                          // Error handling
                      }
                      break;

                  default:
                      // ... other cases as appropriate
                      break;
              }
    });

    m_audio_output->start(&sourceFile);
}

void YLMessageView::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();
    QWebEngineView::mousePressEvent(event);
}
