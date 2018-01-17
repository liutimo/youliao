#ifndef YLNAVIGATIONBAR_H
#define YLNAVIGATIONBAR_H

#include <QWidget>

class QToolButton;

class YLNavigationBar : public QWidget
{
    Q_OBJECT
public:
    explicit YLNavigationBar(QWidget *parent = nullptr);

private:

    const QString qss_selected = "QToolButton{border:0px;border-bottom:2px solid red;color:gray;color:red;font: 14px solid 黑体;}"
                                 "QToolButton:hover{border:0px;border-bottom:2px solid red; color:red;font: 14px solid 黑体;}";

    const QString qss_no_selected = "QToolButton{border:0px;color:gray;font: 14px solid 黑体;}"
                                    "QToolButton:hover{border:0px;color:black;font: 14px solid 黑体;}";

    void init();

protected:
    void resizeEvent(QResizeEvent *event);
signals:
    void click_index(int);
private slots:
    void on_clicked();
private:
    QToolButton *toolbutton_message_;
    QToolButton *toolbutton_friend_;
    QToolButton *toolbutton_group_;
};

#endif // YLNAVIGATIONBAR_H
