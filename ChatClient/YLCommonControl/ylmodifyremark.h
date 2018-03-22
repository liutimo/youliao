#ifndef YLMODIFYREMARK_H
#define YLMODIFYREMARK_H

#include "ylmessagebox.h"
class QLineEdit;
class YLModifyRemarkWidget : public YLMessageBox
{
    Q_OBJECT
public:
    explicit YLModifyRemarkWidget(QWidget *parent = nullptr);
    void setDefalutText(const QString &);
signals:

public slots:

private:
    void init();

    QLabel    *m_tip;
    QLineEdit *m_lineedit;
};

#endif // YLMODIFYREMARK_H
