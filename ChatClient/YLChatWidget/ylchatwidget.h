#ifndef YLCHATWIDGET_H
#define YLCHATWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"


class QPushButton;
class YLQuickBar;
class YLMessageView;
class YLMessageEditWidget;

class YLChatWidget : public YLBasicWidget
{
    Q_OBJECT
    const QString m_qss_min_button = "  QPushButton#m_min_button        {border-image:url(:/res/MainFrame/sysbtn_min_normal.png);}\
                                        QPushButton#m_min_button:hover  {border-image:url(:/res/MainFrame/sysbtn_min_hover.png);}\
                                        QPushButton#m_min_button:pressed{border-image:url(:/res/MainFrame/sysbtn_min_down.png);}\
                                         ";

    const QString m_qss_max_button = "  QPushButton#m_max_button        {border-image:url(:/res/YLChatWidget/sysbtn_max_normal.png);}\
                                        QPushButton#m_max_button:hover  {border-image:url(:/res/YLChatWidget/sysbtn_max_hover.png);}\
                                        QPushButton#m_max_button:pressed{border-image:url(:/res/YLChatWidget/sysbtn_max_down.png);}\
                                        ";
public:
    explicit YLChatWidget(QWidget *parent = Q_NULLPTR);


protected:
    void resizeEvent(QResizeEvent *e);

private slots:
    void max();
    void min();

private:
    void initTitleBar();
    void initView();
    void updatePosition();
    void updateSize();

private:
    QPushButton *m_max_button;
    QPushButton *m_min_button;

    YLQuickBar          *m_quick_bar;
    YLMessageView       *m_message_view;
    YLMessageEditWidget *m_message_edit_widget;
};

#endif // YLCHATWIDGET_H
