#include "ylmodifyremark.h"
#include <QLabel>
#include <QLineEdit>

YLModifyRemarkWidget::YLModifyRemarkWidget(QWidget *parent) : YLMessageBox(BUTTON_OK | BUTTON_CANNEL, parent)
{
    init();
}

void YLModifyRemarkWidget::init()
{
    setTitle("修改备注姓名");

    m_tip = new QLabel("请输入备注姓名:", this);
    m_tip->setStyleSheet("font:14px;");
    m_tip->move(25, 60);

    m_lineedit = new QLineEdit(this);
    m_lineedit->setFixedSize(width() - 50, 32);

    m_lineedit->move(25, 82);
}

void YLModifyRemarkWidget::setDefalutText(const QString &text)
{
    m_lineedit->setText(text);
    m_lineedit->selectAll();
}
