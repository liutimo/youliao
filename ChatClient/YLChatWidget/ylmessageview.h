#ifndef YLMESSAGEVIEW_H
#define YLMESSAGEVIEW_H

#include <QWebEngineView>

class YLMessageView : public QWebEngineView
{

public:
    explicit YLMessageView(QWidget *parent = Q_NULLPTR);

public slots:
    void copy();
};

#endif // YLMESSAGEVIEW_H
