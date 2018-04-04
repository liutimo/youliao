#ifndef YLQUCIKBAR_H
#define YLQUCIKBAR_H

#include <QWidget>


class QPushButton;
class YLEmoticonWidget;

class YLQuickBar : public QWidget
{
    Q_OBJECT
    const QString m_qss_face_btn   = "  QPushButton#face_btn        {border-image:url(:/res/YLChatWidget/aio_quickbar_face.png);}\
                                        QPushButton#face_btn:hover  {border-image:url(:/res/YLChatWidget/aio_quickbar_face_hover.png);}\
                                        QPushButton#face_btn:pressed{border-image:url(:/res/YLChatWidget/aio_quickbar_face_selected.png);}\
                                        ";
public:
    explicit YLQuickBar(QWidget *parent = nullptr);
    YLEmoticonWidget* getEmoticonWidget() {return m_emoticon_widget;}

private:
    void init();
signals:

public slots:

private:
    QPushButton *m_face_btn;
    YLEmoticonWidget *m_emoticon_widget;
};

#endif // YLQUCIKBAR_H
