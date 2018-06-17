#ifndef YLGROUPINFOWIDGET_H
#define YLGROUPINFOWIDGET_H
#include "YLBasicWidget/ylbasicwidget.h"
#include "YLEntityObject/ylgroup.h"
QT_BEGIN_NAMESPACE
class YLHeadFrame;
class QPushButton;
class QLabel;
class QToolButton;
class YLMemberListWidget;
QT_END_NAMESPACE

class YLGroupInfoWidget : public YLBasicWidget
{
    Q_OBJECT
    const QString qss_selected = "QToolButton{background:rgba(255, 255, 255, 0);border:0px;border-bottom:2px solid black;color:gray;color:black;font: 20px solid 黑体;}"
                                 "QToolButton:hover{background:rgba(255, 255, 255, 0);border:0px;border-bottom:2px solid black; color:black;font: 20px solid 黑体;}";

    const QString qss_no_selected = "QToolButton{background:rgba(255, 255, 255, 0);border:0px;color:black;font: 20px solid 黑体;}"
                                    "QToolButton:hover{background:rgba(255, 255, 255, 0);border:0px;color:black;font: 20px solid 黑体;}";

    const QString qss_add_photo    = "QPushButton        {border-image:url(:/res/MainFrame/addphoto_nomal.png);}\
                                      QPushButton:hover  {border-image:url(:/res/MainFrame/addphoto_hover.png);}\
                                      QPushButton:pressed{border-image:url(:/res/MainFrame/addphoto_down.png);}";

public:
    explicit YLGroupInfoWidget(QWidget *parent = nullptr);
    void setGroup(const YLGroup &);


private:
    void initLeft();    //width = 200
    void initRight1();   //width = 430
    void initRight2();   //width = 430
    void initTopNavigationBar();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void uploadPhoto();
    void navigationClicked();
    void modifyGroupCard();
    void updateGroupMemberList();

    void mainShow();
    void memberShow();
    void settingShow();
    void mainHide();
    void memberHide();
    void settingHide();

signals:

private:
    //left
    YLHeadFrame *m_head_frame;
    QLabel *m_label_group_name;
    QLabel *m_label_group_id;
    QPushButton *m_send_button;

    //导航栏按钮
    QToolButton *m_main;
    QToolButton *m_member;
    QToolButton *m_setting;

    //right1 首 页
    QPushButton *m_add_photo;
    YLHeadFrame *m_photo;
    QLabel *m_group_intro;
    QLabel *m_label_group_intro;
    QLabel *m_label_manager;
    QLabel *m_label_member_distr;
    QVector<YLHeadFrame*> members;

    //right 成员列表
    YLMemberListWidget *m_member_list;
    QLabel      *m_label_manager_count;
    QPushButton *m_modify_group_card;
    //data
    YLGroup m_group;

    int index;
};

#endif // YLGROUPINFOWIDGET_H
