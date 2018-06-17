#ifndef YLVALIDATEGROUPWIDGET_H
#define YLVALIDATEGROUPWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"
#include "YLEntityObject/ylgroup.h"
QT_BEGIN_NAMESPACE
class QLabel;
class YLHeadFrame;
class QPushButton;
class QTextEdit;
class QLineEdit;
class QComboBox;
QT_END_NAMESPACE
class YLValidateGroupWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLValidateGroupWidget(QWidget *parent = nullptr);
    ~YLValidateGroupWidget();
    void setGroup(const YLGroup &group);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void next();
private:
    YLGroup m_group;

    void initLeft();
    void initRight();
    void initBottom();

    //left
    YLHeadFrame *m_head_frame;
    QLabel *m_group_name;
    QLabel *m_group_id;
    QLabel *m_group_member_count;
    QLabel *m_group_intro;

    //right1;
    QLabel *m_tip;
    QTextEdit *m_text_eidt;
    QLabel *m_info;
    QLabel *m_icon;

    //bottom
    QPushButton *m_next;
    QPushButton *m_cancel;

    //record current index
    int m_index;
};

#endif // YLVALIDATEGROUPWIDGET_H
