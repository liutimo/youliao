#include "ylheadframe.h"
#include <QPainter>
#include <QToolButton>
#include <QMenu>
#include <QDebug>
YLHeadFrame::YLHeadFrame(QWidget *parent) : QLabel(parent)
{
    resize(120, 120);
}

void YLHeadFrame::setHeadFromLocal(const QString &path)
{
    path_ = path;
    update();
}

void YLHeadFrame::setHeadFromUrl(const QUrl &url)
{
    url_ = url;
    update();
}

void YLHeadFrame::paintEvent(QPaintEvent *e)
{

    QPainter p(this);
    p.setPen(Qt::NoPen);
    p.setRenderHint(QPainter::Antialiasing);
    p.drawEllipse(1, 1, width() - 2, height() - 2);

    QPainterPath path;
    path.addEllipse(2, 2, width() - 4, height() - 4);

    p.setClipPath(path);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.drawPixmap(2, 2, width() - 4, height() - 4,
                 QPixmap(path_.isEmpty() ? ":/res/1.jpg" : path_).scaled(width() - 6, height() - 6,
                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}




