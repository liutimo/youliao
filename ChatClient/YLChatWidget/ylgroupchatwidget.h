#ifndef YLGROUPCHATWIDGET_H
#define YLGROUPCHATWIDGET_H


#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class YLMessageView;
class QPushButton;
class YLMessageEditWidget;
class QToolButton;
class YLGroupNoticeWidget;
class YLGroupMemberListWidget;
QT_END_NAMESPACE

class YLGroupChatWidget : public QWidget
{
    Q_OBJECT
    const QString qss_selected = "QToolButton{background:rgba(255, 255, 255, 0);border:0px;border-bottom:2px solid #009BDB;color:gray;color:black;font: 20px solid 黑体;}"
                                 "QToolButton:hover{background:rgba(255, 255, 255, 0);border:0px;border-bottom:2px solid #009BDB; color:black;font: 20px solid 黑体;}";

    const QString qss_no_selected = "QToolButton{background:rgba(255, 255, 255, 0);border:0px;color:black;font: 20px solid 黑体;}"
                                    "QToolButton:hover{background:rgba(255, 255, 255, 0);border:0px;color:black;font: 20px solid 黑体;}";

    const QString qss_split_button_left =      "QPushButton        {border-image:url(:/res/YLChatWidget/aio_splitbutton_left_normal.png);}\
                                                QPushButton:hover  {border-image:url(:/res/YLChatWidget/aio_splitbutton_left_hover.png);}\
                                                QPushButton:pressed{border-image:url(:/res/YLChatWidget/aio_splitbutton_left_down.png);}\
                                                ";
    const QString qss_split_button_right =      "QPushButton        {border-image:url(:/res/YLChatWidget/aio_splitbutton_right_normal.png);}\
                                                 QPushButton:hover  {border-image:url(:/res/YLChatWidget/aio_splitbutton_right_hover.png);}\
                                                 QPushButton:pressed{border-image:url(:/res/YLChatWidget/aio_splitbutton_right_down.png);}\
                                                 ";
public:
    explicit YLGroupChatWidget(QWidget *parent = nullptr);

signals:

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    void initTop();
    void init();
    void initLeft();
    void updateSizeAndPosition();
private slots:
    void navigationClicked();
    void spliteButtonClicked();
private:
    QLabel                  *m_label;           //top bar
    QLabel                  *m_label2;          //mid bar
    YLMessageView           *m_meesage_view;
    YLMessageEditWidget     *m_meesage_edit_widget;
    QPushButton             *m_send_button;
    QPushButton             *m_close_button;
    QPushButton             *m_split_button;
    bool                     m_hide;
    //导航栏按钮
    QToolButton *m_chat;
    QToolButton *m_notice;
    QToolButton *m_file;
    QToolButton *m_setting;

    //通知栏
    YLGroupNoticeWidget *m_notice_widget;
    //成员列表
    YLGroupMemberListWidget *m_member_list_widget;

    int         m_scale_width;  //仅在右边隐藏时使用，用于计算左边部分的新宽度或位置
};

#endif // YLGROUPCHATWIDGET_H
