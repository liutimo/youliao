#ifndef YLMODIFYUSERICON_H
#define YLMODIFYUSERICON_H

#include "YLBasicWidget/ylbasicwidget.h"
#include "ui_uploadheadicon.h"
#include "ylimageeditwidget.h"
#include <QPainter>
namespace Ui{
class UploadHeadIcon;
}
class MaskWidget;

class YLModifyUserIcon : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLModifyUserIcon(QWidget *parent = nullptr);
    void setUserIcon(const QString &);
    QPixmap getClipPixmap();

signals:
    void changeIcon(const QString &);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_uploadImage_clicked();

    void on_leftRotate_clicked();

    void on_cancel_clicked();

    void on_btnSave_clicked();

    void on_rightRotate_clicked();

private:
    Ui::UploadHeadIcon  *ui;
    QPixmap m_pixmap;
    QPixmap m_temp;
    qint32  m_angle;        //旋转角度  0 90 180 270
    YLImageEditWidget *imageEditWidget;
    QString m_file_name;
    MaskWidget *m_mask_widget;
};

class MaskWidget : public QWidget
{
    Q_OBJECT
public:
    MaskWidget(QWidget *parent = Q_NULLPTR) : QWidget(parent)
    {
        setMouseTracking(true);
    }


protected:
    void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.setPen(Qt::NoPen);
        p.drawPixmap(0, 0, 350, 350, QPixmap(":/res/headicon/CircleMask.png").scaled(350, 350, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }

};

#endif // YLMODIFYUSERICON_H
