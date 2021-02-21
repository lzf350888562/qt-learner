#include "MyLable.h"

MyLable::MyLable(QWidget *parent) : QLabel(parent)
{
    setFixedSize(60,50);
    setPixmap(QPixmap(":/img/no.png").scaled(60,50));
}

void MyLable::step(QList<MyLable *> lists, int current)
{
    lists[current-1]->setPixmap(QPixmap(":/img/yes.png").scaled(60,50));
    lists[current]->setPixmap(QPixmap(":/img/empty.png").scaled(60,50));
}
