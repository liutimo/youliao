#include "ylmessageeditwidget.h"
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QDebug>
YLMessageEditWidget::YLMessageEditWidget(QWidget *parent)
    : QTextEdit(parent)
{
    setAcceptRichText(true);
    initMenu();
    QFont f = font();
    f.setPixelSize(24);
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

    connect(m_action_cpoy, &QAction::triggered, this, &YLMessageEditWidget::slotCopy);
    connect(m_action_cut, &QAction::triggered, this, &YLMessageEditWidget::slotCut);
    connect(m_action_paste, &QAction::triggered, this, &YLMessageEditWidget::slotPaste);
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


///slots
void YLMessageEditWidget::slotCopy()
{
    copy();
}

void YLMessageEditWidget::slotCut()
{
    cut();
}

void YLMessageEditWidget::slotPaste()
{
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mime_data = clipboard->mimeData();

    if (mime_data->hasImage())
    {
        QPixmap pixmap = qvariant_cast<QPixmap>(mime_data->imageData());
        pixmap.save("a.jpg");
        insertHtml("<img src=\"file:///home/liuzheng/Documents/Code/build-ChatClient-Desktop_Qt_5_9_0_GCC_64bit-Debug/a.jpg\">");
    }
    else if (mime_data->hasText())
    {
        //paste text
        qDebug() << 2;
        insertHtml(mime_data->text());
    }
    else if (mime_data->hasHtml())
    {
        //paste html
        qDebug() << 3;
        paste();
    }

    qDebug() << toHtml();
    qDebug() << "-----------------------------";
    qDebug() << toPlainText();

}
