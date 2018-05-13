#ifndef YLSINGLECHATWIDGET_H
#define YLSINGLECHATWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class YLMessageView;
class QPushButton;
class YLMessageEditWidget;
QT_END_NAMESPACE

class YLSingleChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit YLSingleChatWidget(QWidget *parent = nullptr);

signals:

protected:
    void paintEvent(QPaintEvent *event);

private:
    void init();

public slots:


private:
    QLabel                  *m_label;           //top bar
    QLabel                  *m_label2;          //mid bar
    YLMessageView           *m_meesage_view;
    YLMessageEditWidget     *m_meesage_edit_widget;
    QPushButton             *m_send_button;
    QPushButton             *m_close_button;
};

#endif // YLSINGLECHATWIDGET_H
