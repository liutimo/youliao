#include "ylcreategroupwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QButtonGroup>
YLCreateGroupWidget::YLCreateGroupWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(550, 450);
    setAttribute(Qt::WA_DeleteOnClose);
    init();
    initLayout();
    setWidgetIcon();
    setWidgetTitle("创建群组");

}

void YLCreateGroupWidget::init()
{
    m_tip = new QLabel(this);
    m_tip->move(40, 30);
    m_tip->setText("填写信息");

    m_label_group_name = new QLabel("群名称:", this);
    m_label_group_name->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_label_group_name->setFixedWidth(60);

    m_label_group_count = new QLabel("群规模:", this);
    m_label_group_count->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_label_group_count->setFixedWidth(60);

    m_label_verify = new QLabel("加群验证:", this);
    m_label_verify->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_label_verify->setFixedWidth(60);

    m_lineedit_group_name = new QLineEdit(this);
    m_lineedit_custom_count = new QLineEdit(this);
    m_lineedit_custom_count->setEnabled(false);

    m_custom = new QRadioButton("自定义", this);
    m_custom->setStyleSheet(qss_radio);

    m_200 = new QRadioButton("200人", this);
    m_200->setStyleSheet(qss_radio);

    m_500 = new QRadioButton("500人", this);
    m_500->setStyleSheet(qss_radio);

    m_200->setChecked(true);

    m_group1 = new QButtonGroup(this);
    m_group1->addButton(m_200, 1);
    m_group1->addButton(m_500, 2);
    m_group1->addButton(m_custom, 3);
    connect(m_group1, SIGNAL(buttonToggled(int,bool)), this, SLOT(enableCustom(int,bool)));

    m_all = new QRadioButton("允许任何人", this);
    m_all->setStyleSheet(qss_radio);

    m_need_verify = new QRadioButton("需身份验证", this);
    m_need_verify->setStyleSheet(qss_radio);

    m_none_all = new QRadioButton("不允许任何人", this);\
    m_none_all->setStyleSheet(qss_radio);

    m_need_verify->setChecked(true);

    m_next = new QPushButton("下一步", this);
    m_next->setFixedSize(60, 30);

    m_before = new QPushButton("上一步", this);
    m_before->setFixedSize(60, 30);
    m_before->hide();

    connect(m_next, &QPushButton::clicked, this, [this](){
        if (m_next->text() == "下一步")
        {
            if (m_lineedit_group_name->text().isEmpty())
            {
                //do something
                return;
            }

            if (m_custom->isChecked() && m_lineedit_custom_count->text().isEmpty())
            {
                //do something
                return;
            }

            m_widget_1->hide();
            m_before->show();
            m_next->setText("完成");
        }
        else
        {
            //do something
            close();
        }
    });

    connect(m_before, &QPushButton::clicked, this, [this](){
        m_widget_1->show();
        m_next->setText("下一步");
    });

    m_widget_1 = new QWidget(this);
}

void YLCreateGroupWidget::initLayout()
{
    QHBoxLayout *h1 = new QHBoxLayout();
    h1->setContentsMargins(0, 10, 0, 10);
    h1->addWidget(m_label_group_name);
    h1->addWidget(m_lineedit_group_name);
    h1->setSizeConstraint(QLayout::SetFixedSize);

    QHBoxLayout *h2 = new QHBoxLayout();
    h2->setContentsMargins(0, 10, 0, 10);
    h2->addWidget(m_label_group_count);
    h2->addWidget(m_200);
    h2->addWidget(m_500);
    h2->addWidget(m_custom);
    h2->addWidget(m_lineedit_custom_count);
    h2->setSizeConstraint(QLayout::SetFixedSize);

    QHBoxLayout *h3 = new QHBoxLayout();
    h3->setContentsMargins(0, 10, 0, 10);
    h3->addWidget(m_label_verify);
    h3->addWidget(m_all);
    h3->addWidget(m_need_verify);
    h3->addWidget(m_none_all);
    h3->setSizeConstraint(QLayout::SetFixedSize);

    QVBoxLayout *v = new QVBoxLayout();
    v->setContentsMargins(10, 50, 10, 0);
    v->addLayout(h1);
    v->addLayout(h2);
    v->addLayout(h3);

    m_widget_1->setLayout(v);
    m_widget_1->move(70, 70);

    m_next->move(480, 410);
    m_before->move(410, 410);

    v->setSizeConstraint(QLayout::SetFixedSize);
}

void YLCreateGroupWidget::enableCustom(int id, bool checked)
{
    if (id == 3 && checked)
    {
        m_lineedit_custom_count->setEnabled(true);
    }
    else
    {
        m_lineedit_custom_count->setEnabled(false);
    }
}
