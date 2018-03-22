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

    //获取关键html代码
    QString getContent() const;

    //添加系统表情
    void addEmoticon(int index);

private:
    void initMenu();

private slots:
    void slotCopy();
    void slotCut();
    void slotPaste();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    QMenu	*m_menu;
    QAction *m_action_cpoy;
    QAction *m_action__paste;
    QAction *m_action_cut;

};

#endif // YLMESSAGEEDITWIDGET_H
