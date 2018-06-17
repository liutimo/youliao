#include "yluserinformationwidget.h"
#include "ui_userinformation.h"

#include "YLCommonControl/ylheadframe.h"
#include "globaldata.h"
#include "YLCommonControl/ylmodifyinfowidget.h"
#include "YLCommonControl/ylmodifyusericon.h"
#include <QUrl>
#include <QPainter>

YLUserInformationWidget::YLUserInformationWidget(QWidget *parent) : YLBasicWidget(parent), ui(new Ui::UserInfoWidget)
{
    ui->setupUi(this);

    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(60, 60);
    m_head_frame->move(65, 410);
    m_head_frame->setStyleSheet("QLabel:hover{border-image:url(:/res/head_bkg_highlight_60.png);}");
    connect(m_head_frame, &YLHeadFrame::clicked, this, [this](){
        YLModifyUserIcon *w = new YLModifyUserIcon;
        QUrl url(m_user_info.user_header_url().c_str());
        w->setUserIcon(GlobalData::imagePath + url.fileName());
        w->show();
    });
}


void YLUserInformationWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::red);
}

void YLUserInformationWidget::setUserInfo()
{
    m_user_info = GlobalData::getCurrLoginUser();

    setBigIcon();
    setSmallIcon();
    setNickName();
    setSignature();
    setLocation();
    setAge();
    setBirthday();
    setPhone();
    setEmail();
    setHomeTown();
    setSchool();
}


void YLUserInformationWidget::setBigIcon()
{
    QUrl url(m_user_info.user_header_url().c_str());
    ui->bigIcon->setPixmap(QPixmap(GlobalData::imagePath + url.fileName()));
}

void YLUserInformationWidget::setSmallIcon()
{
    m_head_frame->setHeadFromUrl(QUrl(m_user_info.user_header_url().c_str()));
}

void YLUserInformationWidget::setNickName()
{
    ui->nick->setText(m_user_info.user_nick().c_str());
}

void YLUserInformationWidget::setSignature()
{
    QString signature = m_user_info.user_sign_info().c_str();
    if (signature.isEmpty())
        ui->signature->setText("编辑个性签名");
    else
        ui->signature->setText(signature);
}

void YLUserInformationWidget::setLocation()
{
    ui->location->setText(m_user_info.user_location().c_str());
}

void YLUserInformationWidget::setAge()
{
    ui->age->setText("");
}

void YLUserInformationWidget::setBirthday()
{

}

void YLUserInformationWidget::setPhone()
{
    ui->phone->setText(m_user_info.user_phone().c_str());
}

void YLUserInformationWidget::setEmail()
{
    ui->email->setText(m_user_info.user_email().c_str());
}

void YLUserInformationWidget::setHomeTown()
{
    ui->hometown->setText(m_user_info.user_hometown().c_str());
}

void YLUserInformationWidget::setSchool()
{
    ui->school->setText(m_user_info.user_school().c_str());
}

void YLUserInformationWidget::on_pushButton_clicked()
{
    YLModifyInfoWidget *w = new YLModifyInfoWidget;
    w->setUserInfo(m_user_info);
    w->show();

    connect(w, &YLModifyInfoWidget::modifySuccess, this, [this](){
        setUserInfo();
    });
}
