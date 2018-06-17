#ifndef YLHEADFRAME_H
#define YLHEADFRAME_H

/*
 *用于显示用户头像。
 */

#include <QLabel>
#include <QUrl>
#include "YLNetWork/http/httphelper.h"
class QToolButton;
class QMenu;
class YLHeadFrame : public QLabel
{
    Q_OBJECT
public:

    explicit YLHeadFrame(QWidget *parent = nullptr);

    void setHeadFromLocal(const QString &path, bool online = true);
    void setHeadFromUrl(const QUrl &url, bool online = true);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void clicked();

private:

    QUrl url_;
    QString path_;
    bool m_online;
    HttpHelper *m_http;
};

#endif // YLHEADFRAME_H
