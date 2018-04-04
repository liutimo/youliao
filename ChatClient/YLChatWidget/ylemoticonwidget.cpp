#include "ylemoticonwidget.h"
#include <QLabel>
#include <QTableWidget>
#include <QMovie>
#include <QHeaderView>
#include <QFocusEvent>

bool YLEmoticonWidget::isShow = false;

YLEmoticonWidget::YLEmoticonWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    init();
    isShow = false;
}


void YLEmoticonWidget::init()
{
    m_title_label = new QLabel("Emoticon", this);
    m_title_label->move(2,2);

    int row = 213 % 12 ? 213 / 12 + 1 : 213 / 12;
    int cloumn = 12;

    m_emoticon_tablewidget = new QTableWidget(row, cloumn, this);
    m_emoticon_tablewidget->move(2, 30);
    m_emoticon_tablewidget->resize(375, 200);
    m_emoticon_tablewidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_emoticon_tablewidget->horizontalHeader()->hide();
    m_emoticon_tablewidget->verticalHeader()->hide();
    m_emoticon_tablewidget->horizontalHeader()->setDefaultSectionSize(30);
    m_emoticon_tablewidget->verticalHeader()->setDefaultSectionSize(30);
    m_emoticon_tablewidget->setObjectName("EmoticonTableWidget");
    m_emoticon_tablewidget->setFocusPolicy(Qt::NoFocus);
    m_emoticon_tablewidget->setStyleSheet(m_qss_emoticon);

    for (int r = 0; r < row; ++r)
    {
        for (int c = 0; c < cloumn; ++c)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            YLEmoticonLabel *l = new YLEmoticonLabel;
            l->setEmoticon(r * 12 + c);
            m_emoticon_tablewidget->setCellWidget(r, c, l);
            m_emoticon_tablewidget->setItem(r, c, item);
        }
    }

    connect(m_emoticon_tablewidget, &QTableWidget::cellPressed, [this](int row, int cloumn){
        emit selected(row * 12 + cloumn);
        isShow = false;
        this->close();
    });

}




////////////////////////////////////////////////////////////////
YLEmoticonLabel::YLEmoticonLabel(QWidget *parent) : QLabel(parent)
{
    setMouseTracking(true);
    m_emoticon_movie = Q_NULLPTR;
}

void YLEmoticonLabel::setEmoticon(int index)
{

    QString path = ":/res/YLChatWidget/face/" + QString::number(index) + ".gif";
    m_emoticon_movie = new QMovie(path);
    setMovie(m_emoticon_movie);
    m_emoticon_movie->start();
    m_emoticon_movie->stop();
    m_emoticon_movie->jumpToFrame(0);
    m_emoticon_movie->setScaledSize(QSize(28, 28));
}

void YLEmoticonLabel::enterEvent(QEvent *e)
{
    if (m_emoticon_movie != Q_NULLPTR)
        m_emoticon_movie->start();
    QLabel::enterEvent(e);
}

void YLEmoticonLabel::leaveEvent(QEvent *e)
{
    if (m_emoticon_movie != Q_NULLPTR)
    {
        m_emoticon_movie->stop();
        m_emoticon_movie->jumpToFrame(0);
    }
    QLabel::leaveEvent(e);
}

void YLEmoticonLabel::mouseReleaseEvent(QMouseEvent *e)
{
    //
    QLabel::mouseReleaseEvent(e);
}
