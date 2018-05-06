#ifndef YLCONFIRMWIDGET_H
#define YLCONFIRMWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
QT_END_NAMESPACE

class YLConfirmWidget : public YLBasicWidget
{
    Q_OBJECT
    const QString qss_confirm_button =  "QPushButton        {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btn_focus_normal.png);}\
                                        QPushButton:hover  {border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btn_focus_highlight.png);}\
                                        QPushButton:pressed{border-image:url(:/res/YLAddFriendWIdgets/AddBuddy/btn_focus_down.png);}\
                                        ";
public:
    explicit YLConfirmWidget(QWidget *parent = nullptr);
    ~YLConfirmWidget();
    void setOtherId(uint32_t id) { m_other_id = id; }
signals:
    void complete();
private:
    QLabel *m_remark;
    QLabel *m_group;
    QLineEdit *m_line_edit;
    QComboBox *m_combo_box;
    QPushButton *m_confirm;

    uint32_t m_other_id;
};

#endif // YLCONFIRMWIDGET_H
