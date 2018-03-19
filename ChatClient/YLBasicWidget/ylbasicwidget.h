#ifndef YLBASICWIDGET_H
#define YLBASICWIDGET_H

#include <QWidget>


class QPushButton;


class YLBasicWidget : public QWidget
{
    Q_OBJECT
private:
    const QString qss_close_button = "QPushButton#close_button_        {border-image:url(:/res/sysbtn_close_normal.png);}\
                                      QPushButton#close_button_:hover  {border-image:url(:/res/sysbtn_close_hover.png);}\
                                      QPushButton#close_button_:pressed{border-image:url(:/res/sysbtn_close_down.png);}\
                                      ";
    void init();

public:
    explicit YLBasicWidget(QWidget *parent = nullptr);

    /*
     *设置是否允许窗口拖动, 默认为允许
     */
    void setWidgetDraged(bool flag = true);

private slots:
    void on_close();

protected:
    void resizeEvent      (QResizeEvent *event);
    void mousePressEvent  (QMouseEvent  *event);
    void mouseReleaseEvent(QMouseEvent  *event);
    void mouseMoveEvent   (QMouseEvent  *event);

protected:
    QPushButton *close_button_;

    bool drag_flag_;
    bool pressed_flag_;

    QPoint begin_pos_;
};

#endif // YLBASICWIDGET_H
