#ifndef YLMENUBUTTON_H
#define YLMENUBUTTON_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QMenu;
QT_END_NAMESPACE

class YLMenuButton : public QWidget
{
    Q_OBJECT
    const QString qss_custom_button_ = "QPushButton        {border-image:url(%1);}\
                                        QPushButton:hover  {border-image:url(%2);}\
                                        QPushButton:pressed{border-image:url(%3);}\
                                        ";
public:
    explicit YLMenuButton(QWidget *parent = nullptr);
    void setSize(const QSize& left, const QSize &right);
    void setIcon(const QString &leftIcon, const QString &rightIcon);
    void setHoverColor(const QColor &color);
    void setNormalColor(const QColor &color);
    void setPressedColor(const QColor &color);
    void setMenu(QMenu *menu);
signals:

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *event);
private slots:
    void showMenu();

private:
    typedef enum {HOVER, PRESSED, NORMAL} Status;
    void init();


private:
    Status m_status;
    QMenu *m_menu;
    QPushButton *m_left_button;
    QPushButton *m_right_arrow;

    QSize m_left_size;
    QSize m_right_size;

    bool m_menu_init;

    QColor m_hover_color, m_pressed_color, m_normal_color;
};

#endif // YLMENUBUTTON_H
