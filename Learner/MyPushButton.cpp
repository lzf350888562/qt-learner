#include "MyPushButton.h"

#include <QMessageBox>
#include <QPropertyAnimation>

MyPushButton::MyPushButton(QString imgPath, QWidget *parent) : QPushButton(parent)
{
    QPixmap pixmap;
    if(!pixmap.load(imgPath))
        QMessageBox().warning(this,"Error","START Button Picture path missing");
    setFixedSize(100,100);
    setStyleSheet("QPushButton{border:0px;}");  //如果不加这个语句 按钮为带背景的矩形图片
    setIcon(QIcon(pixmap));
    setIconSize(QSize(100,100));
}

void MyPushButton::shake()
{
    //创建动画对象
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation1->setDuration(400);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();

    QPropertyAnimation * animation2 =  new QPropertyAnimation(this,"geometry");
    animation2->setDuration(400);
    animation2->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation2->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation2->setEasingCurve(QEasingCurve::OutBounce);
    animation2->start();
}
