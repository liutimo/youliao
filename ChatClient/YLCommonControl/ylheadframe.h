#ifndef YLHEADFRAME_H
#define YLHEADFRAME_H

/*
 *用于显示用户头像。
 */

#include <QLabel>
#include <QUrl>

class QToolButton;
class QMenu;
class YLHeadFrame : public QLabel
{
    Q_OBJECT
public:

    explicit YLHeadFrame(QWidget *parent = nullptr);

    void setHeadFromLocal(const QString &path);
    void setHeadFromUrl(const QUrl &url);

protected:
    void paintEvent(QPaintEvent *e);

private:

    QUrl url_;
    QString path_;
};

#endif // YLHEADFRAME_H
