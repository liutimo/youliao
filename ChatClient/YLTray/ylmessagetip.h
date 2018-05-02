#ifndef YLMESSAGETIP_H
#define YLMESSAGETIP_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLabel;
class QListWidget;
QT_END_NAMESPACE

class YLMessageTip : public QWidget
{
    Q_OBJECT
    const QString qss_button = "QPushButton{border:0px; color:#1DB0B8;}"
                               "QPushButton:hover{border:0px; color:#37C6C0;}";
public:
    static YLMessageTip *instance();
    void updateList();
signals:
    void readAll();
    void ignoreAll();
public slots:

private:
    void init();
    void initTop();
    void initMiddle();
    void initBottom();

    YLMessageTip(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    static YLMessageTip *m_instance;
    QLabel *m_title;

    QPushButton *m_ignore_all;
    QPushButton *m_show_all;

    QListWidget *m_list_widget;
};

#endif // YLMESSAGETIP_H
