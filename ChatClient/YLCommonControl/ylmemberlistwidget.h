#ifndef MEMBERLISTWIDGET_H
#define MEMBERLISTWIDGET_H
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "protobuf/youliao.base.pb.h"
#include "YLEntityObject/ylgroup.h"
#include "YLCommonControl/ylmessagebox.h"
#include "YLNetWork/ylbusiness.h"
using namespace youliao::pdu;
QT_BEGIN_NAMESPACE
class QLabel;
class YLHeadFrame;
class MemberListWidgetItem;
class YLLineEdit;
class ButtonGroup;
QT_END_NAMESPACE


/**
 * @brief The MemberNameWidgetItem class
 * 用于群信息界面中的成员列表
 */
class MemberNameWidgetItem : public QWidget
{
    Q_OBJECT
public:
    typedef enum  { GROUPMANAGER = 1, GROUPOWER, GROUPMEMBER}MemberType;

    explicit MemberNameWidgetItem(QWidget *parent = nullptr);
    ~MemberNameWidgetItem();

    void setMemberType(MemberType type);
    void setMemberName(const QString &name);
    void setHeader(const QString &);
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
    void setGroup(const YLGroup &group);
    ~YLMemberListWidget();

    void setHeader();
    void setRow(const base::MemberInfo &memberInfo, MemberNameWidgetItem::MemberType type);         //新增行

    void modifyGroupCard();

private:
    void setRowColor(int row, QColor color);

protected:
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void cellEntered(int,int);

signals:
    void groupCardChanged(uint32_t memberId, QString groupCard);

private:
    QColor  m_last_row_color;                   //存储item之前的颜色，这里是透明的，默认设置为透明
    int     m_previous_color_row;               // 鼠标移动过的上一行的行号
    YLLineEdit *m_line_edit;

    YLGroup m_group;
    QMap<uint32_t /*id*/, uint32_t /*row*/> m_row_id;          //id和row的映射

    bool m_is_group_creator;
    bool m_is_group_manager;
};

class ButtonGroup : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonGroup(QWidget *parent = nullptr)
    {
        setFixedSize(300, 30);

        m_set_manager = new QPushButton(this);
        m_set_manager->setToolTip("设置为管理员");
        m_set_manager->setFixedSize(16, 16);
        m_set_manager->move(125, 7);
        m_set_manager->setStyleSheet("QPushButton{border-image:url(:/res/YLCommonControl/set.png);}"
                                     "QPushButton:hover{border-image:url(:/res/YLCommonControl/set_hover.png);}"
                                     "QPushButton:pressed{border-image:url(:/res/YLCommonControl/set_pressed.png);}");

        m_kick_out = new QPushButton(this);
        m_kick_out->setToolTip("从本群中移出");
        m_kick_out->setFixedSize(16, 16);
        m_kick_out->move(148, 7);
        m_kick_out->setStyleSheet("QPushButton{border-image:url(:/res/YLCommonControl/remove.png);}"
                                  "QPushButton:hover{border-image:url(:/res/YLCommonControl/remove_hover.png);}"
                                  "QPushButton:pressed{border-image:url(:/res/YLCommonControl/remove_pressed.png);}");

        connect(m_kick_out, &QPushButton::clicked, this, [this](){
            YLMessageBox *messageBox = new YLMessageBox(BUTTON_OK | BUTTON_CANNEL, this);
            messageBox->setToolTip(QString("你确定将%1(%2)从本群中移除吗？"));
            messageBox->setWidgetTitle("提示");
            messageBox->setTipType(YLMessageBox::Tips);
            BottonResult res =  messageBox->exec();
            if (res == BUTTON_OK)
            {
                YLBusiness::kickOutGroupMember(m_group_id, m_user_id);
            }
        });

        connect(m_set_manager, &QPushButton::clicked, this, [this](){
            YLMessageBox *messageBox = new YLMessageBox(BUTTON_OK | BUTTON_CANNEL, this);
            messageBox->setToolTip(QString("确定要设置%1(%2)为管理员吗？"));
            messageBox->setWidgetTitle("提示");
            messageBox->setTipType(YLMessageBox::Tips);
            BottonResult res =  messageBox->exec();
            if (res == BUTTON_OK)
            {
                YLBusiness::setGroupManager(m_group_id, m_user_id);
            }
        });
    }

    void hideSet()
    {
        m_set_manager->hide();
        m_kick_out->move(125, 7);
    }

    void setUserId(const uint32_t userId) { m_user_id = userId; }
    void setGroupId(const uint32_t groupId) { m_group_id = groupId; }

private:
    QPushButton *m_set_manager;
    QPushButton *m_kick_out;

    uint32_t m_user_id;
    uint32_t m_group_id;
};


#endif // MEMBERLISTWIDGET_H
