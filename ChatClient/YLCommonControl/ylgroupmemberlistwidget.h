#ifndef YLGROUPMEMBERLISTWIDGET_H
#define YLGROUPMEMBERLISTWIDGET_H

#include <QWidget>
#include <QPushButton>
QT_BEGIN_NAMESPACE
class QListWidget;
class QLineEdit;
class QVBoxLayout;
QT_END_NAMESPACE
class Button : public QPushButton
{
    Q_OBJECT
    //按下去的stylesheet
    const QString qss_btn_down = "QPushButton        {border-image:url(:/res/YLChatWidget/SearchIcon_down.png);}\
                                  QPushButton:hover  {border-image:url(:/res/YLChatWidget/SearchIcon_down.png);}\
                                  QPushButton:pressed{border-image:url(:/res/YLChatWidget/SearchIcon_down.png);}\
                                  ";

    const QString qss_btn = "QPushButton        {border-image:url(:/res/YLChatWidget/SearchIcon_normal.png);}\
                             QPushButton:hover  {border-image:url(:/res/YLChatWidget/SearchIcon_hover.png);}\
                             QPushButton:pressed{border-image:url(:/res/YLChatWidget/SearchIcon_down.png);}\
                            ";
public:
    Button(QWidget *parent = nullptr) : QPushButton(parent), m_clicked(false)
    {
        setStyleSheet("text-align:left;border:0px;");
        m_search_button = new QPushButton(this);
        m_search_button->setFixedSize(16, 16);
        m_search_button->setStyleSheet(qss_btn);

        connect(m_search_button, &QPushButton::clicked, this, [this](){
            if (m_clicked)
            {
                m_search_button->setStyleSheet(qss_btn);
                emit isShow(false);
            }
            else
            {
                m_search_button->setStyleSheet(qss_btn_down);
                emit isShow(true);
            }
            m_clicked = !m_clicked;
        });
    }
signals:
    void isShow(bool);
protected:
    void resizeEvent(QResizeEvent *event)
    {
        m_search_button->move(width() - 26, height() / 2 - 8);
    }

private:
    QPushButton     *m_search_button;
    bool             m_clicked;
};

class YLGroupMemberListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit YLGroupMemberListWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    Button      *m_button;
    QLineEdit   *m_line_edit;
    QListWidget *m_list_widget;
    QVBoxLayout *m_v_ayout;
};

#endif // YLGROUPMEMBERLISTWIDGET_H
