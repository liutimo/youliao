#ifndef YLRECORDAUDIOWIDGET_H
#define YLRECORDAUDIOWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QFile>

QT_BEGIN_NAMESPACE
class QAudioInput;
QT_END_NAMESPACE

class RecordAudio : public QObject
{
    Q_OBJECT
public:
    explicit RecordAudio(QObject *parent = nullptr);

    void cancel();
    void startRecord();
    QString stopRecording();

private:
    void initAudioInput();
    QFile *m_file;
    QAudioInput *m_audio_input;
    QString m_file_name;
};

QT_BEGIN_NAMESPACE
class QTimer;
class QPushButton;
class QLabel;
QT_END_NAMESPACE

class YLRecordAudioWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YLRecordAudioWidget(QWidget *parent = nullptr);
    void start();
    QString stop();
    void cancelRecord();
    uint32_t getTime() { return m_current_times; }
private:
    void init();

signals:
    void cancel();
    void send();

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);

private:
    quint32     m_current_times;            //每秒+1

    QTimer      *m_timer;                   //每一秒触发一次
    QLabel      *m_tip_label;
    QLabel      *m_tip_light;              //指示灯
    QPushButton *m_send_button;
    QPushButton *m_cancel_button;

    QPixmap m_light_color;
    QPixmap m_deepin_color;
    bool    m_current_color;            //记录当前颜色类型

    RecordAudio *m_record_audio;
};


#endif // YLRECORDAUDIOWIDGET_H
