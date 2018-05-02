#include "ylvalidatewidget.h"
#include <QLabel>
#include <QDebug>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include "globaldata.h"
#include "YLNetWork/ylbusiness.h"
#include "YLCommonControl/ylheadframe.h"

YLValidateWidget::YLValidateWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(460, 360);
    initLeft();
    initRight1();
    initRight2();
    initRight3();
    initBottom();

    right2Hide();
    right3Hide();
    m_index = 1;
}

YLValidateWidget::~YLValidateWidget()
{
    qDebug() << "YLValidateWidget::~YLValidateWidget()";
}

void YLValidateWidget::initLeft()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(110, 110);
    m_head_frame->move(15, 70);

    m_info = new QLabel(this);
    m_info->move(30, 200);
    m_info->setText("<span style='font:14px; color:black;'>空空</span><br>"
                    "<span style='font:12px; color:black;'>123456</span><br>"
                    "<span style='font:12px; color:#8C8C77;'>性别:男</span><br>"
                    "<span style='font:12px; color:#8C8C77;'>年龄:13</span><br>"
                    "<span style='font:12px; color:#8C8C77;'>地点:湖南长沙</span>");
}

void YLValidateWidget::initRight1()
{
    m_tip = new QLabel("<span style='font:14px; color:black;'>请输入验证信息:</span>", this);
    m_tip->move(135, 50);

    m_text_eidt = new QTextEdit(this);
    m_text_eidt->setFixedSize(280, 80);
    m_text_eidt->move(135, 80);
    m_text_eidt->setPlaceholderText("验证信息");
}

void YLValidateWidget::initRight2()
{
    m_remark = new QLabel("<span style='font:14px; color:black;'>备注姓名:</span>", this);
    m_remark->move(135, 50);
    m_group = new QLabel("<span style='font:14px; color:black;'>分  组:</span>", this);
    m_group->move(135, 80);

    m_line_edit = new QLineEdit(this);
    m_line_edit->setFixedSize(180, 30);
    m_line_edit->move(200, 50);

    m_combo_box = new QComboBox(this);
    m_combo_box->setFixedSize(180, 30);
    m_combo_box->move(200, 80);

    for(auto groupName : GlobalData::getGroup())
    {
        m_combo_box->addItem(groupName);
    }

}


void YLValidateWidget::initRight3()
{
    m_result = new QLabel(this);
    m_result->setText("add friend success!!!");
    m_result->move(135, 50);
}

void YLValidateWidget::initBottom()
{
    m_next = new QPushButton("下一步", this);
    m_next->setFixedSize(80, 30);
    m_next->move(270, height() - 35);
    connect(m_next, &QPushButton::clicked, this, &YLValidateWidget::next);

    m_cancel = new QPushButton("取消", this);
    m_cancel->setFixedSize(80, 30);
    m_cancel->move(360, height() - 35);
    connect(m_cancel, &QPushButton::clicked, this, [this](){ close(); });
}

void YLValidateWidget::right1Hide()
{
    m_tip->hide();
    m_text_eidt->hide();
}

void YLValidateWidget::right2Hide()
{
    m_remark->hide();
    m_group->hide();
    m_line_edit->hide();
    m_combo_box->hide();
}

void YLValidateWidget::right2Show()
{
    m_remark->show();
    m_group->show();
    m_line_edit->show();
    m_combo_box->show();
}


void YLValidateWidget::right3Hide()
{
    m_result->hide();
}

void YLValidateWidget::right3Show()
{
    m_result->show();
}

void YLValidateWidget::next()
{
    ++m_index;

    if (m_index == 2)
    {
        right1Hide();
        right3Hide();
        right2Show();
    }
    else if (m_index == 3)
    {
        //send request
        uint32_t groupId = GlobalData::getGroupIdByName(m_combo_box->currentText());
        QString validateData = m_text_eidt->toPlainText();
        QString remark = m_line_edit->text();
        YLBusiness::addFriend(m_friend.friendId(), validateData, remark, groupId);

        right1Hide();
        right2Hide();
        right3Show();
        m_next->hide();
        m_cancel->setText("Finsh");
    }
}

