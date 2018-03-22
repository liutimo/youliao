#include "ylmessagebox.h"
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QEventLoop>
YLMessageBox::YLMessageBox(QWidget *parent) : YLBasicWidget(parent)
{
    setFixedSize(350, 180);
    init();
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::Window);
}


void YLMessageBox::init()
{
    m_title = new QLabel("删除好友", this);
    m_title->move(5, 5);
    m_title->setStyleSheet("color:white; font:14px;");

    m_ok = new QPushButton("确定", this);
    m_ok->setFixedSize(70, 28);
    m_ok->move(190, 147);
    m_ok->setStyleSheet(qss_btn);
    connect(m_ok, &QPushButton::clicked, this, [this](){
        m_botton_reslut = ID_OK;
        close();
    });

    m_cannel = new QPushButton("取消", this);
    m_cannel->setFixedSize(70, 28);
    m_cannel->move(270, 147);
    m_cannel->setStyleSheet(qss_btn);
    connect(m_cannel, &QPushButton::clicked, this, [this](){
        m_botton_reslut = ID_CANNEL;
        close();
    });
}

BottonResult YLMessageBox::exec()
{
    setWindowModality(Qt::ApplicationModal);

    show();
    m_event_loop = new QEventLoop(this);
    m_event_loop->exec();

    return m_botton_reslut;
}

void YLMessageBox::setTitle(const QString &title)
{
    m_title->setText(title);
}

void YLMessageBox::paintEvent(QPaintEvent *event)
{
    const int titleBarHeight = 32;
    const int bottomBtnHeight = 36;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);


    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    painter.setBrush(QColor::fromRgb(40, 138, 221, 122));
    painter.drawRect(0, 0, width(), titleBarHeight);

    painter.setBrush(QColor::fromRgb(200, 200, 200, 122));
    painter.drawRect(0, height() - bottomBtnHeight, width(), bottomBtnHeight);
}

void YLMessageBox::closeEvent(QCloseEvent *event)
{
    if (m_event_loop != nullptr)
        m_event_loop->exit();

    YLBasicWidget::closeEvent(event);
}

