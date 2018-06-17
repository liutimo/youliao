#include "ylgroupmemberlistwidget.h"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QListWidget>
#include "ylheadframe.h"


MemberWidgetItem::MemberWidgetItem(QWidget *parent) : QWidget(parent)
{
    setFixedSize(200, 30);
    init();
}

MemberWidgetItem::~MemberWidgetItem()
{

}

void MemberWidgetItem::init()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(25, 25);
    m_head_frame->move(22, 2);

    m_member_type = new QLabel(this);
    m_member_type->setFixedSize(16, 16);
    m_member_type->move(200 - 18, 7);

    m_member_name = new QLabel(this);
    m_member_name->setFixedSize(130, 20);
    m_member_name->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    setMemberName("我是谁的某2某12345");
    m_member_name->move(50, 5);
}


void MemberWidgetItem::setMember(const YLGroupMember &member)
{
    m_member = member;

    m_head_frame->setHeadFromUrl(m_member.getMemberHeader());
    setMemberName(m_member.getGroupCard().isEmpty() ? m_member.getMemberNick() : m_member.getGroupCard());

    setMemberType((MemberType)m_member.getMemberType());
}

void MemberWidgetItem::setMemberType(MemberType type)
{
    if (type == GROUPMANAGER)
    {
        m_member_type->setPixmap(QPixmap(":/res/MainFrame/trad_girl.png"));
    }
    else if (type == GROUPOWER)
    {
        m_member_type->setPixmap(QPixmap(":/res/MainFrame/trad_boy.png"));
    }
}


void MemberWidgetItem::setMemberName(const QString &name)
{
    //校验昵称长度，如果超过label width则使用 '...'
    QString memberName = name;
    QFontMetrics fontMetrics(m_member_name->font());
    int strWidth = fontMetrics.width(memberName);

    if (strWidth > 70)
    {
        memberName += "...";
        while (strWidth > 70) {
            memberName = memberName.remove(memberName.length() - 4, 1);
            strWidth = fontMetrics.width(memberName);
        }
    }

    m_member_name->setText("<p style='color:#777'>" + memberName + "</p>");
}


/***********************************/


YLGroupMemberListWidget::YLGroupMemberListWidget(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(200);

    m_button = new Button(this);
    m_button->setText("群成员");
    m_button->setFixedSize(200, 25);
    connect(m_button, &Button::isShow, this, [this](bool flag){
        if (flag)
        {
            m_line_edit->show();
            m_v_ayout->removeWidget(m_list_widget);
            m_v_ayout->addWidget(m_line_edit);
            m_v_ayout->addWidget(m_list_widget);
        }
        else
        {
            m_line_edit->hide();
            m_v_ayout->removeWidget(m_line_edit);
        }
    });


    m_line_edit = new QLineEdit(this);
    m_line_edit->setFixedSize(200, 20);
    m_line_edit->hide();

    m_list_widget = new QListWidget(this);
    m_list_widget->setFixedWidth(200);
    m_list_widget->setStyleSheet("background-color:transparent");

    m_v_ayout = new QVBoxLayout();
    m_v_ayout->addWidget(m_button);
    m_v_ayout->addWidget(m_list_widget);

    m_v_ayout->setSpacing(0);
    m_v_ayout->setMargin(0);
    setLayout(m_v_ayout);
}


void YLGroupMemberListWidget::addRow(const YLGroupMember &member)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setSizeHint(QSize(200, 30));
    m_list_widget->addItem(item);

    MemberWidgetItem *w = new MemberWidgetItem;
    w->setMember(member);

    m_list_widget->setItemWidget(item, w);

}
