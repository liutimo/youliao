#ifndef YLMESSAGEBOX_H
#define YLMESSAGEBOX_H

#include "../YLBasicWidget/ylbasicwidget.h"

class QLabel;
class QPushButton;
class QEventLoop;

typedef enum
{
    ID_OK = 1,
    ID_CANNEL
}BottonResult;

typedef enum
{
    BUTTON_OK = 0x0001,
    BUTTON_CANNEL = 0x0010
}BottonType;

class YLMessageBox : public YLBasicWidget
{
    Q_OBJECT
    const QString qss_btn = "QPushButton{border-radius:3px;background-color:rgb(244 , 244 , 244); border: 1px solid rgb(160 , 150 , 152);}\
                             QPushButton:hover{background-color:rgb(190 , 231 , 253);border: 1px solid rgb(79 , 173 , 216);}\
                             QPushButton:pressed{background-color:rgb(235 , 236 , 237);border: 1px solid rgb(79 , 173 , 216);padding-left:2px;  padding-top:2px;}";
public:        
      typedef enum {
            Tips = 0,
            Error,
            Warn
       }TipType;

    explicit YLMessageBox(int type = BUTTON_OK | BUTTON_CANNEL, QWidget *parent = nullptr);
    BottonResult exec();
    void setToolTip(const QString &toolTip);
    void setIcon(const QString &path);
    void setTipType(TipType type);
protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void init();
    void initButtonOk(const QPoint &p);
    void initButtonCannel(const QPoint &p);

    QLabel       *m_icon;
    QLabel       *m_tooltip;
    QPushButton  *m_ok;
    QPushButton  *m_cannel;
    QEventLoop   *m_event_loop;
    BottonResult  m_botton_reslut;
    int           m_button_type;

    QPoint point1;
    QPoint point2;
};

#endif // YLMESSAGEBOX_H
