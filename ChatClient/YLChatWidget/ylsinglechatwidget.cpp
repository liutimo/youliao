#include "globaldata.h"
#include "ylmessageview.h"
#include "signalforward.h"
#include "ylsinglechatwidget.h"
#include "ylmessageeditwidget.h"
#include "YLNetWork/ylbusiness.h"
#include "YLEntityObject/ylsession.h"
#include "YLCommonControl/ylbutton.h"
#include "YLNetWork/http/httphelper.h"
#include "yltransferfiletasklistwidget.h"
#include "YLCommonControl/ylrecordaudiowidget.h"
#include "YLFileTransfer/ylfiletransfermanager.h"
#include "YLChatWidget/ylemoticonwidget.h"
#include <QDir>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFile>
#include <QFileDialog>
#include "YLDataBase/yldatabase.h"
YLSingleChatWidget::YLSingleChatWidget(QWidget *parent) : QWidget(parent), m_hide(true), m_scale_width(0)
{
    setAttribute(Qt::WA_DeleteOnClose);
    resize(800, 650);
    init();
    initMidToolBar();
    initRight();
}

YLSingleChatWidget::~YLSingleChatWidget()
{
    GlobalData::removeSingleChatWidget(m_friend.friendId());
}

void YLSingleChatWidget::setFriend(const YLFriend &fri)
{
    m_friend = fri;
    uint32_t msgId = GlobalData::getLatestMsgId(m_friend.friendId());
    m_friend_header_path = "file://" + GlobalData::imagePath + "/" + m_friend.friendImageName();
    m_message_view->setFriendId(m_friend.friendId());
    m_message_view->setFriendIconPath(m_friend_header_path);
    if (msgId == 0)
    {
        //send request
        YLBusiness::getLatestMsgId(m_friend.friendId());
    }
}


void YLSingleChatWidget::addSendFileItem(const QString &taskId)
{
    if (m_transfer_file_widget->count() < 1)
    {
            m_split_button->show();
            m_hide = false;
    }
    m_transfer_file_widget->addSendFile(taskId);
}


void YLSingleChatWidget::addRecvFileItem(const QString &taskId)
{
    if (m_transfer_file_widget->count() < 1)
    {
            m_split_button->show();
            m_hide = false;
    }
    m_transfer_file_widget->addRecvFile(taskId);
}


void YLSingleChatWidget::updateFileTransferProgressBar(const QString &taskId, uint32_t progress)
{
    m_transfer_file_widget->updateFileTransferProgressBar(taskId, progress);
}


void YLSingleChatWidget::transferComplete(const QString &taskId)
{
    YLTransferFileEntity entity;
    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId.toStdString(), entity))
        return;
    QString s;
    uint32_t size = entity.m_file_size;
    if (size < 1024)
    {
        s = QString::number(size) + "Bytes";
    }
    else if (size > 1024 && size < 1024 * 1024)
    {
        s = QString::number(size / 1024.0) + "KB";
    }
    else if (size > 1024 * 1024 && size < 1024 * 1024 * 1024)
    {
        s = QString::number(size / 1024.0 / 1024.0) + "MB";
    }

    uint32_t pos = entity.m_file_name.find_last_of('/');

    if (entity.m_client_role == base::CLIENT_REALTIME_SENDER)
        m_message_view->sendFileSuccess(GlobalData::getCurrLoginUserIconPath(), entity.m_file_name.substr(pos + 1).c_str(), s);
    else
        m_message_view->recvFileSuccess(m_friend_header_path, entity.m_file_name.c_str(), s);
    m_transfer_file_widget->transferComplete(taskId);
}


void YLSingleChatWidget::cancelFileTransfer(const QString &taskId)
{
    YLTransferFileEntity entity;
    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId.toStdString(), entity))
        return;
    QString s;
    uint32_t size = entity.m_file_size;
    if (size < 1024)
    {
        s = QString::number(size) + "Bytes";
    }
    else if (size > 1024 && size < 1024 * 1024)
    {
        s = QString::number(size / 1024.0) + "KB";
    }
    else if (size > 1024 * 1024 && size < 1024 * 1024 * 1024)
    {
        s = QString::number(size / 1024.0 / 1024.0) + "MB";
    }
    if (entity.m_client_role == base::CLIENT_REALTIME_SENDER)
        m_message_view->opponentCancalRecv(entity.m_file_name.c_str(), s);
    else
        m_message_view->opponentCancalSend(entity.m_file_name.c_str(), s);

    m_transfer_file_widget->cancelFileTransfer(taskId);
}

