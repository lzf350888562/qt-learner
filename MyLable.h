#ifndef MYLABLE_H
#define MYLABLE_H

#include <QLabel>

class MyLable : public QLabel
{
    Q_OBJECT
public:
    explicit MyLable(QWidget *parent = nullptr);
    //改变lists集合中current和current-1索引处的标签
    static void step(QList<MyLable *> lists,int current);
signals:

public slots:
};

#endif // MYLABLE_H
