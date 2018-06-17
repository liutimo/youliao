#include "ylregisterwidget.h"
#include "ui_register.h"
#include <QFileDialog>
#include <QDebug>
#include "YLNetWork/http/httphelper.h"
#include "YLNetWork/ylbusiness.h"
#include "YLNetWork/pduhandler.h"

#include <QMovie>
#include <QPainter>

YLRegisterWidget::YLRegisterWidget(QWidget *parent) : YLBasicWidget(parent), ui(new Ui::RegisterWidget)
  ,m_header_uploaded(false)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);

    ui->title->setPixmap(QPixmap(":/res/LoginPanel/2.png").scaled(500, 50));

    connect(ui->radioButton_2, &QRadioButton::toggled, this, [this](bool flag){
        if (flag)
        {
            ui->pushButton->setEnabled(true);
        }
        else
        {
            ui->pushButton->setEnabled(false);
        }
    });

    connect(PduHandler::instance(), &PduHandler::regiserStatus, this, [this](uint32_t resultCode, QString account){
        if (resultCode == 0)
            m_loading_widget->registerSuccess(account);
        else
            m_loading_widget->registerFailed();
    });
}

void YLRegisterWidget::on_registerButton_clicked()
{
    if (ui->nickName->text().isEmpty())
    {
        ui->tip1->setText("昵称不能为空");
    }
    else
    {
        ui->tip1->setText("");
    }

    if (ui->password1->text().isEmpty())
    {
        ui->tip2->setText("密码不能为空");
    }
    else
    {
        ui->tip2->setText("");
    }

    if (ui->password1->text() != ui->password2->text())
    {
        ui->tip3->setText("两次密码不一致");
    }
    else
    {
        ui->tip3->setText("");
    }

    if (ui->radioButton_2->isChecked() && !m_header_uploaded)
    {
        ui->tip4->setText("未上传头像");
    }
    else
    {
        ui->tip4->setText("");
    }

    if (ui->tip1->text().isEmpty() && ui->tip2->text().isEmpty() && ui->password1->text() == ui->password2->text())
    {
        YLBusiness::registerAccount(ui->nickName->text(), ui->password1->text(), m_image_url);
        m_loading_widget = new LoadingWidget(this);
        m_loading_widget->resize(size());
        m_loading_widget->show();

        connect(m_loading_widget, &LoadingWidget::closeClicked, this, [this](bool success){
            if (success)
                close();
            else
                m_loading_widget->close();
        });
    }


}

void YLRegisterWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor::fromRgb(123, 193, 234));
    painter.drawRect(0, 0, width(), 190);
    painter.setBrush(QColor::fromRgb(235, 242, 249));    //#EBF2F9
    painter.drawRect(0, 190, width(), height() - 190);
}

void YLRegisterWidget::uploadImage(const QString &fileName)
{
    HttpHelper httpHelper;
    m_image_url = httpHelper.upload(fileName);
    if (!m_image_url.isEmpty())
        m_header_uploaded = true;
}

void YLRegisterWidget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "", QDir::homePath(), tr("Images (*.png *.jpeg *.bmp *.gif *.jpg)"));

    if (fileName.isEmpty())
    {
        return;
    }

    uploadImage(fileName);

    QFileInfo info(fileName);
    ui->tip4->setText("已选择" + info.fileName());
}




/********************loading********************************/
LoadingWidget::LoadingWidget(QWidget *parent) : QWidget(parent), m_success(false)
{
    m_load = new QLabel(this);
    m_load->setFixedSize(128, 128);

    m_movie = new QMovie(":/res/LoginPanel/loading.gif");
    m_load->setMovie(m_movie);

    m_login = new QPushButton("前往登录", this);
    m_login->setFixedSize(250, 35);
    m_login->setStyleSheet(qss_login_button_);
    m_login->hide();
    connect(m_login, &QPushButton::clicked, this, [this](){
        emit closeClicked(m_success);
    });

    m_account = new QLabel(this);
    m_account->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_account->setFixedSize(250, 35);
    m_account->hide();
}

void LoadingWidget::resizeEvent(QResizeEvent *event)
{
    m_load->move((width() - m_load->width()) / 2, (height() - m_load->height()) / 2);
    m_login->move((width() - 250) / 2, 300);
    m_account->move((width() - 250) / 2, 255);
    QWidget::resizeEvent(event);
}

void LoadingWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(255, 255, 255, 255));
    p.drawRect(rect());
}

void LoadingWidget::registerSuccess(const QString &account)
{
    m_load->setFixedSize(313, 250);
    m_load->setPixmap(QPixmap(":/res/LoginPanel/register_success.png"));
    m_load->move((width() - m_load->width()) / 2, 0);

    m_login->show();

    m_account->setText(QString("<span style=\"color:#FF5B5B; font-size:14px;\">你的账号是:</span><span style=\"color:#FF5B5B; font-size:18px;\">%1</span>").arg(account));
    m_account->show();

    m_success = true;
}

void LoadingWidget::registerFailed()
{
    m_load->setFixedSize(189, 128);
    m_load->setPixmap(QPixmap(":/res/LoginPanel/register_failed.png"));
    m_load->move((width() - m_load->width()) / 2, 100);

    m_account->setText(QString("<span style=\"color:#FF5B5B; font-size:14px;\">注册失败，请稍后再试！</span>"));
    m_account->show();

    m_login->setText("关闭");
    m_login->show();
}
