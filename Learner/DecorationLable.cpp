#include "DecorationLable.h"

DecorationLable::DecorationLable(int flag,int destination,QWidget *parent) :QLabel(parent),flag(flag),destination(destination)
{
    step=0;
    img=new QImage(":/img/bicycle.png");
    *img=img->scaled(90,75);
    setFixedSize(90,75);
    setPixmap(QPixmap::fromImage(img->scaled(90,75)));
}

void DecorationLable::moveAnimation()
{
    if(step==destination)
        return;
    if(step==flag){
        QMatrix matrix;
        matrix.rotate(270);
        *img=img->transformed(matrix,Qt::FastTransformation);
        setFixedSize(75,90);
        setPixmap(QPixmap::fromImage(*img));
        move(this->pos().rx()+10,this->pos().ry());
    }
    if(step<flag){
        moveRight();
        step++;
    }else {
        moveUp();
        step++;
    }
}

void DecorationLable::moveRight()
{
    animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation->setDuration(400);
    //创建起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation->setEndValue(QRect(this->x()+50,this->y(),this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    //animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation->start();
}

void DecorationLable::moveUp()
{
    animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation->setDuration(400);
    //创建起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation->setEndValue(QRect(this->x(),this->y()-50,this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    //animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation->start();
}
