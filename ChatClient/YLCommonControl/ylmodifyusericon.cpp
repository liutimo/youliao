#include "ylmodifyusericon.h"
#include "ui_uploadheadicon.h"
#include <QDir>
#include <QPainter>
#include <QFileDialog>
#include <QDebug>
#include "YLNetWork/http/httphelper.h"
#include "YLNetWork/ylbusiness.h"
YLModifyUserIcon::YLModifyUserIcon(QWidget *parent) : YLBasicWidget(parent), ui(new Ui::UploadHeadIcon)
{
    ui->setupUi(this);
    setMouseTracking(true);
    setWidgetIcon(":/res/qqlogo.png");
    setWidgetTitle("更换头像");

    imageEditWidget = new YLImageEditWidget(this);
    imageEditWidget->setFixedSize(350, 350);


    m_mask_widget = new MaskWidget(this);
    m_mask_widget->setFixedSize(350, 350);
    m_mask_widget->move(19, 92);
    m_mask_widget->hide();

    ui->verticalLayout->replaceWidget(ui->scrollArea, imageEditWidget);



    ui->scrollArea->close();
}


void YLModifyUserIcon::setUserIcon(const QString &url)
{
    QPixmap pix(url);
    imageEditWidget->setPixmap(pix.scaled(350, 350, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}


QPixmap YLModifyUserIcon::getClipPixmap()
{

}

void YLModifyUserIcon::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor::fromRgb(40, 138, 221));           //#288ADD
    p.drawRect(0, 0, width(), 32);

    p.setBrush(Qt::white);
    p.drawRect(0, 32, width(), height() - 78);
}

void YLModifyUserIcon::on_uploadImage_clicked()
{
    m_file_name = QFileDialog::getOpenFileName(this, "选择图片", QDir::homePath());

    m_pixmap = QPixmap(m_file_name);

    //计算缩放比例
    int pixW = m_pixmap.width();
    int pixH = m_pixmap.height();

    int mini = pixW > pixH ? pixH : pixW;

    qreal rate = 350.0 / mini;

    m_pixmap = m_pixmap.scaled(rate * pixW, rate * pixH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    imageEditWidget->setPixmap(m_pixmap);
}

void YLModifyUserIcon::on_leftRotate_clicked()
{
    imageEditWidget->leftRotate();
}

void YLModifyUserIcon::on_cancel_clicked()
{
    close();
}

void YLModifyUserIcon::on_btnSave_clicked()
{
    emit changeIcon(m_file_name);
    //[1]上传图片。
    HttpHelper httpHelper;
    QString uploadFileName = httpHelper.upload(m_file_name);

    //[2]成功则更改数据库
    QString  url = "http://www.liutimo.cn/images/" + uploadFileName;
    YLBusiness::modifyUserIcon(url);
    //[3]
    close();
}

void YLModifyUserIcon::on_rightRotate_clicked()
{
    imageEditWidget->rightRotate();
}
