#ifndef TEST_H
#define TEST_H

#include <QObject>
class QWebEnginePage;
class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);
    void setPage(QWebEnginePage* page);
signals:

public slots:
    void copy();
private:
    QWebEnginePage *m_page;

};

#endif // TEST_H
