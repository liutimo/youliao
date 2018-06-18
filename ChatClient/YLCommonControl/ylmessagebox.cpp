#include "ylmessagebox.h"
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QEventLoop>
YLMessageBox::YLMessageBox(int type, QWidget *parent) : YLBasicWidget(parent), m_button_type(type)
{
    setFixedSize(350, 160);
    setWidgetIcon(":/res/qqlogo.png");
    setWidgetTitle("提示");
    m_icon = new QLabel(this);
    m_icon->setFixedSize(40, 40);
    m_icon->move(20, 57);

    m_tooltip = new QLabel(this);
    m_tooltip->setFixedSize(250, 92);
    m_tooltip->setWordWrap(true);
    m_tooltip->setAlignment(Qt::AlignVCenter);
    m_tooltip->setStyleSheet("font:12px");
    m_tooltip->move(70, 30);

    point1 = QPoint(190, 130);
    point2 = QPoint(270, 130);

    init();
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::Window);
}


void YLMessageBox::init()
{
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
    m_ok->setFixedSize(68, 23);
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
    m_cannel->setFixedSize(68, 23);
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
void YLMessageBox::setTipType(TipType type)
{
    QString filePath;
    switch (type) {
    case Tips:
        filePath = ":/res/MessageBox/sysmessagebox_inforFile.png";
        break;
    case Error:
        filePath = ":/res/MessageBox/sysmessagebox_errorFile.png";
        break;
    case Warn:
        filePath = ":/res/MessageBox/sysmessagebox_warningFile.png";
        break;
    default:
        filePath = ":/res/MessageBox/sysmessagebox_inforFile.png";
        break;
    }

    setIcon(filePath);

}

void YLMessageBox::paintEvent(QPaintEvent *event)
{
    const int titleBarHeight = 32;
    const int bottomBtnHeight = 36;

    QPainter painter(this);
    painter.setPen(Qt::NoPen);


    painter.setBrush(Qt::white);
    painter.drawRect(rect());

    painter.setBrush(QColor::fromRgb(40, 138, 221));           //#288ADD
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
    m_tooltip->setText(toolTip);
}


void YLMessageBox::setIcon(const QString &path)
{
    m_icon->setPixmap(QPixmap(path));
}
