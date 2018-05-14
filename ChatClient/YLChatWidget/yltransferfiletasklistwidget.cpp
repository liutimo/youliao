#include "yltransferfiletasklistwidget.h"
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QPixmap>
#include <QScrollArea>
#include <QDebug>
#include <QVBoxLayout>
YLTransferFileTaskListWidget::YLTransferFileTaskListWidget(QWidget *parent) : QWidget(parent)
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


void YLTransferFileTaskListWidget::addSendFile(const QString &fileName, uint32_t fileSize)
{
    YLSendFileWidget *w = new YLSendFileWidget;
    w->setFileInfo(fileName, fileSize);
    m_v_layout->addWidget(w);
}

void YLTransferFileTaskListWidget::initLayout()
{
    m_v_layout = new QVBoxLayout;
    m_v_layout->setSizeConstraint(QLayout::SetFixedSize);
    m_v_layout->setMargin(0);

    m_h_layout = new QHBoxLayout;
    m_h_layout->setMargin(0);
}

/*********************YLSendFileWidget******************/
YLSendFileWidget::YLSendFileWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300, 75);
    init();
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

    m_file_info = new QLabel("赤裸裸.mp3 (5.4M)", this);
    QFont f = m_file_info->font();
    f.setPixelSize(10);
    m_file_info->setFont(f);
    m_file_info->move(50, 10);

    m_cancel = new QPushButton("取消", this);
    m_cancel->setFixedSize(35, 22);
    m_cancel->move(260, 50);
    m_cancel->setStyleSheet(qss_button);
    connect(m_cancel, &QPushButton::clicked, this, [this](){
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
    m_transfer_progress->setMaximum(100);
    m_transfer_progress->setValue(50);
    m_transfer_progress->setTextVisible(false);

    m_speed = new QLabel(this);
    m_speed->setText("800.09kb/s");
    m_speed->move(50, 50);
}

void YLSendFileWidget::setFileInfo(const QString &fileName, uint32_t fileSize)
{
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
    m_file_info->setText(QString("%1 (%2)").arg(fileName).arg(s));
}



/*******************YLReceiveFileWidget****************/
YLReceiveFileWidget::YLReceiveFileWidget(QWidget *parent) : QWidget(parent)
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

    m_file_info = new QLabel("赤裸裸.mp3 (5.4M)", this);
    QFont f = m_file_info->font();
    f.setPixelSize(10);
    m_file_info->setFont(f);
    m_file_info->move(50, 10);

    m_cancel = new QPushButton("取消", this);
    m_cancel->setFixedSize(35, 22);
    m_cancel->move(260, 50);
    m_cancel->setStyleSheet(qss_button);
    connect(m_cancel, &QPushButton::clicked, this, [this](){
        close();
    });
    m_receive = new QPushButton("接收", this);
    m_receive->setFixedSize(35, 22);
    m_receive->move(180, 50);
    m_receive->setStyleSheet(qss_button);

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
    m_speed->setText("800.09kb/s");
    m_speed->move(50, 50);
}
