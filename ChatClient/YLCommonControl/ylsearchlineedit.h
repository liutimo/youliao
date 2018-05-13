#ifndef YLSEARCHLINEEDIT_H
#define YLSEARCHLINEEDIT_H

#include <QLineEdit>

class QLabel;
class QPushButton;
class YLSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    YLSearchLineEdit(QWidget *parent = nullptr);

private:
    void init();

    const QString qss_search_label = "QLabel#search_label_{border-image:url(:/res/MainFrame/search_icon.png);}";
    const QString qss_delete_buton = "QPushButton#delete_button_        {border-image:url(:/res/MainFrame/main_search_delnormal.png);}\
                                      QPushButton#delete_button_:hover  {border-image:url(:/res/MainFrame/main_search_delhighlight.png);}\
                                      QPushButton#delete_button_:pressed{border-image:url(:/res/MainFrame/main_search_deldown.png);}\
                                        ";
    const QString qss_this_on_edit = "QLineEdit#YLSearchLineEdit_this{border:0px; font:20px bold 黑体;padding:0 40 0 30; background-color:rgba(255, 255, 255, 255);}";
    const QString qss_this_no_edit = "QLineEdit#YLSearchLineEdit_this{border:0px; font:20px bold 黑体;padding:0 40 0 30; background-color:rgba(255, 255, 255, 90);}";


protected:
    void resizeEvent(QResizeEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

private slots:
    void on_delete();

private:
    QLabel      *search_label_;
    QPushButton *delete_button_;
};

#endif // YLSEARCHLINEEDIT_H
