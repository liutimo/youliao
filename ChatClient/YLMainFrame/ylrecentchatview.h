#ifndef YLRECENTCHATVIEW_H
#define YLRECENTCHATVIEW_H

#include <QListWidget>
#include "YLEntityObject/ylfriend.h"
#include "YLEntityObject/ylsession.h"

class YLFriendListItem;
class QListWidgetItem;
class YLRecentChatView : public QListWidget
{
    Q_OBJECT
    const QString qss_this = "QListWidget#YLRecentChatView{background:rgba(255, 255, 255, 200);}"
                             "QListWidget#YLRecentChatView::item:hover    {background: rgba(200, 200, 200, 1.0);}"
                             "QListWidget#YLRecentChatView::item:selected {background: rgba(217, 209, 206, 1.0);}";
    const QString qss_scroll_bar = "QScrollBar:vertical {border: 0px solid grey;background: transparent;width: 12px;margin: 12px 0 12px 0;}\
                                    QScrollBar::handle:vertical {border-radius:6px;background:gray;}\
                                    QScrollBar::add-line:vertical {border: 0px ; border-image: url(:/res/MainFrame/scrollbar_arrowdown_normal.png);height: 12px; subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_highlight.png);height: 12px;subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_down.png);height: 12px;subcontrol-position: bottom;ubcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical {border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_normal.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin; }\
                                    QScrollBar::sub-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_highlight.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_down.png);height: 12px;subcontrol-position: top;ubcontrol-origin: margin;}";

public:
    YLRecentChatView(QWidget *parent = nullptr);
    void addItem(const YLSession&);
    void updateList();

protected:
    void mousePressEvent(QMouseEvent *event);


private slots:
    void on_move_to_top  (YLSession &);
    void on_del_from_list(const YLSession &);
    void newSession();
    void readComplete(uint32_t sessionId);
private:
    void add(const YLSession&, int pos = 0);

//    QList<YLSession> m_data;
//    QList<YLSession> m_top_data;
};

#endif // YLRECENTCHATVIEW_H
