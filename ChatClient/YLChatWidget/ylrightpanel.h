#ifndef YLFILEWIDGET_H
#define YLFILEWIDGET_H

#include <QWidget>
QT_BEGIN_NAMESPACE
class QTabWidget;
class QHBoxLayout;
QT_END_NAMESPACE
class YLRightPanel : public QWidget
{
    Q_OBJECT
    const QString qss_tab_bar = "QTabBar::close-button         {image: url(:/res/YLChatWidget/sidebar_tabbutton_close_normal.png) subcontrol-position: right;}"
                                "QTabBar::close-button:hover   {image: url(:/res/YLChatWidget/sidebar_tabbutton_close_hover.png)}"
                                "QTabBar::close-button:pressed {image: url(:/res/YLChatWidget/sidebar_tabbutton_close_down.png)}";

public:
    explicit YLRightPanel(QWidget *parent = nullptr);
    ~YLRightPanel();
signals:

protected:
    void paintEvent(QPaintEvent *event);

private:
    QTabWidget *m_tab_widget;
    QHBoxLayout *hLayout;
};

#endif // YLFILEWIDGET_H
