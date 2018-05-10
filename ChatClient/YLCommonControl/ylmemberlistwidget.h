#ifndef MEMBERLISTWIDGET_H
#define MEMBERLISTWIDGET_H
#include <QTableWidget>
QT_BEGIN_NAMESPACE
class QLabel;
class YLHeadFrame;
class MemberListWidgetItem;
QT_END_NAMESPACE

class MemberNameWidgetItem : public QWidget
{
    Q_OBJECT
public:
    typedef enum  { GROUPMANAGER = 1, GROUPOWER, GROUPMEMBER}MemberType;

    explicit MemberNameWidgetItem(QWidget *parent = nullptr);
    ~MemberNameWidgetItem();

    void setMemberType(MemberType type);
    void setMemberName(const QString &name);

private:
    void init();


private:
    YLHeadFrame *m_head_frame;
    QLabel *m_member_type;          //如果是管理员或者群主显示相应的图标
    QLabel *m_member_name;          //显示成员昵称
};

class YLMemberListWidget : public QTableWidget
{
    Q_OBJECT
    const QString qss_scroll_bar = "QScrollBar:vertical {border: 0px solid grey;background: transparent;width: 5px;margin: 12px 0 12px 0;}\
                                    QScrollBar::handle:vertical {border-radius:2px;background:gray;}\
                                    QScrollBar::add-line:vertical {border: 0px ; border-image: url(:/res/MainFrame/scrollbar_arrowdown_normal.png);height: 12px; subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_highlight.png);height: 12px;subcontrol-position: bottom;subcontrol-origin: margin;}\
                                    QScrollBar::add-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowdown_down.png);height: 12px;subcontrol-position: bottom;ubcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical {border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_normal.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin; }\
                                    QScrollBar::sub-line:vertical:hover{ border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_highlight.png);height: 12px;subcontrol-position: top;subcontrol-origin: margin;}\
                                    QScrollBar::sub-line:vertical:pressed{border: 0px ;border-image: url(:/res/MainFrame/scrollbar_arrowup_down.png);height: 12px;subcontrol-position: top;ubcontrol-origin: margin;}";

public:
    explicit YLMemberListWidget(QWidget *parent = nullptr);
    ~YLMemberListWidget();

    void setRow(const QString &name, MemberNameWidgetItem::MemberType type, const QString &groupNick, const QString &lastChatTime);

private:
    void setRowColor(int row, QColor color);

protected:
    void leaveEvent(QEvent *event);

public slots:
    void cellEntered(int,int);

private:
    QColor  m_last_row_color;                   //存储item之前的颜色，这里是透明的，默认设置为透明
    int     m_previous_color_row;               // 鼠标移动过的上一行的行号

};



#endif // MEMBERLISTWIDGET_H
