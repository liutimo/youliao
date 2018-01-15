#ifndef YLLINEEDIT_H
#define YLLINEEDIT_H

/*
 * 继承至QLineEdit
 * 在其内部添加一个按钮。点击时发送信号，由用户处理该信号实现相关操作
 * 用途：
 *      - 登录界面的账号输入框
 *      - 主界面的好友搜索框
 *      - 群聊天中的群成员搜索
 *      ....
 */

#include <QLineEdit>

class QPushButton;

class YLLineEdit : public QLineEdit
{
    const QString qss_custom_button_ = "QPushButton#button_custom_        {border-image:url(%1);}\
                                        QPushButton#button_custom_:hover  {border-image:url(%2);}\
                                        QPushButton#button_custom_:pressed{border-image:url(%3);}\
                                        ";
    Q_OBJECT
public:
    YLLineEdit(QWidget *parent = nullptr);

    /**
     * 设置lineedit内部按钮的三态图片
     * @brief setButtonIcon
     * @param normal
     * @param hover
     * @param pressed
     */
    void setButtonIcon(const QString &normalPath, const QString &hoverPath, const QString &pressedPath);

    void setButtonSize(const QSize &size);

private:
    void init();

signals:
    void button_clicked();

protected:
    void resizeEvent(QResizeEvent *event);

private:
    QPushButton *button_custom_;
};

#endif // YLLINEEDIT_H
