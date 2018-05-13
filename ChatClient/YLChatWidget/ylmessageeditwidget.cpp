#include "ylmessageeditwidget.h"
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QDebug>
#include <QTextDocumentFragment>
#include <QDateTime>
#include <QCryptographicHash>
YLMessageEditWidget::YLMessageEditWidget(QWidget *parent)
    : QTextEdit(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background:transparent;");
    setAcceptRichText(true);
    initMenu();
    QFont f = font();
    f.setPixelSize(12);
    setFont(f);
}

YLMessageEditWidget::~YLMessageEditWidget()
{
    delete m_action_cpoy;
    delete m_action_cut;
    delete m_action_paste;

    qDebug() << "~YLMessageEditWidget()";
}

void YLMessageEditWidget::initMenu()
{
    m_menu = new QMenu(this);
    m_action_cpoy = new QAction("复制");
    m_action_cut = new QAction("剪切");
    m_action_paste = new QAction("粘贴");

    m_menu->addAction(m_action_cpoy);
    m_menu->addAction(m_action_cut);
    m_menu->addAction(m_action_paste);

    connect(m_action_cpoy, &QAction::triggered, this, &YLMessageEditWidget::copy);
    connect(m_action_cut, &QAction::triggered, this, &YLMessageEditWidget::cut);
    connect(m_action_paste, &QAction::triggered, this, &YLMessageEditWidget::paste);
}



QString YLMessageEditWidget::getContent() const
{
    QString pattern("<p .*>(.*)</p>");
    QRegExp re(pattern);
    int pos = toHtml().indexOf(re);
    QString  content = re.cap(1);
    content.replace(str1, "");
    content.replace(str2, "");
    content.replace(str3, "");
    content.replace(str4, "");
    content.replace("\n", "<br />");

    content.replace("\"", "'");

    return content;
}


void YLMessageEditWidget::addEmoticon(int index)
{
    insertHtml(QString("<img src='qrc:/res/YLChatWidget/face/%1.gif' />").arg(index));
}

////event

void YLMessageEditWidget::keyPressEvent(QKeyEvent* event)
{
    if(event->key() ==  Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        emit enterPress();
    }
    else
        QTextEdit::keyPressEvent(event);
}


void YLMessageEditWidget::contextMenuEvent(QContextMenuEvent *event)
{
    m_menu->exec(event->globalPos());
}



bool YLMessageEditWidget::canInsertFromMimeData(const QMimeData *source) const
{
    return source->hasImage() || source->hasUrls() || QTextEdit::canInsertFromMimeData(source);
}

void YLMessageEditWidget::insertFromMimeData(const QMimeData *source)
{
    //may be consider calculate MD5 to determime this image whether exists.
    if (source->hasImage())
    {
        QPixmap pixmap = qvariant_cast<QPixmap>(source->imageData());

        QString fileName = "/home/liuzheng/Documents/youliao/TEMP.png";
        pixmap.save(fileName);

        QFile file(fileName);
        file.open(QIODevice::ReadOnly);

        QString strHash(QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex());
        qDebug() << strHash;
        fileName = "/home/liuzheng/Documents/youliao/" + strHash + ".png";
        QFile f(fileName);
        if (!f.exists())
            pixmap.save(fileName);

        int w = pixmap.width();
        int h = pixmap.height();

        float scaledTimes = qMax(w, h) / 150.0;

        if (qMax(w, h) > 150)
        {
            w /= scaledTimes;
            h /= scaledTimes;
        }
        insertHtml(QString("<img width=\"%1\" height=\"%2\" src=\"file://%3\" >").arg(w).arg(h).arg(fileName));
    }
    else if (source->hasText())
    {
        insertHtml(source->text());
    }
    else if (source->hasHtml())
    {
        paste();
    }
}
