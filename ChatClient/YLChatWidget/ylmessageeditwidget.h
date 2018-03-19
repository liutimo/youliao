#ifndef YLMESSAGEEDITWIDGET_H
#define YLMESSAGEEDITWIDGET_H

#include <QWidget>

class QPushButton;
class QTextEdit;
class YLMessageEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YLMessageEditWidget(QWidget *parent = nullptr);

signals:

public slots:
protected:
    void resizeEvent(QResizeEvent *event);
private:
    QTextEdit       *m_text_editor;
    QPushButton     *m_send_button;
    QPushButton     *m_close_bitton;
};

#endif // YLMESSAGEEDITWIDGET_H
