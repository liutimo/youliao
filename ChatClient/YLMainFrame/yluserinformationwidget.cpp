#include "yluserinformationwidget.h"
#include "ui_userinformation.h"

#include "YLCommonControl/ylheadframe.h"
#include "globaldata.h"
#include "YLCommonControl/ylmodifyinfowidget.h"
#include "YLCommonControl/ylmodifyusericon.h"
#include <QUrl>
#include <QPainter>
#include <QDateTime>

YLUserInformationWidget::YLUserInformationWidget(QWidget *parent) : YLBasicWidget(parent), ui(new Ui::UserInfoWidget)
{
    ui->setupUi(this);

    m_head_frame = new YLHeadFrame(this);
    m_head_frame->setFixedSize(60, 60);
    m_head_frame->move(65, 410);
    m_head_frame->setStyleSheet("QLabel:hover{border-image:url(:/res/head_bkg_highlight_60.png);}");
    connect(m_head_frame, &YLHeadFrame::clicked, this, [this](){
        YLModifyUserIcon *w = new YLModifyUserIcon;
        connect(w, &YLModifyUserIcon::changeIcon, this, [this](const QString &icon){
            ui->bigIcon->setPixmap(QPixmap(icon).scaled(350, 350, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            m_head_frame->setHeadFromLocal(icon);
        });

        QUrl url(m_user_info.user_header_url().c_str());
        w->setUserIcon(GlobalData::imagePath + url.fileName());
        w->show();
    });

//    ui->nick->setTextInteractionFlags(Qt::TextSelectableByMouse);
}


void YLUserInformationWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(239, 239, 239));        //#EFEFEF
    p.drawRect(0, 0, 350, height());

    p.setBrush(Qt::white);
    p.drawRect(350, 0, width() - 350, height());
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
    ui->bigIcon->setPixmap(QPixmap(GlobalData::imagePath + url.fileName())
                           .scaled(360, 360, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void YLUserInformationWidget::setSmallIcon()
{
    m_head_frame->setHeadFromUrl(QUrl(m_user_info.user_header_url().c_str()));
}

void YLUserInformationWidget::setNickName()
{
    QString nickName = m_user_info.user_nick().c_str();
    ui->nick->setToolTip(nickName);

    QFontMetrics fontMetrics(ui->nick->font());
    int strWidth = fontMetrics.width(nickName);

    if (strWidth > 140)
    {
        nickName += "...";
        while (strWidth > 140) {
            nickName = nickName.remove(nickName.length() - 4, 1);
            strWidth = fontMetrics.width(nickName);
        }
    }
    ui->nick->setText(nickName);

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
    QString birth = m_user_info.user_birthday().c_str();
    QDate date = QDate::fromString(birth, "yyyy-MM-dd");

    int mouth = date.month();
    int day = date.day();
    int year = date.year();
    QDate::currentDate().year() - year;

    QString birthdaty = QString("%1月%2日").arg(mouth).arg(day );
    ui->birthday->setText(birthdaty);
    ui->age->setText(QString("%1岁").arg(QDate::currentDate().year() - year + 1));
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
        emit signalChange(m_user_info.user_sign_info().c_str());
    });
}
