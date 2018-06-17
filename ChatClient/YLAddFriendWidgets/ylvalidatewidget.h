#ifndef YLVALIDATEWIDGET_H
#define YLVALIDATEWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"
#include "YLEntityObject/ylfriend.h"

class QLabel;
class YLHeadFrame;
class QPushButton;
class QTextEdit;
class QLineEdit;
class QComboBox;
class YLValidateWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLValidateWidget(QWidget *parent = nullptr);
    ~YLValidateWidget();
    void setFriend(const YLFriend &fri) { m_friend = fri; }

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void next();
private:
    YLFriend m_friend;

    void initLeft();
    void initRight1();
    void initRight2();
    void initRight3();
    void initBottom();

    void right1Hide();
    void right2Hide();
    void right2Show();
    void right3Hide();
    void right3Show();

    //left
    YLHeadFrame *m_head_frame;
    QLabel *m_info;

    //right1;
    QLabel *m_tip;
    QTextEdit *m_text_eidt;

    //right2;
    QLabel *m_remark;
    QLabel *m_group;
    QLineEdit *m_line_edit;
    QComboBox *m_combo_box;


    //right3
    QLabel *m_result;

    //bottom
    QPushButton *m_next;
    QPushButton *m_cancel;

    //record current index
    int m_index;
};

#endif // YLVALIDATEWIDGET_H
