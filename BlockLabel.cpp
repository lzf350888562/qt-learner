#include "BlockLabel.h"

int BlockLabel::isChanging=0;

BlockLabel::BlockLabel(QImage image,QWidget *parent) : QLabel(parent),myImage(image)
{
    setFixedSize(200,150);
    myImage=myImage.scaled(200,150);
    setPixmap(QPixmap::fromImage(myImage));
    positive=1;
}

void BlockLabel::rotation()
{
    QMatrix matrix;
    matrix.rotate(180);
    myImage=myImage.transformed(matrix,Qt::FastTransformation);
    setPixmap(QPixmap::fromImage(myImage));

}

void BlockLabel::moveAnimation(BlockLabel::direction d)
{
    if(d==up)
    {
        animation = new QPropertyAnimation(this,"geometry");
        //设置时间间隔，单位毫秒
        animation->setDuration(400);
        //创建起始位置
        animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //创建结束位置
        animation->setEndValue(QRect(this->x(),this->y()-150,this->width(),this->height()));
        //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
        animation->setEasingCurve(QEasingCurve::OutBounce);
        //开始执行动画
        animation->start();
    }
    else if(d==down)
    {
        animation = new QPropertyAnimation(this,"geometry");
        //设置时间间隔，单位毫秒
        animation->setDuration(400);
        //创建起始位置
        animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //创建结束位置
        animation->setEndValue(QRect(this->x(),this->y()+150,this->width(),this->height()));
        //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
        animation->setEasingCurve(QEasingCurve::OutBounce);
        //开始执行动画
        animation->start();
    }
    else if(d==left)
    {
        animation = new QPropertyAnimation(this,"geometry");
        //设置时间间隔，单位毫秒
        animation->setDuration(400);
        //创建起始位置
        animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //创建结束位置
        animation->setEndValue(QRect(this->x()-200,this->y(),this->width(),this->height()));
        //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
        animation->setEasingCurve(QEasingCurve::OutBounce);
        //开始执行动画
        animation->start();
    }
    else if(d==right)
    {
        animation = new QPropertyAnimation(this,"geometry");
        //设置时间间隔，单位毫秒
        animation->setDuration(400);
        //创建起始位置
        animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
        //创建结束位置
        animation->setEndValue(QRect(this->x()+200,this->y(),this->width(),this->height()));
        //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
        animation->setEasingCurve(QEasingCurve::OutBounce);
        //开始执行动画
        animation->start();
    }
}

bool BlockLabel::isOk()
{
    if(currentX==positionX&&currentY==positionY&&positive==1)
        return true;
    else
        return false;
}

void BlockLabel::setPosition(int x, int y)
{
    this->currentX=x;
    this->currentY=y;
}

void BlockLabel::haveRotated()
{
    positive=positive?0:1;
}

