#include "ylrecordaudiowidget.h"
#include <QTimer>
#include <QLabel>
#include <QPainter>
#include <QPushButton>
#include <QAudioInput>
#include <QAudioFormat>
#include <QDateTime>
#include <QProcess>
#include <QDir>

RecordAudio::RecordAudio(QObject *parent) : QObject(parent)
{
    initAudioInput();
}

void RecordAudio::initAudioInput()
{
    //[1]设置音频格式
    QAudioFormat format;
    format.setSampleRate(8000);                         //采样率
    format.setChannelCount(1);                          //单声道
    format.setSampleSize(8);                            //采样精度
    format.setCodec("audio/pcm");                       //格式
    format.setByteOrder(QAudioFormat::LittleEndian);    //字节序
    format.setSampleType(QAudioFormat::UnSignedInt);    //采样类型

    //[2]获取音频设备信息
    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    if (!info.isFormatSupported(format))
        format = info.nearestFormat(format);            //支持的最接近的format

    //[3] 初始化QAudioInput
    m_audio_input = new QAudioInput(format, this);
    connect(m_audio_input, &QAudioInput::stateChanged, this, [this](QAudio::State state){
        switch (state) {
                 case QAudio::StoppedState:
                     if (m_audio_input->error() != QAudio::NoError) {
                         // Error handling
                     } else {
                         // Finished recording
                     }
                     break;

                 case QAudio::ActiveState:
                     // Started recording - read from IO device
                     break;

                 default:
                     // ... other cases as appropriate
                     break;
             }
    });





}


void RecordAudio::startRecord()
{
    m_file_name = QString::number(QDateTime::currentDateTime().toTime_t()) + ".raw";
    m_file = new QFile(m_file_name);
    m_file->open( QIODevice::WriteOnly | QIODevice::Truncate );
    m_audio_input->start(m_file);
}

QString RecordAudio::stopRecording()
{
    m_audio_input->stop();
    m_file->close();
    delete m_file;
    m_file = nullptr;
    QString m_file_name_1 = QString::number(QDateTime::currentDateTime().toTime_t()) + ".amr";

    //转码
    QProcess p;
    p.start(QString("ffmpeg -f u8 -ar 8000 -ac 1 -acodec pcm_u8 -i %1 %2").arg(m_file_name).arg(m_file_name_1));
    p.waitForStarted();
    p.waitForFinished();

    //删除原文件
    QDir dir(QDir::currentPath());
    dir.remove(m_file_name);
    return m_file_name_1;
}

void RecordAudio::cancel()
{
    m_audio_input->stop();
    m_file->close();
    delete m_file;
    m_file = nullptr;

    //删除文件
    QDir dir(QDir::currentPath());
    dir.remove(m_file_name);
}

/**************************************************************************************************************************/

YLRecordAudioWidget::YLRecordAudioWidget(QWidget *parent) : QWidget(parent), m_current_color(false)
{
    m_current_times = 0;
    init();
}

void YLRecordAudioWidget::init()
{
    m_light_color   = QPixmap(":/res/YLCommonControl/Indicator_light_1.png").scaled(QSize(10, 10));
    m_deepin_color  = QPixmap(":/res/YLCommonControl/Indicator_light_2.png").scaled(QSize(10, 10));

    m_tip_light = new QLabel(this);
    m_tip_light->setFixedSize(10, 10);
    m_tip_light->move(10, 10);
    m_tip_light->setPixmap(m_light_color);

    m_tip_label = new QLabel("正在录音...", this);
    m_tip_label->setFixedHeight(20);
    m_tip_label->move(25, 5);
    m_tip_label->setAlignment(Qt::AlignVCenter);

    m_send_button = new QPushButton("发送", this);
    m_send_button->setFixedSize(64, 23);
    connect(m_send_button, &QPushButton::clicked, this, [this](){ emit send(); });

    m_cancel_button = new QPushButton("取消", this);
    m_cancel_button->setFixedSize(64, 23);
    connect(m_cancel_button, &QPushButton::clicked, this, [this](){ emit cancel(); });

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this](){
        if (m_current_color)
            m_tip_light->setPixmap(m_deepin_color);
        else
            m_tip_light->setPixmap(m_light_color);
        m_current_color = !m_current_color;
        if (m_current_times == 60)
        {
//            emit
            m_timer->stop();
            emit send();
        }

        ++m_current_times;
        update();
    });

    m_record_audio = new RecordAudio;
}


void YLRecordAudioWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    m_send_button->move(width() - 140, 3);
    m_cancel_button->move(width() - 70, 3);
}


void YLRecordAudioWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(223, 230, 236)); //DFE6EC
    p.drawRect(rect());

    p.setBrush(QColor::fromRgb(190, 232, 248));  //#BEE8F8
    p.drawRect(0, 0, (width() / 60 + 1)* m_current_times, height());
}


void YLRecordAudioWidget::start()
{
    if (!m_timer->isActive())
    {
        m_current_times = 0;
        m_timer->start(1000);
        m_record_audio->startRecord();
    }
}

QString YLRecordAudioWidget::stop()
{
    m_current_color = false;
    hide();
    m_timer->stop();
    return m_record_audio->stopRecording();
}


void YLRecordAudioWidget::cancelRecord()
{
    m_current_color = false;
    m_current_times = 0;
    hide();
    m_timer->stop();
    m_record_audio->cancel();
}
