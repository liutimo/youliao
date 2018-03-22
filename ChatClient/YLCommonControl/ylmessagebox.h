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

class YLMessageBox : public YLBasicWidget
{
    Q_OBJECT
    const QString qss_btn = "QPushButton{border-radius:3px;background-color:rgb(244 , 244 , 244); border: 1px solid rgb(160 , 150 , 152);}\
                             QPushButton:hover{background-color:rgb(190 , 231 , 253);border: 1px solid rgb(79 , 173 , 216);}\
                             QPushButton:pressed{background-color:rgb(235 , 236 , 237);border: 1px solid rgb(79 , 173 , 216);padding-left:2px;  padding-top:2px;}";
public:


    explicit YLMessageBox(QWidget *parent = nullptr);
    BottonResult exec();
    void setTitle(const QString &title);

protected:
    void paintEvent(QPaintEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void init();

    QLabel       *m_title;
    QPushButton  *m_ok;
    QPushButton  *m_cannel;
    QEventLoop   *m_event_loop;
    BottonResult  m_botton_reslut;
};

#endif // YLMESSAGEBOX_H
