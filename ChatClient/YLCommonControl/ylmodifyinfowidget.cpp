#include "ylmodifyinfowidget.h"
#include "ui_modifyinfo.h"
#include <QPainter>
#include "YLNetWork/ylbusiness.h"
#include "protobuf/youliao.base.pb.h"
#include "globaldata.h"
using namespace youliao::pdu;

YLModifyInfoWidget::YLModifyInfoWidget(QWidget *parent) : YLBasicWidget(parent), ui(new Ui::ModifyInfoationWidget)
{
    ui->setupUi(this);

    setWidgetTitle("编辑资料");
    setWidgetIcon();
}


void YLModifyInfoWidget::setUserInfo(base::UserInfo &userInfo)
{
    m_user_info = userInfo;
    ui->nick->setText(userInfo.user_nick().c_str());
    ui->email->setText(userInfo.user_email().c_str());
    ui->hometown->setText(userInfo.user_hometown().c_str());
    ui->location->setText(userInfo.user_location().c_str());
    ui->school->setText(userInfo.user_school().c_str());
    ui->phone->setText(userInfo.user_phone().c_str());
    ui->signal->setPlainText(userInfo.user_sign_info().c_str());
    ui->birthday->setText(userInfo.user_birthday().c_str());
    ui->comboBox->setCurrentIndex(userInfo.user_sex());
}


void YLModifyInfoWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(40,138,221));
    p.drawRect(0, 0, width(), 32);

    p.setBrush(Qt::white);
    p.drawRect(0, 32, width(), height() - 72);


    p.setBrush(QColor::fromRgb(221,221,221));
    p.drawRect(0, height() - 42, width(), 42);

}

void YLModifyInfoWidget::on_pushButton_2_clicked()
{
    close();
}

void YLModifyInfoWidget::on_saveBtn_clicked()
{
    bool flag = false;
    if (m_user_info.user_sign_info() != ui->signal->toPlainText().toStdString())
        flag = true;

    m_user_info.set_user_nick(ui->nick->text().toStdString());
    m_user_info.set_user_sex(ui->comboBox->currentIndex());
    m_user_info.set_user_birthday(ui->birthday->text().toStdString());
    m_user_info.set_user_hometown(ui->hometown->text().toStdString());
    m_user_info.set_user_location(ui->location->text().toStdString());
    m_user_info.set_user_school(ui->school->text().toStdString());
    m_user_info.set_user_phone(ui->phone->text().toStdString());
    m_user_info.set_user_email(ui->email->text().toStdString());
    m_user_info.set_user_sign_info(ui->signal->toPlainText().toStdString());


    YLBusiness::modifyInformation(m_user_info, flag);

    GlobalData::setCurrLoginUser(m_user_info);

    emit modifySuccess();
    close();
}
