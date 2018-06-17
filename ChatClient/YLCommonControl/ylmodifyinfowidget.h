#ifndef YLMODIFYINFOWIDGET_H
#define YLMODIFYINFOWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"
#include "protobuf/youliao.base.pb.h"

using namespace youliao::pdu;

namespace Ui {
class ModifyInfoationWidget;
}
class YLModifyInfoWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLModifyInfoWidget(QWidget *parent = nullptr);
    void setUserInfo(base::UserInfo &userInfo);

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_2_clicked();

    void on_saveBtn_clicked();

signals:
    void modifySuccess();

private:
    Ui::ModifyInfoationWidget *ui;
    base::UserInfo          m_user_info;
};

#endif // YLMODIFYINFOWIDGET_H
