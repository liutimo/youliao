#ifndef YLSIGNATURELINEEDIT_H
#define YLSIGNATURELINEEDIT_H

#include <QLineEdit>

class YLSignatureLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    YLSignatureLineEdit(QWidget *parent = nullptr);

private:
    const QString qss_this_on_edit = "QLineEdit#YLSignatureLineEdit_this{border:0px; font:14px bold 黑体;background-color:rgba(255, 255, 255, 255);}";
    const QString qss_this_no_edit = "QLineEdit#YLSignatureLineEdit_this{border:0px; font:14px bold 黑体;background-color:rgba(255, 255, 255, 0);}";

protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

private:

};

#endif // YLSIGNATURELINEEDIT_H
