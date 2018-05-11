#include "ylgroupinfowidget.h"
#include "YLCommonControl/ylheadframe.h"
#include "YLCommonControl/ylmemberlistwidget.h"
#include "YLNetWork/ylbusiness.h"
#include "YLNetWork/pduhandler.h"
#include "globaldata.h"
#include <QToolButton>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPalette>
#include <QFileDialog>
#include <QDebug>
#include <QDateTime>
YLGroupInfoWidget::YLGroupInfoWidget(QWidget *parent) : YLBasicWidget(parent), index(1)
{
    setFixedSize(630, 450);
    initTopNavigationBar();
    initLeft();
    initRight1();
    initRight2();

    memberHide();
    settingHide();

    connect(PduHandler::instance(), &PduHandler::groupMembers, this, &YLGroupInfoWidget::updateGroupMemberList);
}

void YLGroupInfoWidget::initTopNavigationBar()
{
    m_main = new QToolButton(this);
    m_main->setText("首页");
    m_main->setFixedSize(45, 40);
    m_main->move(210, 20);
    m_main->setStyleSheet(qss_selected);
    connect(m_main, &QToolButton::clicked, this, &YLGroupInfoWidget::navigationClicked);

    m_member = new QToolButton(this);
    m_member->setText("成员");
    m_member->setFixedSize(45, 40);
    m_member->move(275, 20);
    m_member->setStyleSheet(qss_no_selected);
    connect(m_member, &QToolButton::clicked, this, &YLGroupInfoWidget::navigationClicked);

    m_setting = new QToolButton(this);
    m_setting->setText("设置");
    m_setting->setFixedSize(45, 40);
    m_setting->move(335, 20);
    m_setting->setStyleSheet(qss_no_selected);
    connect(m_setting, &QToolButton::clicked, this, &YLGroupInfoWidget::navigationClicked);
}

void YLGroupInfoWidget::initLeft()
{
    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(100, 100);
    m_head_frame->move(50, 60);

    m_label_group_name = new QLabel("2345678", this);
    m_label_group_name->setFixedSize(140, 20);
    m_label_group_name->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_label_group_name->move(30, 180);

    m_label_group_id = new QLabel("2345678", this);
    m_label_group_id->setFixedSize(200, 20);
    m_label_group_id->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_label_group_id->move(0, 205);

    QFont f = m_label_group_name->font();
    f.setPixelSize(14);
    m_label_group_name->setFont(f);
    f.setPixelSize(12);
    m_label_group_id->setFont(f);

    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::white);
    m_label_group_name->setPalette(pa);
    m_label_group_id->setPalette(pa);

    m_send_button = new QPushButton("发消息", this);
    m_send_button->setFixedSize(90, 30);
    m_send_button->move(55 , 370);
}

void YLGroupInfoWidget::initRight1()
{
    m_add_photo = new QPushButton(this);
    m_add_photo->setFixedSize(60, 60);
    m_add_photo->move(250, 70);
    m_add_photo->setStyleSheet(qss_add_photo);
    connect(m_add_photo, &QPushButton::clicked, this, &YLGroupInfoWidget::uploadPhoto);

    m_photo = new QLabel(this);
    m_photo->setFixedSize(60, 60);
    m_photo->move(312, 70);

    m_label_group_intro = new QLabel("<p style='color:gray;'>群介绍</p>", this);
    m_label_group_intro->setFixedSize(40, 20);
    m_label_group_intro->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_label_group_intro->move(250, 170);

    m_group_intro = new QLabel(this);
    m_group_intro->setFixedSize(200, 20);
    m_group_intro->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_group_intro->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_group_intro->move(295, 170);

    m_label_manager = new QLabel("<p style='color:gray;'>群主/管理员</p>", this);
    m_label_manager->setFixedSize(70, 20);
    m_label_manager->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_label_manager->move(250, 200);

    int w = 250;
    for (int i = 0; i < 1 + m_group.getManagers().size(); ++i)
    {
        YLHeadFrame *h = new YLHeadFrame(this);
        h->setFixedSize(36, 36);

        h->move(w + i * 40, 220);
        members.push_back(h);
    }

    m_label_member_distr = new QLabel(this);
    m_label_member_distr->setFixedSize(100, 20);
    m_label_member_distr->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_label_member_distr->move(250, 255);
}


void YLGroupInfoWidget::initRight2()
{
    m_member_list = new YLMemberListWidget(this);
    m_member_list->setFixedSize(400, 350);
    m_member_list->move(210, 95);
    connect(m_member_list, &YLMemberListWidget::groupCardChanged, this, [this](uint32_t memberId, QString groupCard){
        auto &member = GlobalData::getMemberInfo(m_group.getGroupId(), memberId);
        member.set_group_card(groupCard.toStdString());
        YLBusiness::modifyGroupCard(m_group.getGroupId(), groupCard);
    });

    m_label_manager_count = new QLabel(this);
    m_label_manager_count->setFixedSize(100, 20);
    m_label_manager_count->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_label_manager_count->move(220, 70);


    m_modify_group_card = new QPushButton("修改我的群名片", this);
    m_modify_group_card->setFixedSize(100, 20);
    m_modify_group_card->setStyleSheet("border:0px; color:#31C0F6;");
    m_modify_group_card->move(480, 70);
    connect(m_modify_group_card, &QPushButton::clicked, this, &YLGroupInfoWidget::modifyGroupCard);

}