void YLSingleChatWidget::refuseFileTransfer(const QString &taskId)
{
    YLTransferFileEntity entity;
    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId.toStdString(), entity))
        return;
    QString s;
    uint32_t size = entity.m_file_size;
    if (size < 1024)
    {
        s = QString::number(size) + "Bytes";
    }
    else if (size > 1024 && size < 1024 * 1024)
    {
        s = QString::number(size / 1024.0) + "KB";
    }
    else if (size > 1024 * 1024 && size < 1024 * 1024 * 1024)
    {
        s = QString::number(size / 1024.0 / 1024.0) + "MB";
    }

    m_message_view->opponentRefuseRecv(entity.m_file_name.c_str(), s);;

    m_transfer_file_widget->refuseFileTransfer(taskId);
}

void YLSingleChatWidget::init()
{
    m_label = new QLabel(this);
    QPixmap pixmap(":/res/YLChatWidget/1.png");
    m_label->setFixedSize(pixmap.size());
    m_label->setPixmap(pixmap);
    m_label->move(5, 5);

    m_message_view = new YLMessageView(this);
    m_message_view->setFocusPolicy(Qt::NoFocus);
    m_message_view->resize(width(), 450);
    m_message_view->move(0, 50);
    m_message_view->setStyleSheet("background:red;");
    connect(m_message_view, &YLMessageView::loadFinished, this, [this](bool f) {
        //load message
        YLDataBase db;
        auto vec = db.getRecentMessage(m_friend.friendId());

        for (QPair<uint32_t, QString> pair : vec)
        {
            //senderid 是当前登录用户
            if (pair.first == GlobalData::getCurrLoginUserId())
            {
                m_message_view->addRight(GlobalData::getCurrLoginUserIconPath(), pair.second);
            }
            else
            {
                m_message_view->addLeft(m_friend_header_path, pair.second);
            }

        }

        if (f) emit loadFinish();
    });

    m_label2 = new QLabel(this);
    QPixmap pixmap1(":/res/YLChatWidget/2.png");
    m_label2->setFixedSize(pixmap1.size());
    m_label2->setPixmap(pixmap1);
    m_label2->hide();;

    m_message_edit_widget = new YLMessageEditWidget(this);
    m_message_edit_widget->resize(width(), 75);

    m_close_button = new QPushButton("关闭", this);
    m_close_button->setFixedSize(65, 30);
    m_close_button->setStyleSheet("border:0px;background-color:white; color:black");
    connect(m_close_button, &QPushButton::clicked, this, [this](){close();});

    m_send_button = new QPushButton("发送", this);
    m_send_button->setFixedSize(65, 30);
    m_send_button->setStyleSheet("border:0px;background-color:white; color:black");
    connect(m_send_button, &QPushButton::clicked, this, &YLSingleChatWidget::sendMessage);
}


