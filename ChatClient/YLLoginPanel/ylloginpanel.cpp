#include "ylloginpanel.h"

#include "YLCommonControl/ylheadandstatusframe.h"
#include "YLCommonControl/yllineedit.h"
#include "ylaccountlistview.h"
#include "YLMainFrame/ylmainwidget.h"
#include "YLNetWork/ylnetservice.h"
#include "YLNetWork/ylbusiness.h"
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
using namespace youliao::pdu;

YLLoginPanel::YLLoginPanel(QWidget *parent) : YLBasicWidget(parent), m_connected(false)
{
    init();
    initCheckBoxs();
    connectToLoginServer();
}

void YLLoginPanel::init()
{
    head_frame_           = new YLHeadAndStatusFrame(this);
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


    account_listview_     = new YLAccountListView(this);
    connect(account_listview_, &YLAccountListView::selected, this, [this](const QString &account){
        lineedit_useraccount_->setText(account);
    });


    lineedit_passwd_->resize(200, 35);
    pushbutton_login_->resize(200, 35);
    lineedit_useraccount_->resize(200, 35);



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
    head_frame_->move((width() - head_frame_->width()) / 2, 35);
    lineedit_useraccount_->move((width() - lineedit_useraccount_->width()) / 2, 175);
    lineedit_passwd_->move((width() - lineedit_passwd_->width()) / 2, 210);
    pushbutton_login_->move((width() - pushbutton_login_->width()) / 2, 275);
    m_remember_pwd->move(pushbutton_login_->geometry().topLeft().x(), 250);
    m_auto_login->move(pushbutton_login_->geometry().topRight().x() - 70, 250);

    YLBasicWidget::resizeEvent(event);
}

void YLLoginPanel::mousePressEvent(QMouseEvent *event)
{
    if (!account_listview_->geometry().contains(event->pos()))
        account_listview_->hide();

    YLBasicWidget::mousePressEvent(event);
}

void YLLoginPanel::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.setPen(Qt::NoPen);
//    painter.drawPixmap(0, 0, width(), height(), QPixmap(":/res/LoginPanel/background.jpeg"));


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
//        YLMainWidget *main = new YLMainWidget;
//        main->show();
//        this->close();
    }
}

//network

void YLLoginPanel::connectToLoginServer()
{
    YLNetService *ylNetService = YLNetService::instance();
    connect(ylNetService, &YLNetService::connectLoginServerStatus, this, [this](bool status){
       m_connected = status;
       if (!m_connected)
           QMessageBox::about(this, "网络错误", "无法连接登录服务器");
    }, Qt::QueuedConnection);
}

