#include "ylheadframe.h"
#include <QPainter>
#include <QToolButton>
#include <QMenu>
#include <QDebug>
YLHeadFrame::YLHeadFrame(QWidget *parent) : QLabel(parent), m_online(false)
{
    resize(120, 120);
    m_http = new HttpHelper(this);
    connect(m_http, &HttpHelper::downloadFinshed, this, [this](){
        setHeadFromLocal(m_http->getFilename());
    });
}

void YLHeadFrame::setHeadFromLocal(const QString &path, bool online)
{
    m_online = online;
    path_ = path;
    update();
}

void YLHeadFrame::setHeadFromUrl(const QUrl &url)
{
    url_ = url;
    m_http->download(url_.toString());
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

    QImage image(path_.isEmpty() ? ":/res/1.jpg" : path_);
    if (!m_online)
        image = image.convertToFormat(QImage::Format_Grayscale8);

    QPixmap pix(QPixmap::fromImage(image));

    p.drawPixmap(2, 2, width() - 4, height() - 4,
                 pix.scaled(width() - 6, height() - 6,
                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}




