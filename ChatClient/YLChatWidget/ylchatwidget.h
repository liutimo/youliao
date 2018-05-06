#ifndef YLCHATWIDGET_H
#define YLCHATWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"
#include "YLEntityObject/ylfriend.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class YLQuickBar;
class YLMessageView;
class YLMessageEditWidget;
class YLRightPanel;
QT_END_NAMESPACE

class YLChatWidget : public YLBasicWidget
{
    Q_OBJECT
    const QString m_qss_min_button = "  QPushButton#min_button        {border-image:url(:/res/MainFrame/sysbtn_min_normal.png);}\
                                        QPushButton#min_button:hover  {border-image:url(:/res/MainFrame/sysbtn_min_hover.png);}\
                                        QPushButton#min_button:pressed{border-image:url(:/res/MainFrame/sysbtn_min_down.png);}\
                                         ";

    const QString m_qss_max_button = "  QPushButton#max_button        {border-image:url(:/res/YLChatWidget/sysbtn_max_normal.png);}\
                                        QPushButton#max_button:hover  {border-image:url(:/res/YLChatWidget/sysbtn_max_hover.png);}\
                                        QPushButton#max_button:pressed{border-image:url(:/res/YLChatWidget/sysbtn_max_down.png);}\
                                        ";
    const QString qss_scroll_bar = "QScrollBar:vertical {border: 0px solid grey;background: transparent;width: 12px;margin: 12px 0 12px 0;}\
                                    QScrollBar::handle:vertical {border-radius:6px;background:gray;}\
                                    QScrollBar::add-line:vertical {border: 0px ; border-image: url(:/res/MainFrame/scrollbar_arrowdown_normal.png);height: 12px; subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_highlight.png);height: 12px;subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_down.png);height: 12px;subcontrol-position: bottom;ubcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical {border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_normal.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin; }\
                                    QScrollBar::sub-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_highlight.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_down.png);height: 12px;subcontrol-position: top;ubcontrol-origin: margin;}";

    const QString qss_split_button_left =    "QPushButton        {border-image:url(:/res/YLChatWidget/aio_splitbutton_left_normal.png);}\
                                                QPushButton:hover  {border-image:url(:/res/YLChatWidget/aio_splitbutton_left_hover.png);}\
                                                QPushButton:pressed{border-image:url(:/res/YLChatWidget/aio_splitbutton_left_down.png);}\
                                                ";
    const QString qss_split_button_right =    "QPushButton        {border-image:url(:/res/YLChatWidget/aio_splitbutton_right_normal.png);}\
                                                 QPushButton:hover  {border-image:url(:/res/YLChatWidget/aio_splitbutton_right_hover.png);}\
                                                 QPushButton:pressed{border-image:url(:/res/YLChatWidget/aio_splitbutton_right_down.png);}\
                                                 ";
public:
    explicit YLChatWidget(QWidget *parent = Q_NULLPTR);
    ~YLChatWidget();
    void setFriend(const YLFriend &);
signals:
    void updateSession(YLFriend &ylFriend);
    void loadFinish();
protected:
    void resizeEvent(QResizeEvent *e);
    void closeEvent(QCloseEvent *event);

public slots:
    void receiveMessage(uint32_t user_id, const QString &message);

private slots:
    void max();
    void min();
    void sendMessage();

private:
    void initTitleBar();
    void initRight();
    void initView();
    void updatePosition();
    void updateSize();

private:
    QPushButton *m_max_button;
    QPushButton *m_min_button;
    QPushButton *m_nickname_button;

    YLQuickBar          *m_quick_bar;
    YLRightPanel        *m_ritht_panel;
    YLMessageView       *m_message_view;
    YLMessageEditWidget *m_message_edit_widget;

    QPushButton *m_send_button;
    QPushButton *m_close_button;

    YLFriend m_friend;

    QString m_friend_header_path;

    QPushButton *m_split_button;
    bool m_hide;

    int m_scale_width;
};

#endif // YLCHATWIDGET_H
