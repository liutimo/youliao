#ifndef YLMESSAGEEDITWIDGET_H
#define YLMESSAGEEDITWIDGET_H

#include <QWidget>

#include <QTextEdit>

class QMenu;
class QAction;

class YLMessageEditWidget : public QTextEdit
{
    Q_OBJECT

public:
    explicit YLMessageEditWidget(QWidget *parent = Q_NULLPTR);
    virtual ~YLMessageEditWidget();
    //获取关键html代码
    QString getContent() const;
    //添加系统表情

    void addEmoticon(int index);

signals:
    void enterPress();

private:
    void initMenu();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

    bool canInsertFromMimeData(const QMimeData *source) const override;
    void insertFromMimeData(const QMimeData *source) override;

private:
    QMenu	*m_menu;
    QAction *m_action_cpoy;
    QAction *m_action_paste;
    QAction *m_action_cut;

    QString str1 = "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">";
    QString str2 = "<br />";
    QString str3 = "</p>";
    QString str4 = "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">";
};

#endif // YLMESSAGEEDITWIDGET_H
