#ifndef YLIMAGEEDITWIDGET_H
#define YLIMAGEEDITWIDGET_H

#include <QScrollArea>
class ImageWidget;
class YLImageEditWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit YLImageEditWidget(QWidget *parent = nullptr);
    void setPixmap(const QPixmap &);

    void leftRotate();
    void rightRotate();

protected:
    //重载鼠标事件实现通过鼠标移动图片
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

protected:
    void paintEvent(QPaintEvent *event);

public:
    ImageWidget *imageWidget;

private:
    QPixmap     m_pixmap;
    bool m_left_pressed;
    bool m_loop;
    qint32 m_pressed_x;     //鼠标按下时的x
    qint32 m_pressed_y;     //鼠标按下时的y
    qint32 m_h_value;
    qint32 m_v_value;
    qint32 m_x_offest;
    qint32 m_y_offest;
};


class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = nullptr);

    //设置图片
    void setPixmap(const QString &fileName);
    void setPixmap(const QPixmap &pixmap);

    void zoomInPixmap();                                    //缩小图片
    void zoomOutPixmap();                                   //放大图片
protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap  m_pixmap;
};

#endif // YLIMAGEEDITWIDGET_H
