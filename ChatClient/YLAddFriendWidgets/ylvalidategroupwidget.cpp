#include "ylvalidategroupwidget.h"
#include <QLabel>
#include <QPainter>
#include <QTextEdit>
#include <QPushButton>
#include "YLCommonControl/ylheadframe.h"
#include "YLNetWork/ylbusiness.h"
YLValidateGroupWidget::YLValidateGroupWidget(QWidget *parent) : YLBasicWidget(parent)
{
    setWidgetTitle("添加群");
    setWidgetIcon(":/res/qqlogo.png");
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

    m_group_name->setText(m_group.getGroupName());
    m_head_frame->setHeadFromUrl(m_group.getGroupImage());
    m_group_id->setText(QString::number(m_group.getGroupId()));
    m_group_member_count->setText(QString("成员: %1人").arg(m_group.getCount()));
//    m_group_intro->setText("");

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
        m_icon->show();
        m_info->show();
        //send Request
        YLBusiness::addGroup(m_group.getGroupId());
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


    m_icon = new QLabel(this);
    m_icon->setFixedSize(40, 40);
    m_icon->setPixmap(QPixmap(":/res/MessageBox/sysmessagebox_okFile.png"));
    m_icon->move(160, 65);
    m_icon->hide();

    m_info = new QLabel("成功加入该群", this);
    m_info->setFixedSize(210, 40);
    m_info->setWordWrap(true);
    m_info->setAlignment(Qt::AlignVCenter);
    m_info->move(210, 65);;
    m_info->hide();
}


void YLValidateGroupWidget::initBottom()
{
    m_next = new QPushButton("下一步", this);
    m_next->setFixedSize(64, 23);
    m_next->move(300, height() - 30);
    connect(m_next, &QPushButton::clicked, this, &YLValidateGroupWidget::next);
    m_next->setStyleSheet("QPushButton{border-image:url(:/res/YLCommonControl/audio_button_normal.png)}\
                          QPushButton:hover{border-image:url(:/res/YLCommonControl/audio_button_hoverl.png)}\
                          QPushButton:pressed{border-image:url(:/res/YLCommonControl/audio_button_down.png)}");

    m_cancel = new QPushButton("关闭", this);
    m_cancel->setFixedSize(64, 23);
    m_cancel->move(380, height() - 30);
    connect(m_cancel, &QPushButton::clicked, this, [this](){ close(); });
    m_cancel->setStyleSheet("QPushButton{border-image:url(:/res/YLCommonControl/audio_button_normal.png)}\
                            QPushButton:hover{border-image:url(:/res/YLCommonControl/audio_button_hoverl.png)}\
                            QPushButton:pressed{border-image:url(:/res/YLCommonControl/audio_button_down.png)}");

}

void YLValidateGroupWidget::next()
{
    m_next->hide();
    m_tip->hide();
    m_text_eidt->hide();
    m_icon->show();
    m_info->show();
    m_info->setText("你的加群请求已发送成功,请等候群主/管理员验证。");
    YLBusiness::addGroup(m_group.getGroupId(), m_text_eidt->toPlainText());
}


void YLValidateGroupWidget::paintEvent(QPaintEvent *event)
{
    const int titleBarHeight = 32;
    const int bottomBarHeight = 36;
    const int leftWidth = 130;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);


    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    painter.setBrush(QColor::fromRgb(40, 138, 221));           //#288ADD
    painter.drawRect(0, 0, width(), titleBarHeight);

    painter.setBrush(QColor::fromRgb(234, 238, 245));           //#EAEEF5
    painter.drawRect(0, height() - bottomBarHeight, width(), bottomBarHeight);

    painter.setBrush(QColor::fromRgb(248, 250, 252));           //#F8FAFC
    painter.drawRect(0, titleBarHeight, leftWidth, height() - titleBarHeight - bottomBarHeight);
}
