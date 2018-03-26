#include "ylmessagebox.h"
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QEventLoop>
YLMessageBox::YLMessageBox(int type, QWidget *parent) : YLBasicWidget(parent), m_button_type(type)
{
    setFixedSize(350, 180);
    point1 = QPoint(190, 147);
    point2 = QPoint(270, 147);

    init();
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::Window);
}


void YLMessageBox::init()
{
    m_title = new QLabel("删除好友", this);
    m_title->move(5, 5);
    m_title->setStyleSheet("color:white; font:14px;");

    if ((m_button_type & BUTTON_OK) && (m_button_type & BUTTON_CANNEL))
    {
        initButtonOk(point1);
        initButtonCannel(point2);
    }
    else if (m_button_type & BUTTON_OK)
    {
        initButtonOk(point2);
    }
    else if (m_button_type & BUTTON_CANNEL)
    {
        initButtonCannel(point2);
    }
}

void YLMessageBox::initButtonOk(const QPoint &p)
{
    m_ok = new QPushButton("确定", this);
    m_ok->setFixedSize(70, 28);
    m_ok->move(p);
    m_ok->setStyleSheet(qss_btn);
    connect(m_ok, &QPushButton::clicked, this, [this](){
        m_botton_reslut = ID_OK;
        close();
    });
}


void YLMessageBox::initButtonCannel(const QPoint &p)
{
    m_cannel = new QPushButton("取消", this);
    m_cannel->setFixedSize(70, 28);
    m_cannel->move(p);
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

void YLMessageBox::setToolTip(const QString &toolTip)
{
    m_tooltip = new QLabel(this);
    m_tooltip->setStyleSheet("font:16px");
    m_tooltip->move(50, 67);
    m_tooltip->setText(toolTip);
}
