#include "ylloginpanel.h"
#include "ylregisterwidget.h"
#include "YLCommonControl/ylheadandstatusframe.h"
#include "YLCommonControl/yllineedit.h"
#include "YLCommonControl/ylmessagebox.h"
#include "YLNetWork/http/httphelper.h"
#include "YLMainFrame/ylmainwidget.h"
#include "YLTray/yllogintray.h"
#include "YLNetWork/ylnetservice.h"
#include "YLNetWork/ylbusiness.h"
#include "YLNetWork/pduhandler.h"
#include "../yllocalsettings.h"
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QCheckBox>
#include <QApplication>
using namespace youliao::pdu;

YLLoginPanel::YLLoginPanel(QWidget *parent) : YLBasicWidget(parent), m_connected(false)
{
    init();
    initTray();
    initCheckBoxs();
    connectToLoginServer();

    connect(PduHandler::instance(), &PduHandler::loginStatus, this, [this](bool successed, base::UserInfo *userInfo){
        if (successed)
        {
            YLMainWidget *mainWidget = new YLMainWidget;
            mainWidget->setUserInfo(userInfo);
            mainWidget->startHeartBeat();
            mainWidget->show();
            userInfo = nullptr;
            m_login_tray->hide();
            hide();
        }
        else
        {
            YLMessageBox *message = new YLMessageBox(BUTTON_OK,this);
            message->setTitle("网络错误");
            message->setToolTip("无法连接登录服务器");
            message->exec();
        }
    }, Qt::QueuedConnection);


}

void YLLoginPanel::init()
{

    min_button_ = new QPushButton(this);
    min_button_->resize(close_button_->size());
    min_button_->setObjectName("min_button_");
    min_button_->setStyleSheet(qss_min_button);
    min_button_->move(436, 0);

    connect(min_button_, &QPushButton::clicked, this, [this](){
        hide();
    });

    head_frame_           = new YLHeadAndStatusFrame(this);
    head_frame_->setHeadFromLocal("1.jpg", true);
    connect(head_frame_, &YLHeadAndStatusFrame::statusChanged, this, [this](YLHeadAndStatusFrame::Status s){
        //handle status changed message here;
    });

    lineedit_useraccount_ = new QLineEdit(this);
    lineedit_useraccount_->setPlaceholderText("输入账号");
    lineedit_useraccount_->setObjectName("lineedit_useraccount_");
    lineedit_useraccount_->setStyleSheet(qss_useraccount_);

    lineedit_passwd_      = new QLineEdit(this);
    lineedit_passwd_->setPlaceholderText("输入密码");
    lineedit_passwd_->setEchoMode(QLineEdit::Password);
    lineedit_passwd_->setObjectName("lineedit_passwd_");
    lineedit_passwd_->setStyleSheet(qss_password_);

    pushbutton_login_     = new QPushButton(this);
    pushbutton_login_->setText("登   录");
    pushbutton_login_->setObjectName("pushbutton_login_");
    pushbutton_login_->setStyleSheet(qss_login_button_);
    connect(pushbutton_login_, &QPushButton::clicked, this, &YLLoginPanel::on_login);

    m_icon = new QLabel(this);
    m_icon->setFixedSize(63, 48);
    m_icon->setPixmap(QPixmap(":/res/LoginPanel/chat.png"));
    m_icon->move(150, 80);

    m_name = new QLabel(this);
    m_name->setFixedSize(200, 106);
    m_name->setPixmap(QPixmap(":/res/LoginPanel/2.png").scaled(500, 50));
    m_name->move(220, 50);


    m_register = new QPushButton(this);
    m_register->setFixedSize(54, 16);
    m_register->setStyleSheet(qss_regis_button);
    connect(m_register, &QPushButton::clicked, this, &YLLoginPanel::on_register);

    m_find_pw = new QPushButton(this);
    m_find_pw->setFixedSize(54, 16);
    m_find_pw->setStyleSheet(qss_mima_button);

    lineedit_passwd_->resize(200, 35);
    pushbutton_login_->resize(200, 35);
    lineedit_useraccount_->resize(200, 35);
}


