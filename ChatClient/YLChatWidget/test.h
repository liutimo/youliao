#ifndef TEST_H
#define TEST_H

#include <QObject>
class QWebEnginePage;
class QMenu;
class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);
    void setPage(QWebEnginePage* page);
signals:

private:
    void initPMenu();

public slots:
    void showContentPMenu();

private:
    QWebEnginePage *m_page;
    QMenu          *m_p_menu;
};

#endif // TEST_H
