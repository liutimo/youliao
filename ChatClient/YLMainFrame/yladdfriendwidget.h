#ifndef YLADDFRIENDWIDGET_H
#define YLADDFRIENDWIDGET_H

#include "YLBasicWidget/ylbasicwidget.h"

class QLineEdit;

class YLAddFriendWidget : public YLBasicWidget
{
    Q_OBJECT
public:
    explicit YLAddFriendWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    void init();

    QLineEdit *m_search_lineedit;
    QPushButton *m_search_button;
};

#endif // YLADDFRIENDWIDGET_H