void YLSingleChatWidget::initMidToolBar()
{
    m_emotion = new YLButton(this);
    m_emotion->setImage(":/res/YLChatWidget/aio_quickbar_face.png");
    m_emotion->setFixedSize(35, 30);
    connect(m_emotion, &YLButton::clicked, this, &YLSingleChatWidget::showEmotionWidget);

    m_gif = new YLButton(this);
    m_gif->setImage(":/res/YLChatWidget/aio_quickbar_gif.png");
    m_gif->setFixedSize(35, 30);

    m_cut = new YLButton(this);
    m_cut->setImage(":/res/YLChatWidget/aio_quickbar_cut.png");
    m_cut->setFixedSize(35, 30);

    m_audio = new YLButton(this);
    m_audio->setImage(":/res/YLChatWidget/aio_quickbar_audio.png");
    m_audio->setFixedSize(35, 30);
    connect(m_audio, &YLButton::clicked, this, &YLSingleChatWidget::recordAudio);

    m_file = new YLButton(this);
    m_file->setImage(":/res/YLChatWidget/aio_quickbar_uploadfile.png");
    m_file->setFixedSize(35, 30);
    connect(m_file, &YLButton::clicked, this, &YLSingleChatWidget::selectFile);

    m_image = new YLButton(this);
    m_image->setImage(":/res/YLChatWidget/aio_quickbar_sendpic.png");
    m_image->setFixedSize(35, 30);

    m_more = new YLButton(this);
    m_more->setImage(":/res/YLChatWidget/aio_quickbar_more.png");
    m_more->setFixedSize(35, 30);

    m_msg_record = new YLButton(this);
    m_msg_record->setImage(":/res/YLChatWidget/aio_quickbar_register.png");
    m_msg_record->setFixedSize(35, 30);

    m_record_audio = new YLRecordAudioWidget(this);
    m_record_audio->setFixedHeight(30);
    m_record_audio->hide();
    connect(m_record_audio, &YLRecordAudioWidget::send, this, [this](){
        QString fileName = m_record_audio->stop();
        updateSizeAndPosition();

        YLBusiness::sendAudioMessage(GlobalData::getCurrLoginUserId(), m_friend.friendId(), fileName, m_record_audio->getTime());
    });
    connect(m_record_audio, &YLRecordAudioWidget::cancel, this, [this](){
        m_record_audio->cancelRecord();
        updateSizeAndPosition();
    });


    QHBoxLayout *hl = new QHBoxLayout;

    hl->addWidget(m_emotion);
    hl->addWidget(m_gif);
    hl->addWidget(m_cut);
    hl->addWidget(m_audio);
    hl->addWidget(m_file);
    hl->addWidget(m_image);
    hl->addWidget(m_more);
    hl->addStretch();
    hl->addWidget(m_msg_record);
    hl->setMargin(0);
    hl->setSpacing(0);

    m_mid_toolbar = new QWidget(this);
    m_mid_toolbar->setLayout(hl);
}

void YLSingleChatWidget::initRight()
{
    m_split_button = new QPushButton(this);
    m_split_button->setFixedSize(13, 90);
    m_split_button->setStyleSheet(qss_split_button_left);
    m_split_button->hide();
    connect(m_split_button, &QPushButton::clicked, this, &YLSingleChatWidget::spliteButtonClicked);

    m_transfer_file_widget = new YLTransferFileTaskListWidget(this);
    m_transfer_file_widget->hide();
    connect(m_transfer_file_widget, &YLTransferFileTaskListWidget::cancelSend, this, [this](const QString &fileName, const QString &fileSize){
        m_message_view->addCancelSend(fileName, fileSize);
    });

    connect(m_transfer_file_widget, &YLTransferFileTaskListWidget::cancelRecv, this, [this](const QString &fileName, const QString &fileSize){
        m_message_view->addCancelRecv(fileName, fileSize);
    });
}

void YLSingleChatWidget::updateSizeAndPosition()
{
    m_send_button->move(width() - 95 - m_scale_width, height() - 40);
    m_close_button->move(width() - 165 - m_scale_width, height() - 40);
    m_split_button->move(width() - m_scale_width - 13, height() / 2 - 45);
    m_mid_toolbar->move(0, height() - 148);
    m_message_edit_widget->move(0, height() - 110);
    m_transfer_file_widget->move(width() - 300, 51);    
    m_record_audio->move(0, m_mid_toolbar->geometry().topLeft().y() - 30);

    m_message_view->resize(width() - m_scale_width, m_mid_toolbar->geometry().topLeft().y() - 51 -(m_record_audio->isHidden() ? 0 : 30));
    m_mid_toolbar->resize(width() - m_scale_width, 35);
    m_transfer_file_widget->setFixedHeight(height() - 51);
    m_record_audio->setFixedWidth(width() - m_scale_width);
}

void YLSingleChatWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(250, 250, 251)); //#FAFAFB
    p.drawRect(rect());

    p.setPen(QColor::fromRgb(217, 217, 218));     //#E7E7E8
    p.drawLine(0, 49, width(), 49);
    p.drawLine(0, height() - 147, width(), height() - 147);

}


void YLSingleChatWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    updateSizeAndPosition();
}


