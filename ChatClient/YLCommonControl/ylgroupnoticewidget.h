#ifndef YLGROUPNOTICEWIDGET_H
#define YLGROUPNOTICEWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QListWidget;
QT_END_NAMESPACE

class YLGroupNoticeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YLGroupNoticeWidget(QWidget *parent = nullptr);

signals:

private:
    void init();

private:
    QLabel          *m_title;
    QListWidget     *m_list_widget;
};

#endif // YLGROUPNOTICEWIDGET_H
