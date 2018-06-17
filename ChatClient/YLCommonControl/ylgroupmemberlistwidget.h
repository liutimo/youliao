#ifndef YLGROUPMEMBERLISTWIDGET_H
#define YLGROUPMEMBERLISTWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "YLEntityObject/ylgroupmember.h"
QT_BEGIN_NAMESPACE
class QListWidget;
class QLineEdit;
class QVBoxLayout;
class QLabel;
class YLHeadFrame;
QT_END_NAMESPACE
class Button : public QPushButton
{
    Q_OBJECT
    //按下去的stylesheet
    const QString qss_btn_down = "QPushButton        {border-image:url(:/res/YLChatWidget/SearchIcon_down.png);}\
                                  QPushButton:hover  {border-image:url(:/res/YLChatWidget/SearchIcon_down.png);}\
                                  QPushButton:pressed{border-image:url(:/res/YLChatWidget/SearchIcon_down.png);}\
                                  ";

    const QString qss_btn = "QPushButton        {border-image:url(:/res/YLChatWidget/SearchIcon_normal.png);}\
                             QPushButton:hover  {border-image:url(:/res/YLChatWidget/SearchIcon_hover.png);}\
                             QPushButton:pressed{border-image:url(:/res/YLChatWidget/SearchIcon_down.png);}\
                            ";
public:
    Button(QWidget *parent = nullptr) : QPushButton(parent), m_clicked(false)
    {
        setStyleSheet("text-align:left;border:0px;");
        m_search_button = new QPushButton(this);
        m_search_button->setFixedSize(16, 16);
        m_search_button->setStyleSheet(qss_btn);

        connect(m_search_button, &QPushButton::clicked, this, [this](){
            if (m_clicked)
            {
                m_search_button->setStyleSheet(qss_btn);
                emit isShow(false);
            }
            else
            {
                m_search_button->setStyleSheet(qss_btn_down);
                emit isShow(true);
            }
            m_clicked = !m_clicked;
        });
    }
signals:
    void isShow(bool);
protected:
    void resizeEvent(QResizeEvent *event)
    {
        m_search_button->move(width() - 26, height() / 2 - 8);
    }

private:
    QPushButton     *m_search_button;
    bool             m_clicked;
};

/**
 * @brief The MemberNameWidgetItem class
 * 用于群信息界面中的成员列表
 */
class MemberWidgetItem : public QWidget
{
    Q_OBJECT
public:
    typedef enum  { GROUPMANAGER = 1, GROUPOWER, GROUPMEMBER}MemberType;

    explicit MemberWidgetItem(QWidget *parent = nullptr);
    ~MemberWidgetItem();

    void setMember(const YLGroupMember &member);

private:
    void init();
    void setMemberType(MemberType type);
    void setMemberName(const QString &name);

private:
    YLHeadFrame     *m_head_frame;
    QLabel          *m_member_type;          //如果是管理员或者群主显示相应的图标
    QLabel          *m_member_name;          //显示成员昵称
    YLGroupMember   m_member;
};


class YLGroupMemberListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit YLGroupMemberListWidget(QWidget *parent = nullptr);
    void addRow(const YLGroupMember &member);
private:
    Button      *m_button;
    QLineEdit   *m_line_edit;
    QListWidget *m_list_widget;
    QVBoxLayout *m_v_ayout;
};

#endif // YLGROUPMEMBERLISTWIDGET_H
