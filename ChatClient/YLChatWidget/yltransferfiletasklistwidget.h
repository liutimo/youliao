#ifndef YLTRANSFERFILETASKLISTWIDGET_H
#define YLTRANSFERFILETASKLISTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QProgressBar;
class QPushButton;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;
class QScrollArea;
QT_END_NAMESPACE

class YLTransferFileTaskListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YLTransferFileTaskListWidget(QWidget *parent = nullptr);
    ~YLTransferFileTaskListWidget();

    void initLayout();
    void addSendFile(const QString &fileName, uint32_t fileSize);
private:
    QVBoxLayout *m_v_layout;
    QHBoxLayout *m_h_layout;
    QScrollArea *m_scroll_area;
    QWidget *m_widget;
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
    void setFileInfo(const QString &fileName, uint32_t fileSize);

private:
    void init();

    QLabel *m_file_icon;
    QLabel *m_file_info;    //name + size
    QLabel *m_in_icon;
    QLabel *m_speed;
    QProgressBar *m_transfer_progress;
    QPushButton  *m_convert_button;
    QPushButton  *m_cancel;
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

private:
    QLabel *m_file_icon;
    QLabel *m_file_info;    //name + size
    QLabel *m_in_icon;
    QLabel *m_speed;
    QProgressBar *m_transfer_progress;
    QPushButton  *m_receive;
    QPushButton  *m_save_as;
    QPushButton  *m_cancel;
};

#endif // YLTRANSFERFILETASKLISTWIDGET_H
