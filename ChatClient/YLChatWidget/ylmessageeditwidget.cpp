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
    //setHtml("<img src=\"file:///C:\\Users\\lz153\\Pictures\\1.png\">");
}

void YLMessageEditWidget::initMenu()
{
    m_menu = new QMenu(this);
    m_action_cpoy = new QAction("复制");
    m_action_cut = new QAction("剪切");
    m_action__paste = new QAction("粘贴");

    m_menu->addAction(m_action_cpoy);
    m_menu->addAction(m_action_cut);
    m_menu->addAction(m_action__paste);

    connect(m_action_cpoy, &QAction::triggered, this, &YLMessageEditWidget::slotCopy);
    connect(m_action_cut, &QAction::triggered, this, &YLMessageEditWidget::slotCut);
    connect(m_action__paste, &QAction::triggered, this, &YLMessageEditWidget::slotPaste);
}



QString YLMessageEditWidget::getContent() const
{
    return QString();
}


void YLMessageEditWidget::addEmoticon(int index)
{

}

////event

void YLMessageEditWidget::keyPressEvent(QKeyEvent* event)
{
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
        //paste a image
        qDebug() << 1;
        insertHtml("<img src=\"qrc:/res/2.jpeg\">");
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
