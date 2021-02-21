#ifndef DECORATIONLABLE_H
#define DECORATIONLABLE_H

#include <QLabel>
#include <QPropertyAnimation>

class DecorationLable : public QLabel
{
    Q_OBJECT
public:
    explicit DecorationLable(int flag,int destination,QWidget *parent = nullptr);
    void moveAnimation();
private:
    int flag;
    int destination;
    QImage *img;
    int step;
    QPropertyAnimation *animation;
    void moveRight();
    void moveUp();
signals:

public slots:
};

#endif // DECORATIONLABLE_H
