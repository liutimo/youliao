#include "ylloginpanel.h"

#include "YLCommonControl/ylheadandstatusframe.h"
#include "YLCommonControl/yllineedit.h"
#include "ylaccountlistview.h"
#include "YLMainFrame/ylmainwidget.h"

#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMouseEvent>
#include <QDebug>

#include "YLNetWork/netservice.h"

YLLoginPanel::YLLoginPanel(QWidget *parent) : YLBasicWidget(parent)
{
    init();

    connect(YLNetService::instance(), &YLNetService::error, this, [](YLNetServiceError error){
        if (error == Connect2ServerFailed)
            qDebug() << "连接登录服务器失败";
    });
}

void YLLoginPanel::init()
{
    head_frame_           = new YLHeadAndStatusFrame(this);
    connect(head_frame_, &YLHeadAndStatusFrame::statusChanged, this, [this](YLHeadAndStatusFrame::Status s){
        //handle status changed message here;
    });

    lineedit_useraccount_ = new YLLineEdit(this);
    lineedit_useraccount_->setPlaceholderText("输入账号");
    lineedit_useraccount_->setObjectName("lineedit_useraccount_");
    lineedit_useraccount_->setStyleSheet(qss_useraccount_);
    lineedit_useraccount_->setButtonIcon(":/res/LoginPanel/arrow_normal.png", ":/res/LoginPanel/arrow_hover.png", ":/res/LoginPanel/arrow_press.png");
    connect(lineedit_useraccount_, &YLLineEdit::button_clicked, this, &YLLoginPanel::on_account_button_clicked);

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

void YLLoginPanel::resizeEvent(QResizeEvent *event)
{
    head_frame_->move((width() - head_frame_->width()) / 2, 35);
    lineedit_useraccount_->move((width() - lineedit_useraccount_->width()) / 2, 175);
    lineedit_passwd_->move((width() - lineedit_passwd_->width()) / 2, 210);
    pushbutton_login_->move((width() - pushbutton_login_->width()) / 2, 255);
    YLBasicWidget::resizeEvent(event);
}

void YLLoginPanel::mousePressEvent(QMouseEvent *event)
{
    if (!account_listview_->geometry().contains(event->pos()))
        account_listview_->hide();

    YLBasicWidget::mousePressEvent(event);
}

void YLLoginPanel::on_login()
{
    //登录操作在这里完成。


    YLMainWidget *main_widget = new YLMainWidget;
    main_widget->show();

    this->close();
}

void YLLoginPanel::on_account_button_clicked()
{
    if (account_listview_->isVisible())
    {
        account_listview_->hide();
        return;
    }

    QVector<QStringList> vec;
    QStringList l1;
    l1 << ":/res/1.jpg" << "liuzheng" << "779564531";

    for (int i = 0; i < 5; ++i)
    {
        vec.push_back(l1);
        vec.push_back(l1);
    }

    account_listview_->setData(vec);

    account_listview_->move(QPoint((width() - lineedit_useraccount_->width()) / 2, 210));
    account_listview_->show();

}
