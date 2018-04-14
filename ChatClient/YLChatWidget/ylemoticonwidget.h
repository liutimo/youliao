#ifndef YLEMOTICONWIDGET_H
#define YLEMOTICONWIDGET_H

#include <QWidget>
#include <QLabel>

class QTableWidget;
class QMovie;

class YLEmoticonWidget : public QWidget
{
    Q_OBJECT
    const QString m_qss_emoticon =  "QTableWidget#EmoticonTableWidget::item:hover    {background: rgba(200, 200, 200, 255);}"
                                    "QTableWidget#EmoticonTableWidget::item:selected {background: rgba(200, 200, 200, 255);}";
public:
    explicit YLEmoticonWidget(QWidget *parent = nullptr);
    virtual ~YLEmoticonWidget();

    static bool isShow;

private:
    void init();


signals:
    void selected(int index);
public slots:


private:
    QLabel       *m_title_label;
    QTableWidget *m_emoticon_tablewidget;
};

class YLEmoticonLabel : public QLabel
{
    Q_OBJECT
public:
    explicit YLEmoticonLabel(QWidget *parent = Q_NULLPTR);
    virtual ~YLEmoticonLabel();

    void setEmoticon(int index);

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
//    void select
private:
    QMovie *m_emoticon_movie;
    int i;
};

#endif // YLEMOTICONWIDGET_H
