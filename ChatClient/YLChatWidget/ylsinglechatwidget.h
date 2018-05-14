#ifndef YLSINGLECHATWIDGET_H
#define YLSINGLECHATWIDGET_H

#include <QWidget>
#include "YLEntityObject/ylfriend.h"
QT_BEGIN_NAMESPACE
class QLabel;
class YLMessageView;
class QPushButton;
class YLMessageEditWidget;
class YLButton;
class YLTransferFileTaskListWidget;
QT_END_NAMESPACE

class YLSingleChatWidget : public QWidget
{
    Q_OBJECT
    const QString qss_split_button_left =  "QPushButton        {border-image:url(:/res/YLChatWidget/aio_splitbutton_left_normal.png);}\
                                            QPushButton:hover  {border-image:url(:/res/YLChatWidget/aio_splitbutton_left_hover.png);}\
                                            QPushButton:pressed{border-image:url(:/res/YLChatWidget/aio_splitbutton_left_down.png);}\
                                            ";
    const QString qss_split_button_right = "QPushButton        {border-image:url(:/res/YLChatWidget/aio_splitbutton_right_normal.png);}\
                                            QPushButton:hover  {border-image:url(:/res/YLChatWidget/aio_splitbutton_right_hover.png);}\
                                            QPushButton:pressed{border-image:url(:/res/YLChatWidget/aio_splitbutton_right_down.png);}\
                                            ";
public:
    explicit YLSingleChatWidget(QWidget *parent = nullptr);
    ~YLSingleChatWidget();
    void setFriend(const YLFriend &fri);

signals:
    void loadFinish();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void init();
    void initMidToolBar();
    void initRight();
    void updateSizeAndPosition();

public slots:
    void receiveMessage(uint32_t user_id, const QString &message);


private slots:
    void showEmotionWidget();
    void sendMessage();
    void selectFile();
    void spliteButtonClicked();
private:
    QLabel                  *m_label;           //top bar
    QLabel                  *m_label2;          //mid bar

    //mid tool bar
    YLButton                *m_emotion;
    YLButton                *m_gif;
    YLButton                *m_cut;
    YLButton                *m_file;
    YLButton                *m_image;
    YLButton                *m_more;
    YLButton                *m_msg_record;

    YLMessageView           *m_message_view;
    YLMessageEditWidget     *m_message_edit_widget;
    QPushButton             *m_send_button;
    QPushButton             *m_close_button;

    YLFriend                 m_friend;
    QString                  m_friend_header_path;

    QWidget                 *m_mid_toolbar;

    //文件传输相关
    YLTransferFileTaskListWidget    *m_transfer_file_widget;
    QPushButton                     *m_split_button;
    bool                            m_hide;
    int                             m_scale_width;  //仅在右边隐藏时使用，用于计算左边部分的新宽度或位置
};

#endif // YLSINGLECHATWIDGET_H
