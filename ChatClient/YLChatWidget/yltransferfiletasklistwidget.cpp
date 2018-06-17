#include "yltransferfiletasklistwidget.h"
#include <QLabel>
#include <QDebug>
#include <QPixmap>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QDateTime>
#include <QTimer>
#include <sys/time.h>
#include "YLFileTransfer/ylfiletransfermanager.h"
#include "YLFileTransfer/ylfiletransferthread.h"
YLTransferFileTaskListWidget::YLTransferFileTaskListWidget(QWidget *parent) : QWidget(parent), m_count(0)
{
    initLayout();
    m_scroll_area = new QScrollArea(this);
    m_scroll_area->setFixedWidth(300);
    m_widget = new QWidget(this);

    m_widget->setLayout(m_v_layout);

    m_scroll_area->setWidget(m_widget);

    m_h_layout->addWidget(m_scroll_area);
    setLayout(m_h_layout);
}

YLTransferFileTaskListWidget::~YLTransferFileTaskListWidget()
{
    qDebug() << "~YLTransferFileTaskListWidget()";
    delete m_v_layout;
    delete m_h_layout;
}


void YLTransferFileTaskListWidget::addSendFile(const QString &taskId)
{
    YLSendFileWidget *w = new YLSendFileWidget;
    w->setTaskId(taskId);
    m_v_layout->addWidget(w);
    ++m_count;

    m_file_send_map[taskId] = w;

    connect(w, &YLSendFileWidget::cancel, this, [this](const QString& fileName, const QString &fileSize){
        emit cancelSend(fileName, fileSize);
        auto key = m_file_send_map.key((YLSendFileWidget*)sender());
        m_file_send_map.remove(key);
        --m_count;
    });
}

void YLTransferFileTaskListWidget::updateFileTransferProgressBar(const QString &taskId, uint32_t progress)
{
    YLSendFileWidget *sendWidget = m_file_send_map[taskId];
    if (sendWidget)
    {
        sendWidget->updateProgressBar(progress);
        return;
    }

    YLReceiveFileWidget *recvWidget = m_file_recv_map[taskId];
    if (recvWidget)
    {
        recvWidget->updateProgressBar(progress);
        return;
    }

}


void YLTransferFileTaskListWidget::transferComplete(const QString &taskId)
{
    YLSendFileWidget *sendWidget = m_file_send_map[taskId];
    if (sendWidget)
    {
        sendWidget->close();
        return;
    }

    YLReceiveFileWidget *recvWidget = m_file_recv_map[taskId];
    if (recvWidget)
    {
        recvWidget->close();
        return;
    }
}


void YLTransferFileTaskListWidget::cancelFileTransfer(const QString &taskId)
{
    YLSendFileWidget *sendWidget = m_file_send_map[taskId];
    if (sendWidget)
    {
        sendWidget->close();
        return;
    }

    YLReceiveFileWidget *recvWidget = m_file_recv_map[taskId];
    if (recvWidget)
    {
        recvWidget->close();
        return;
    }
}

void YLTransferFileTaskListWidget::refuseFileTransfer(const QString &taskId)
{
    YLSendFileWidget *sendWidget = m_file_send_map[taskId];
    if (sendWidget)
    {
        sendWidget->close();
        return;
    }

    YLReceiveFileWidget *recvWidget = m_file_recv_map[taskId];
    if (recvWidget)
    {
        recvWidget->close();
        return;
    }
}

void YLTransferFileTaskListWidget::addRecvFile(const QString &taskId)
{
    YLReceiveFileWidget *w = new YLReceiveFileWidget;
    w->setTaskId(taskId);
    m_v_layout->addWidget(w);
    ++m_count;

    m_file_recv_map[taskId] = w;

    connect(w, &YLReceiveFileWidget::cancel, this, [this](const QString& fileName, const QString &fileSize){
        emit cancelRecv(fileName, fileSize);
        auto key = m_file_recv_map.key((YLReceiveFileWidget*)sender());
        m_file_recv_map.remove(key);
        --m_count;
    });
}


