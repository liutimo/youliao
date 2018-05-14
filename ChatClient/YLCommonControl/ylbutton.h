#ifndef YLBUTTON_H
#define YLBUTTON_H

#include <QPushButton>
#include <QPixmap>
class YLButton : public QPushButton
{
    Q_OBJECT
public:
    explicit YLButton(QWidget *parent = nullptr);
    void setImage(const QString &image);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void focusOutEvent(QFocusEvent *e);
private:
    QPixmap m_pixmap;
    bool m_clicked;
    bool m_has_menu;
};

#endif // YLBUTTON_H