void YLSingleChatWidget::receiveMessage(uint32_t user_id, const QString &message)
{
    if (user_id == m_friend.friendId())
    {
        QRegExp re;
        re.setPattern("<img.*src='.*'.*>");
        re.setMinimal(true);
        QString msg = message;
        m_message_view->addLeft(m_friend_header_path, message);
        msg.replace(re, "[Picture]");
        YLSession session = GlobalData::getSessionByFriendId(m_friend.friendId());
        session.setOtherId(user_id);
        session.setSessionType(base::SESSION_TYPE_SINGLE);
        session.setSessionLastChatMessage(msg);
        session.setSessionLastChatTime(QDateTime::currentDateTime().toTime_t());
        SignalForward::instance()->forwordUpdateSession(session);
    }
}


void YLSingleChatWidget::receiveAudioMessage(uint32_t user_id, const QString &message, uint32_t duration, uint32_t msgId)
{
    if (user_id == m_friend.friendId())
    {
        m_message_view->addLeftAudio(m_friend_header_path, duration, msgId);
        YLSession session = GlobalData::getSessionByFriendId(m_friend.friendId());
        session.setOtherId(user_id);
        session.setSessionType(base::SESSION_TYPE_SINGLE);
        session.setSessionLastChatMessage("[语音]");
        session.setSessionLastChatTime(QDateTime::currentDateTime().toTime_t());
        SignalForward::instance()->forwordUpdateSession(session);
        //send message ack
    }
}

void YLSingleChatWidget::showEmotionWidget()
{
    if (YLEmoticonWidget::isShow)
        return;

    YLEmoticonWidget  *emotionWidget = new YLEmoticonWidget();
    QPoint p = mapToGlobal(QPoint(0, 502));
    emotionWidget->move(p.x(), p.y() - 230);
    emotionWidget->show();
    connect(emotionWidget, &YLEmoticonWidget::selected, m_message_edit_widget, &YLMessageEditWidget::addEmoticon);
}


void YLSingleChatWidget::spliteButtonClicked()
{
    if (!m_hide)
    {
        m_scale_width = 300;
        m_split_button->setStyleSheet(qss_split_button_right);
        m_transfer_file_widget->show();
    }
    else
    {
        m_scale_width = 0;
        m_split_button->setStyleSheet(qss_split_button_left);
        m_transfer_file_widget->hide();
    }
    updateSizeAndPosition();
    m_hide = !m_hide;
}


void YLSingleChatWidget::recordAudio()
{
    m_record_audio->show();
    m_record_audio->start();
    updateSizeAndPosition();
}

void YLSingleChatWidget::sendMessage()
{
    QString content = m_message_edit_widget->getContent();
    m_message_edit_widget->clear();

    QString pattern = "src='(file:.*)'";
    QRegExp re(pattern);
    re.setMinimal(true);
    int pos = 0;
    QStringList fileList;
    while ((pos = re.indexIn(content, pos)) >= 0 )
    {
        QString p = re.cap(1);
        fileList << p;
        pos += re.matchedLength();
    };

    HttpHelper *helper = new HttpHelper;
    QStringList uploadFileList;
    for (QString fileName : fileList)
    {
        QString localFile = fileName.replace("file://", "");
        uploadFileList << helper->upload(localFile);
    }


    m_message_view->addRight(GlobalData::getCurrLoginUserIconPath(), content);

    for (int i = 0; i < fileList.size(); ++i)
    {
        content.replace(fileList[i], "http://www.liutimo.cn/images/" + uploadFileList[i]);
    }

    YLBusiness::sendMessage(GlobalData::getCurrLoginUserId(), m_friend.friendId(), content);

    YLSession session = GlobalData::getSessionByFriendId(m_friend.friendId());

    //session 存在,更新session
    if (session.getOtherId() == m_friend.friendId())
    {
        session.setSessionLastChatMessage(content);
        session.setSessionLastChatTime(QDateTime::currentDateTime().toTime_t());
        SignalForward::instance()->forwordUpdateSession(session);
    }

}


void YLSingleChatWidget::selectFile()
{
    //暂时只能发送文件
    QString filePath = QFileDialog::getOpenFileName(this, "选择", QDir::homePath());

    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    YLBusiness::sendFileRequest(m_friend.friendId(), file.fileName(), file.size(), m_friend.friendIsOnline());
}