void YLTransferFileTaskListWidget::initLayout()
{
    m_v_layout = new QVBoxLayout;
    m_v_layout->setSizeConstraint(QLayout::SetFixedSize);
    m_v_layout->setMargin(0);

    m_h_layout = new QHBoxLayout;
    m_h_layout->setMargin(0);
}

int YLTransferFileTaskListWidget::count()
{
    return m_count;
}

/*********************YLSendFileWidget******************/
YLSendFileWidget::YLSendFileWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300, 75);
    init();

//    struct timeval tv;
//    gettimeofday(&tv,NULL);
//    m_start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    m_timer = new QTimer(this);
    m_timer->start(500);
    connect(m_timer, &QTimer::timeout, this, [this](){
        YLTransferFileEntity entity;
        if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(m_task_id.toStdString(), entity))
            return;

        uint32_t progress = entity.m_progress;

        //0.5s内接收
        double size = (progress - m_last_time_progress);
        m_last_time_progress = progress;
        size /= 0.5;

        QString s;
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

        m_speed->setText(s + "/s");
    });

}


YLSendFileWidget::~YLSendFileWidget()
{
    qDebug() << "~YLSendFileWidget()";
}

void YLSendFileWidget::init()
{
    m_file_icon = new QLabel(this);
    m_file_icon->setFixedSize(40, 40);
    m_file_icon->setPixmap(QPixmap(":/res/FileIcon/audio.png"));
    m_file_icon->move(5, 10);

    m_file_info = new QLabel(this);
    QFont f = m_file_info->font();
    f.setPixelSize(10);
    m_file_info->setFont(f);
    m_file_info->move(50, 10);

    m_cancel = new QPushButton("取消", this);
    m_cancel->setFixedSize(35, 22);
    m_cancel->move(260, 50);
    m_cancel->setStyleSheet(qss_button);
    connect(m_cancel, &QPushButton::clicked, this, [this](){
        YLTransferFileEntityManager::instance()->cancelFileTransfer(m_task_id.toStdString());
        emit cancel(m_file_name, m_file_size);
        close();
    });

    m_convert_button = new QPushButton("转为离线发送", this);
    m_convert_button->setFixedSize(70, 22);
    m_convert_button->move(180, 50);
    m_convert_button->setStyleSheet(qss_button);
    connect(m_convert_button, &QPushButton::clicked, this, [this](){
        if (m_convert_button->text() == "转为离线发送")
        {
            m_convert_button->setText("转为在线发送");
        }
        else
        {
            m_convert_button->setText("转为离线发送");
        }
    });

    m_transfer_progress = new QProgressBar(this);
    m_transfer_progress->setFixedSize(240, 5);
    m_transfer_progress->move(50, 35);
    m_transfer_progress->setTextVisible(false);

    m_speed = new QLabel(this);
    m_speed->setText("等待传输中...");
    m_speed->move(50, 50);
}

void YLSendFileWidget::setTaskId(const QString &taskId)
{
    m_task_id = taskId;

    YLTransferFileEntity entity;
    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId.toStdString(), entity))
        return;

    uint32_t fileSize = entity.m_file_size;
    m_file_name = entity.m_file_name.c_str();


    m_transfer_progress->setMaximum(fileSize);
    m_transfer_progress->setValue(0);

    QString s;
    if (fileSize < 1024)
    {
        s = QString::number(fileSize) + "Bytes";
    }
    else if (fileSize > 1024 && fileSize < 1024 * 1024)
    {
        s = QString::number(fileSize / 1024.0) + "KB";
    }
    else if (fileSize > 1024 * 1024 && fileSize < 1024 * 1024 * 1024)
    {
        s = QString::number(fileSize / 1024.0 / 1024.0) + "MB";
    }

    m_file_size = s;
    m_file_info->setText(QString("%1 (%2)").arg(m_file_name).arg(s));
}

