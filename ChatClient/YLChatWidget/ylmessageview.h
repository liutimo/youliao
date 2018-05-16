#ifndef YLMESSAGEVIEW_H
#define YLMESSAGEVIEW_H

#include <QWebEngineView>

class YLMessageView : public QWebEngineView
{

public:
    explicit YLMessageView(QWidget *parent = Q_NULLPTR);

    virtual ~YLMessageView();

    void addLeft(const QString &, const QString &);
    void addRight(const QString &, const QString&);
    void addCancelSend(const QString &, const QString &);
    void addCancelRecv(const QString &, const QString &);

public slots:
    void copy();

protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QWebChannel *channel;
};

#endif // YLMESSAGEVIEW_H
