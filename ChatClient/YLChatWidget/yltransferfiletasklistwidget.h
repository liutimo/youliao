#ifndef YLTRANSFERFILETASKLISTWIDGET_H
#define YLTRANSFERFILETASKLISTWIDGET_H

#include <QWidget>
#include <QMap>
QT_BEGIN_NAMESPACE
class QProgressBar;
class QPushButton;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QScrollArea;
class YLSendFileWidget;
class YLReceiveFileWidget;
class QTimer;
QT_END_NAMESPACE

class YLTransferFileTaskListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YLTransferFileTaskListWidget(QWidget *parent = nullptr);
    ~YLTransferFileTaskListWidget();

    void initLayout();


    void addSendFile(const QString &taskId);
    void addRecvFile(const QString &taskId);
    void updateFileTransferProgressBar(const QString &taskId, uint32_t progress);
    void transferComplete(const QString &taskId);
    void cancelFileTransfer(const QString &taskId);
    void refuseFileTransfer(const QString &taskId);


    int count();
signals:
    void cancelSend(const QString &fileName, const QString &fileSize);
    void cancelRecv(const QString &fileName, const QString &fileSize);

private:
    QVBoxLayout *m_v_layout;
    QHBoxLayout *m_h_layout;
    QScrollArea *m_scroll_area;
    QWidget *m_widget;
    int     m_count;

    QMap<QString, YLSendFileWidget*>            m_file_send_map;
    QMap<QString, YLReceiveFileWidget*>         m_file_recv_map;
};

class YLSendFileWidget : public QWidget
{
    Q_OBJECT
    const QString qss_button = "QPushButton        {border:0px; color:#2D87E3;}"
                               "QPushButton:hover  {border:0px; color:#56A9CD;}"
                               "QPushButton:pressed{border:0px; color:#000;}";
public:
    explicit YLSendFileWidget(QWidget *parent = nullptr);
    ~YLSendFileWidget();
    void setTaskId(const QString &taskId);
    void updateProgressBar(uint32_t progress);

signals:
    void cancel(const QString &fileName, const QString &fileSize);


private:
    void init();

    QLabel *m_file_icon;
    QLabel *m_file_info;    //name + size
    QLabel *m_in_icon;
    QLabel *m_speed;
    QProgressBar *m_transfer_progress;
    QPushButton  *m_convert_button;
    QPushButton  *m_cancel;

    QString m_file_name;
    QString m_file_size;
    QString m_task_id;

    uint32_t m_start_time;
};

class YLReceiveFileWidget : public QWidget
{
    Q_OBJECT
    const QString qss_button = "QPushButton        {border:0px; color:#2D87E3;}"
                               "QPushButton:hover  {border:0px; color:#56A9CD;}"
                               "QPushButton:pressed{border:0px; color:#000;}";
public:
    explicit YLReceiveFileWidget(QWidget *parent = nullptr);
    void init();
    void setTaskId(const QString &taskId);
    void updateProgressBar(uint32_t progress);


signals:
    void cancel(const QString &fileName, const QString &fileSize);

private:
    QLabel *m_file_icon;
    QLabel *m_file_info;    //name + size
    QLabel *m_in_icon;
    QLabel *m_speed;
    QProgressBar *m_transfer_progress;
    QPushButton  *m_receive;
    QPushButton  *m_save_as;
    QPushButton  *m_cancel;

    QString m_file_name;
    QString m_file_size;
    QString m_task_id;

    QTimer *m_timer;        //用于计算实时网速
    uint32_t m_last_time_progress;
};

#endif // YLTRANSFERFILETASKLISTWIDGET_H