void YLSendFileWidget::updateProgressBar(uint32_t progress)
{
    m_transfer_progress->setValue(progress);

//    struct timeval tv;
//    gettimeofday(&tv,NULL);
//    long long  currentTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
//    double speed = progress / ((currentTime - m_start_time) / 1000.0);
//    QString s;
//    if (speed < 1024)
//    {
//        s = QString::number(speed) + "Bytes";
//    }
//    else if (speed > 1024 && speed < 1024 * 1024)
//    {
//        s = QString::number(speed / 1024.0) + "KB";
//    }
//    else if (speed > 1024 * 1024 && speed < 1024 * 1024 * 1024)
//    {
//        s = QString::number(speed / 1024.0 / 1024.0) + "MB";
//    }

//    m_speed->setText(s + "/s");
}




/*******************YLReceiveFileWidget****************/
YLReceiveFileWidget::YLReceiveFileWidget(QWidget *parent) : QWidget(parent), m_last_time_progress(0)
{
    setFixedSize(300, 75);
    init();
}


void YLReceiveFileWidget::init()
{
    m_file_icon = new QLabel(this);
    m_file_icon->setFixedSize(40, 40);
    m_file_icon->setPixmap(QPixmap(":/res/FileIcon/audio.png"));
    m_file_icon->move(5, 10);

    m_file_info = new QLabel(this);
    QFont f = m_file_info->font();
    f.setPixelSize(10);
    m_file_info->setFont(f);
    m_file_info->move(50, 10);

    m_cancel = new QPushButton("取消", this);
    m_cancel->setFixedSize(35, 22);
    m_cancel->move(260, 50);
    m_cancel->setStyleSheet(qss_button);
    connect(m_cancel, &QPushButton::clicked, this, [this](){
        m_timer->stop();
        emit cancel(m_file_name, m_file_size);
        YLTransferFileEntityManager::instance()->cancelFileTransfer(m_task_id.toStdString());
        close();
    });
    m_receive = new QPushButton("接收", this);
    m_receive->setFixedSize(35, 22);
    m_receive->move(180, 50);
    m_receive->setStyleSheet(qss_button);
    connect(m_receive, &QPushButton::clicked, this, [this]()
    {
        m_receive->hide();
        m_save_as->hide();
        YLTransferFileEntityManager::instance()->acceptFileTransfer(m_task_id.toStdString());
        m_timer->start(500);
    });

    m_save_as = new QPushButton("另存为", this);
    m_save_as->setFixedSize(35, 22);
    m_save_as->move(220, 50);
    m_save_as->setStyleSheet(qss_button);

    m_transfer_progress = new QProgressBar(this);
    m_transfer_progress->setFixedSize(240, 5);
    m_transfer_progress->move(50, 35);
    m_transfer_progress->setMaximum(100);
    m_transfer_progress->setValue(50);
    m_transfer_progress->setTextVisible(false);

    m_speed = new QLabel(this);
    m_speed->setText("等待传输中...");
    m_speed->move(50, 50);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        YLTransferFileEntity entity;
        if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(m_task_id.toStdString(), entity))
            return;

        uint32_t progress = entity.m_progress;

        //0.5s内接收
        double size = (progress - m_last_time_progress);
        m_last_time_progress = progress;
        size /= 0.5;

        QString s;
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

        m_speed->setText(s + "/s");
    });

}

void YLReceiveFileWidget::setTaskId(const QString &taskId)
{
    m_task_id = taskId;

    YLTransferFileEntity entity;
    if (!YLTransferFileEntityManager::instance()->getFileInfoByTaskId(taskId.toStdString(), entity))
        return;

    uint32_t fileSize = entity.m_file_size;
    m_file_name = entity.m_file_name.c_str();

    m_transfer_progress->setMaximum(fileSize);
    m_transfer_progress->setValue(0);

    QString s;
    if (fileSize < 1024)
    {
        s = QString::number(fileSize) + "Bytes";
    }
    else if (fileSize > 1024 && fileSize < 1024 * 1024)
    {
        s = QString::number(fileSize / 1024.0) + "KB";
    }
    else if (fileSize > 1024 * 1024 && fileSize < 1024 * 1024 * 1024)
    {
        s = QString::number(fileSize / 1024.0 / 1024.0) + "MB";
    }
    m_file_size = s;
    m_file_info->setText(QString("%1 (%2)").arg(m_file_name).arg(s));
}


void YLReceiveFileWidget::updateProgressBar(uint32_t progress)
{
    m_transfer_progress->setValue(progress);
}