void YLGroupInfoWidget::setGroup(const YLGroup &group)
{
    m_group = group;
    m_label_group_name->setText(m_group.getGroupName());
    m_label_group_id->setText(QString::number(m_group.getGroupId()));
    m_head_frame->setHeadFromUrl(m_group.getGroupImage());
    QUrl url(m_group.getGroupImage());
    m_photo->setPixmap(QPixmap("./" + url.fileName()).scaled(m_photo->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    m_group_intro->setText(QString("该群创建于%1:").arg(QDateTime::fromTime_t(m_group.getCreateTime()).toString("yyyy/mm/dd")));
    m_label_member_distr->setText(QString("<p style='color:gray;'>群员分布(%1/%2)</p>").arg(1 + group.getManagers().size() + group.getMembers().size()).arg(m_group.getGroupCapacity()));
    m_label_manager_count->setText(QString("管理员: %1/10人").arg(m_group.getManagers().size() + 1));

    //发送网络请求
    YLBusiness::getGroupMembersInfo(m_group.getGroupId());
}


void YLGroupInfoWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgba(qRgba(200, 200, 200, 200)));
    p.drawRect(0, 0, 200, 450);

    p.setBrush(Qt::white);
    p.drawRect(200, 0, 430, 450);

    p.setPen(Qt::gray);
    p.drawLine(210, 59, 620, 59);
    if (index == 1)
        p.drawLine(250, 160, 570, 160);
}


void YLGroupInfoWidget::uploadPhoto()
{
    QString m_filename = QFileDialog::getOpenFileName(this, tr("选择图片"), QDir::homePath(), tr("Images (*.png *.jpeg *.bmp *.gif *.jpg)"));
    qDebug() << m_filename;
}


void YLGroupInfoWidget::modifyGroupCard()
{
    m_member_list->modifyGroupCard();
}


void YLGroupInfoWidget::updateGroupMemberList()
{
    m_member_list->clear();
    m_member_list->setHeader();
    auto managers = m_group.getManagers();
    auto members = m_group.getMembers();
    uint32_t creatorId = m_group.getGroupCreator();

    base::MemberInfo memberInfo = GlobalData::getMemberInfo(m_group.getGroupId(), creatorId);
    m_member_list->setRow(memberInfo, MemberNameWidgetItem::GROUPOWER);

    for (uint32_t managerId : managers)
    {
        base::MemberInfo memberInfo = GlobalData::getMemberInfo(m_group.getGroupId(), managerId);
        m_member_list->setRow(memberInfo, MemberNameWidgetItem::GROUPMANAGER);
    }

    for (uint32_t memberId : members)
    {
        base::MemberInfo memberInfo = GlobalData::getMemberInfo(m_group.getGroupId(), memberId);
        m_member_list->setRow(memberInfo, MemberNameWidgetItem::GROUPMEMBER);
    }
}

void YLGroupInfoWidget::navigationClicked()
{
    QToolButton *object = static_cast<QToolButton*>(sender());

    index = 0;

    if (object == m_main)
    {
        index = 1;
        m_main->setStyleSheet(qss_selected);
        m_member->setStyleSheet(qss_no_selected);
        m_setting->setStyleSheet(qss_no_selected);
        mainShow();
        memberHide();
        settingHide();
    }
    else if (object == m_member)
    {
        index = 2;
        m_main->setStyleSheet(qss_no_selected);
        m_member->setStyleSheet(qss_selected);
        m_setting->setStyleSheet(qss_no_selected);
        mainHide();
        memberShow();
        settingHide();
    }
    else if (object == m_setting)
    {
        index = 3;
        m_main->setStyleSheet(qss_no_selected);
        m_member->setStyleSheet(qss_no_selected);
        m_setting->setStyleSheet(qss_selected);
        mainHide();
        memberHide();
        settingShow();
    }
    update();
}


void YLGroupInfoWidget::mainShow()
{
    m_add_photo->show();
    m_photo->show();
    m_group_intro->show();
    m_label_group_intro->show();
    m_label_manager->show();
    m_label_member_distr->show();

    for (YLHeadFrame* item : members)
        item->show();
}

void YLGroupInfoWidget::memberShow()
{
    m_member_list->show();
    m_label_manager_count->show();
    m_modify_group_card->show();
}

void YLGroupInfoWidget::settingShow()
{

}


void YLGroupInfoWidget::mainHide()
{
    m_add_photo->hide();
    m_photo->hide();
    m_group_intro->hide();
    m_label_group_intro->hide();
    m_label_manager->hide();
    m_label_member_distr->hide();
    for (YLHeadFrame* item : members)
        item->hide();
}

void YLGroupInfoWidget::memberHide()
{
    m_member_list->hide();
    m_label_manager_count->hide();
    m_modify_group_card->hide();
}

void YLGroupInfoWidget::settingHide()
{

}