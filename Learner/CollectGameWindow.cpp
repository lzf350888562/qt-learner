#include "CollectGameWindow.h"

#include<QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include<QMessageBox>

CollectGameWindow::CollectGameWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Collect");
    setFixedSize(650,650);
    picBack.load(":/img/game1_background1.png");         //背景图
    picPPL.load(":/img/game1_canmove.png");              //收集容器图
    picPPL=picPPL.scaled(200,120);
    pplRect=QRect(5,460,picPPL.width()/3*2,picPPL.height());//收集容器矩形
    picScore.load(":/img/game1_databackground.png");
    picTime.load(":/img/game1_databackground.png");

    timer0=startTimer(1000);
    timer1=startTimer(300);
    keyWordNumber=0;
    interval=0;
    score=0;
    stopWatch=60;                               //游戏计时(秒)
    //setFocusPolicy(Qt::StrongFocus);
}

void CollectGameWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,650,650,picBack);
    painter.drawPixmap(200,560,120,80,picScore);
    painter.drawPixmap(345,560,120,80,picTime);
    painter.drawPixmap(pplRect,picPPL);

    for(int i=0;i<=keyWordNumber;i++)
    {
        if(!word[i].type)
        {
            wordPic.load(QString(":/img/word%1.png").arg(i));
            painter.drawPixmap(word[i].rc,wordPic);
        }
    }
    QFont font("微软雅黑",15,QFont::Normal,false);
    painter.setFont(font);
    QRect rect1(190,565,150,80);
    QRect rect2(330,565,150,80);
    painter.drawText(rect1,Qt::AlignCenter,QString::number(score));
    painter.drawText(rect2,Qt::AlignCenter,QString::number(stopWatch)+"秒");

}

void CollectGameWindow::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        case Qt::Key_Left:
            if(pplRect.left()>10)
            {
                int x=pplRect.left()-20;
                pplRect.moveLeft(x);
            }
            update();
            break;
        case Qt::Key_Right:
            if(pplRect.right()<this->width()-25)
            {
                int x=pplRect.left()+20;
                pplRect.moveLeft(x);
            }
            update();
            break;
    }
    QWidget::keyPressEvent(e);
}

void CollectGameWindow::timerEvent(QTimerEvent *e)
{
    if(keyWordNumber>=44)
        return;
    if(e->timerId()==timer0)
    {
        stopWatch--;
       //return;
    }
    if(stopWatch==0)
    {
        killTimer(timer0);
        killTimer(timer1);
        QString str;
        if(score<15)
            str="你的完成情况较差";
        else if (score<25) {
            str="你的完成情况较好";
        }else {
            str="你的完成情况很好";
        }
                    QTimer::singleShot(2000,this,[=](){
                QMessageBox::information(this,"结束",str);
            });
    }
    for(int i=0;i<keyWordNumber;i++)
    {
        if(word[i].type!=-1&&pplRect.intersects(word[i].rc))
        {
            score=score+1;
            word[i].type=-1;
        }
        if(word[i].type!=-1&&440<word[i].rc.top())
        {
            qDebug()<<"over";
            word[i].type=-1;
        }
    }
    for (int i=0;i<keyWordNumber;i++)
    {
        int y=0;
        if(word[i].type==0)
            y=word[i].rc.top()+10;
        word[i].rc.moveTop(y);
    }
    if(interval>0)
    {
        interval--;
        update();
        return;
    }
    if(e->timerId()==timer1)
    {
        int x=rand()%(520);
        word[keyWordNumber].type=0;
        word[keyWordNumber].rc=QRect(x,77,100,100);
        keyWordNumber++;
    }
    interval=rand()%3+3;
    update();
}

void CollectGameWindow::closeEvent(QCloseEvent *e)   //关闭执行的操作
{
    QMessageBox::StandardButton sb = QMessageBox::question(this,"Exit","Do you want to exit?");
    if(sb == QMessageBox::Yes){
        emit game1_Return();
        killTimer(timer0);
        killTimer(timer1);
        qDebug()<<"游戏中途退出了";
        e->accept();
    }else if(sb==QMessageBox::No){
        e->ignore();
    }

}
