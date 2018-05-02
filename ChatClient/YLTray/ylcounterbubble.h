#ifndef YLCOUNTERBUBBLE_H
#define YLCOUNTERBUBBLE_H

#include <QLabel>

class YLCounterBubble : public QLabel
{
    Q_OBJECT
public:
    explicit YLCounterBubble(QWidget *parent = nullptr);
    void setNumber(const int num = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int number = 0;
};

#endif // YLCOUNTERBUBBLE_H
