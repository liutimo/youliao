#ifndef YLACCOUNTLISTVIEW_H
#define YLACCOUNTLISTVIEW_H

#include <QListWidget>
//----------------------------


//----------------------------

class YLHeadFrame;
class QLabel;
class QPushButton;
//----------------------------
class YLAccountListView : public QListWidget
{
    Q_OBJECT
    const QString qss_this = "QListWidget::item:hover {background: #228fdb;}";
public:
    YLAccountListView(QWidget *parent = nullptr);

    /**
     * @brief setData
     * @param data vector中的每一个QStringList 都由三个字符串组成，依次是头像地址、昵称和账号。
     */
    void setData(const QVector<QStringList> &data);

signals:
    void selected(const QString &account);

protected:
    void focusOutEvent(QFocusEvent *event);
private:

};


class YLAccountListViewItem : public QWidget
{
    Q_OBJECT
    const QString qss_delete_button = "QPushButton#button_delete_        {border-image:url(:/res/LoginPanel/btn_delete_normal.png);}\
                                       QPushButton#button_delete_:hover  {border-image:url(:/res/LoginPanel/btn_delete_hover.png);}\
                                       QPushButton#button_delete_:pressed{border-image:url(:/res/LoginPanel/btn_delete_down.png);}\
                                      ";

    const QString qss_account_label = "QLabel#label_account_{color:white;}";
public:
    YLAccountListViewItem(QWidget *parent = nullptr);

    void setHeadPicture(const QString &path);
    void setNickName(const QString &nickname);
    void setAccount(const QString &account);

private:
    void init();

protected:
    void resizeEvent(QResizeEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void deleteItem(const QString &);
    void selected(const QString &account);

private:
    QLabel      *label_nick_name_;
    QLabel      *label_account_;
    YLHeadFrame *head_frame_;
    QPushButton *button_delete_;

};

#endif // YLACCOUNTLISTVIEW_H