void YLLoginPanel::initTray()
{
    m_login_tray = new YLLoginTray(this);
    m_login_tray->show();

    connect(m_login_tray, &YLLoginTray::quit, this, &QApplication::quit);
    connect(m_login_tray, &YLLoginTray::showMain, this, [this](){ this->show(); });
}

void YLLoginPanel::initCheckBoxs()
{   
    m_remember_pwd = new QCheckBox("记住密码", this);
    m_remember_pwd->setStyleSheet(qss_checkbox);

    m_auto_login = new QCheckBox("自动登录", this);
    m_auto_login->setStyleSheet(qss_checkbox);

    YLLocalSettings *settings = YLLocalSettings::instance();
    m_auto_login->setChecked(settings->getBool("auto_login"));
    m_remember_pwd->setChecked(settings->getBool("remeber_pwd"));
    lineedit_useraccount_->setText(settings->getValue("recent_account").toString());
    if (m_remember_pwd->isChecked())
        lineedit_passwd_->setText(settings->getValue("password").toString());
}

void YLLoginPanel::resizeEvent(QResizeEvent *event)
{
//    head_frame_->move((width() - head_frame_->width()) / 2, 35);
//    lineedit_useraccount_->move((width() - lineedit_useraccount_->width()) / 2, 175);
//    lineedit_passwd_->move((width() - lineedit_passwd_->width()) / 2, 210);
//    pushbutton_login_->move((width() - pushbutton_login_->width()) / 2, 275);
//    m_remember_pwd->move(pushbutton_login_->geometry().topLeft().x(), 250);
//    m_auto_login->move(pushbutton_login_->geometry().topRight().x() - 70, 250);

    head_frame_->move(50, 200);
    lineedit_useraccount_->move(160, 200);
    lineedit_passwd_->move(160, 235);
    pushbutton_login_->move(160, 305);
    m_remember_pwd->move(160, 275);
    m_auto_login->move(290, 275);

    m_register->move(370, 210);
    m_find_pw->move(370, 245);

    YLBasicWidget::resizeEvent(event);
}

void YLLoginPanel::mousePressEvent(QMouseEvent *event)
{

    YLBasicWidget::mousePressEvent(event);
}

void YLLoginPanel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor::fromRgb(123, 193, 234));
    painter.drawRect(0, 0, width(), 190);
    painter.setBrush(QColor::fromRgb(235, 242, 249));    //#EBF2F9
    painter.drawRect(0, 190, width(), height() - 190);
}


void YLLoginPanel::on_login()
{
    YLLocalSettings *settings = YLLocalSettings::instance();
    settings->setValue("auto_login", m_auto_login->isChecked());
    settings->setValue("remeber_pwd", m_remember_pwd->isChecked());
    settings->setValue("recent_account", lineedit_useraccount_->text());
    if(m_remember_pwd->isChecked())
        settings->setValue("password", lineedit_passwd_->text());

    //登录操作在这里完成。
    if (m_connected)
    {
        YLBusiness::login(lineedit_useraccount_->text(), lineedit_passwd_->text());
    }
}


void YLLoginPanel::on_register()
{
    YLRegisterWidget *widget = new YLRegisterWidget();
    widget->show();
}

//network
void YLLoginPanel::connectToLoginServer()
{
    YLNetService *ylNetService = YLNetService::instance();
    connect(ylNetService, &YLNetService::connectLoginServerStatus, this, [this](bool status){
       m_connected = status;
       if (!m_connected)
       {
           YLMessageBox *message = new YLMessageBox(BUTTON_OK, this);
           message->setTitle("网络错误");
           message->setToolTip("无法连接登录服务器");
           message->exec();
       }
    }, Qt::UniqueConnection);
}

