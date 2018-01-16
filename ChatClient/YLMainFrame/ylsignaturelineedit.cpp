#include "ylsignaturelineedit.h"

YLSignatureLineEdit::YLSignatureLineEdit(QWidget *parent) : QLineEdit(parent)
{
    setObjectName("YLSignatureLineEdit_this");
    setStyleSheet(qss_this_no_edit);
}

void YLSignatureLineEdit::focusInEvent(QFocusEvent *event)
{

    setStyleSheet(qss_this_on_edit);
    QLineEdit::focusInEvent(event);
}

void YLSignatureLineEdit::focusOutEvent(QFocusEvent *event)
{
    setStyleSheet(qss_this_no_edit);

    QLineEdit::focusOutEvent(event);
}

void YLSignatureLineEdit::mouseMoveEvent(QMouseEvent *event)
{

    QLineEdit::mouseMoveEvent(event);
}
