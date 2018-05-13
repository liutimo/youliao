#include "ylgroupmemberlistwidget.h"

#include <QLineEdit>
#include <QVBoxLayout>
#include <QListWidget>
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
