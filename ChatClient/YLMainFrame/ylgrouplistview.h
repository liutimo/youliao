#ifndef YLGROUPLISTVIEW_H
#define YLGROUPLISTVIEW_H
#include <QListWidget>

QT_BEGIN_NAMESPACE
class YLFriendListItem;
class QListWidgetItem;
class QMenu;
QT_END_NAMESPACE
class YLGroupListView : public QListWidget
{
    Q_OBJECT
    const QString qss_this = "QListWidget#YLGroupListView{background:rgba(255, 255, 255, 200);}"
                             "QListWidget#YLGroupListView::item:hover    {background: rgba(200, 200, 200, 1.0);}"
                             "QListWidget#YLGroupListView::item:selected {background: rgba(217, 209, 206, 1.0);}";
    const QString qss_scroll_bar = "QScrollBar:vertical {border: 0px solid grey;background: transparent;width: 12px;margin: 12px 0 12px 0;}\
                                    QScrollBar::handle:vertical {border-radius:6px;background:gray;}\
                                    QScrollBar::add-line:vertical {border: 0px ; border-image: url(:/res/MainFrame/scrollbar_arrowdown_normal.png);height: 12px; subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_highlight.png);height: 12px;subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_down.png);height: 12px;subcontrol-position: bottom;ubcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical {border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_normal.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin; }\
                                    QScrollBar::sub-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_highlight.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_down.png);height: 12px;subcontrol-position: top;ubcontrol-origin: margin;}";

public:
    YLGroupListView(QWidget *parent = nullptr);

private:
    void initMenu();

protected:
    void mousePressEvent(QMouseEvent *event);

private:
    QMenu *m_menu;
};

#endif // YLGROUPLISTVIEW_H
