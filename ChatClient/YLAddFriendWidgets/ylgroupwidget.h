#ifndef YLGROUPINFOWIDGET_H
#define YLGROUPINFOWIDGET_H

#include <QWidget>
#include "YLEntityObject/ylgroup.h"
QT_BEGIN_NAMESPACE
class YLHeadFrame;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class YLGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YLGroupWidget(QWidget *parent = nullptr);
    void setGroup(const YLGroup &group);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void init();

private:
    YLHeadFrame *m_head_frame;
    QLabel      *m_group_name;
    QLabel      *m_group_member_icon;
    QLabel      *m_group_member_count;
    QLabel      *m_group_intro;
    QPushButton *m_add_group;

    YLGroup m_group;
};

#endif // YLGROUPINFOWIDGET_H
