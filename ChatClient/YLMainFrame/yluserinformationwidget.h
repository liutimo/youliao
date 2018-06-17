#ifndef YLUSERINFORMATIONWIDGET_H
#define YLUSERINFORMATIONWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"
#include "protobuf/youliao.base.pb.h"

using namespace youliao::pdu;

namespace Ui {
class UserInfoWidget;
}

class YLHeadFrame;

class YLUserInformationWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLUserInformationWidget(QWidget *parent = nullptr);

    void setUserInfo();


protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    void setBigIcon();
    void setSmallIcon();
    void setNickName();
    void setSignature();
    void setLocation();
    void setAge();
    void setBirthday();
    void setPhone();
    void setEmail();
    void setHomeTown();
    void setSchool();


private:
    Ui::UserInfoWidget *ui;

    base::UserInfo m_user_info;
    YLHeadFrame   *m_head_frame;
};

#endif // YLUSERINFORMATIONWIDGET_H
