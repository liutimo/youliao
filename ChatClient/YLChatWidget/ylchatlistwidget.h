#ifndef YLCHATLISTWIDGET_H
#define YLCHATLISTWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"
#include "YLEntityObject/ylfriend.h"
#include "YLEntityObject/ylgroup.h"
#include <QMap>

QT_BEGIN_NAMESPACE
class YLSearchLineEdit;
class YLSingleChatWidget;
class QPushButton;
class QSplitter;
QT_END_NAMESPACE

/**
 * @brief The YLChatListWidget class
 * 模仿QQ的TabWidget.当聊天窗口大于两个时,将他们合并为一个窗口
 * 左边为listView 右边为聊天窗口
 */
class YLChatListWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLChatListWidget(QWidget *parent = nullptr);
    void setName(const QString &name);
signals:

protected:
    void paintEvent(QPaintEvent *event);

private:
    YLSearchLineEdit    *m_search_lineedit;
    YLSingleChatWidget  *m_signle_chat_widget;
    QSplitter *p;
    QPushButton         *m_name;            //显示用户名或者群组名

};

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class ChildWidgetItem;
QT_END_NAMESPACE

/**
 * @brief The LeftChildWidget class
 * 左边的子窗口
 * 由listView和搜索框组成
 */
class LeftChildWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LeftChildWidget(QWidget *parent = nullptr);
    virtual ~LeftChildWidget();
private:
    void init();

protected:
    void resizeEvent(QResizeEvent *event);
signals:
    void leftItemChanged(const QString);
private:
    QVBoxLayout                 *m_vertical_layout;
    int                         m_current_selected_id;
    QMap<int, ChildWidgetItem*> m_child_items;
};

QT_BEGIN_NAMESPACE
class YLHeadFrame;
class QLabel;
class QGridLayout;
QT_END_NAMESPACE

/**
 * @brief The ChildWidgetItem class
 * 左边窗口 列表子item
 */
class ChildWidgetItem : public QWidget
{
    Q_OBJECT
    const QString m_qss_close_btn  = "  QPushButton        {border-image:url(:/res/YLChatWidget/page_close_btn_normal.png);}\
                                        QPushButton:hover  {border-image:url(:/res/YLChatWidget/page_close_btn_hover.png);}\
                                        QPushButton:pressed{border-image:url(:/res/YLChatWidget/page_close_btn_click.png);}\
                                        ";
public:
    typedef enum {FRIEND = 0, GROUP} ItemType;
    explicit ChildWidgetItem(QWidget *parent = nullptr);
    virtual ~ChildWidgetItem();

    void setId(int id) { m_id = id; }
    void setSelected(bool flag = true) { m_selected = flag; update();}

    int id() const { return m_id; }
    bool isSelected() const { return m_selected; }

    void setFriend(const YLFriend &);
    void setGroup (const YLGroup &);

    /**
     * @brief setName
     * @param name
     * 测试函数  需要删除
     */
    void setName(const QString &name);

    /**
     * @brief getName
     * @return
     * 测试函数  需要删除
     */
    QString getName() const;

    ItemType getItemType();
signals:
    void selectedId(int);

private:
    void init();

protected:
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void leaveEvent(QEvent *event);
    void enterEvent(QEvent *event);

private:
    YLHeadFrame     *m_head_frame;
    QLabel          *m_name;            //显示群组名或者好友名
    QLabel          *m_latest_msg;      //显示最新一条消息的内容
    QLabel          *m_latest_time;      //显示最新一条消息的接收时间
    QGridLayout     *m_grid_layout;     //布局
    QPushButton     *m_close_button;    //关闭按钮
    int             m_index;            //resizeEvent使用，减少操作次数
    bool            m_hover;            //鼠标进入
    bool            m_selected;         //被选中
    int             m_id;               //id
    YLFriend        m_friend;
    YLGroup         m_group;
};

#endif // YLCHATLISTWIDGET_H
