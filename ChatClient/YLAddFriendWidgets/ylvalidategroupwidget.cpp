#include "ylvalidategroupwidget.h"
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include "YLCommonControl/ylheadframe.h"
#include "YLNetWork/ylbusiness.h"
YLValidateGroupWidget::YLValidateGroupWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(460, 360);

    initLeft();
    initRight();
    initBottom();
}

YLValidateGroupWidget::~YLValidateGroupWidget()
{

}

void YLValidateGroupWidget::setGroup(const YLGroup &group)
{
    m_group = group;

    uint32_t verifyType = m_group.getVerifyType();
    if (verifyType == 1) // 需要验证
    {
        //do nothing
    }
    else if (verifyType == 2)   //不需要验证
    {
        m_next->hide();
        m_tip->hide();
        m_text_eidt->hide();
        m_info->show();
        //send Request
//        YLBusiness::addGroup(m_group.getGroupId());
    }
}

void YLValidateGroupWidget::initLeft()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(70, 70);
    m_head_frame->move(15, 50);

    m_group_name = new QLabel("群名", this);
    m_group_name->move(15, 130);

    m_group_id = new QLabel("11", this);
    m_group_id->move(15, 150);

    m_group_member_count = new QLabel("成员: 10人", this);
    m_group_member_count->move(15, 170);

    m_group_intro = new QLabel("简介:", this);
    m_group_intro->move(15, 190);

}

void YLValidateGroupWidget::initRight()
{
    m_tip = new QLabel("<span style='font:14px; color:black;'>请输入验证信息:</span>", this);
    m_tip->move(135, 50);

    m_text_eidt = new QTextEdit(this);
    m_text_eidt->setFixedSize(280, 80);
    m_text_eidt->move(135, 80);

    m_info = new QLabel("成功加入该群", this);
    m_info->setFixedSize(300, 100);
    m_info->move(135, 50);;
    m_info->hide();
}


void YLValidateGroupWidget::initBottom()
{
    m_next = new QPushButton("下一步", this);
    m_next->setFixedSize(80, 30);
    m_next->move(270, height() - 35);
    connect(m_next, &QPushButton::clicked, this, &YLValidateGroupWidget::next);

    m_cancel = new QPushButton("关闭", this);
    m_cancel->setFixedSize(80, 30);
    m_cancel->move(360, height() - 35);
    connect(m_cancel, &QPushButton::clicked, this, [this](){ close(); });

}

void YLValidateGroupWidget::next()
{
    m_next->hide();
    m_tip->hide();
    m_text_eidt->hide();
    m_info->show();
    m_info->setText("已发送加群申请！！！！！！");
}
