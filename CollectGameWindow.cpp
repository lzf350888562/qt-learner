#include "CollectGameWindow.h"

#include<QDebug>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include<QMessageBox>

CollectGameWindow::CollectGameWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("收集C语言关键字");
    QPixmap titlePix(":/img/book.png");
    setWindowIcon(QIcon(titlePix));
    setFixedSize(650,650);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);
    picBack.load(":/img/game1_background1.png");         //背景图
    picPPL.load(":/img/game1_canmove.png");              //收集容器图
    picPPL=picPPL.scaled(200,120);
    pplRect=QRect(5,460,picPPL.width()/3*2,picPPL.height());//收集容器矩形
    picScore.load(":/img/game1_databackground.png");
    picTime.load(":/img/game1_databackground.png");
    oldX=0;
    timer0=startTimer(1000);
    timer1=startTimer(300);
    keyWordNumber=0;
    noKeyWordNumber=0;
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

    for(int i=0;i<=keyWordNumber&&noKeyWordNumber<=19;i++)
    {
        if(!word[i].type)
        {
            wordPic.load(QString(":/img/word%1.png").arg(i));
            painter.drawPixmap(word[i].rc,wordPic);
        }
    }
    for(int i=0;i<=noKeyWordNumber&&noKeyWordNumber<=19;i++)
    {
        if(!noWord[i].type)
        {
            wordPic.load(QString(":/img/noword%1.png").arg(i+1));
            painter.drawPixmap(noWord[i].rc,wordPic);
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
    if(keyWordNumber>=44||noKeyWordNumber>=18)
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
    for(int i=0;i<keyWordNumber&&keyWordNumber<=44;i++)
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
    for(int i=0;i<noKeyWordNumber&&noKeyWordNumber<=19;i++)
    {
        if(noWord[i].type!=-1&&pplRect.intersects(noWord[i].rc))
        {
            score=score-2;
            noWord[i].type=-1;
        }
        if(noWord[i].type!=-1&&440<noWord[i].rc.top())
        {
            qDebug()<<"no over";
            noWord[i].type=-1;
        }
    }
    for (int i=0;i<keyWordNumber&&keyWordNumber<=44;i++)
    {
        int y=0;
        if(word[i].type==0)
            y=word[i].rc.top()+10;
        word[i].rc.moveTop(y);
    }
    for (int i=0;i<noKeyWordNumber&&noKeyWordNumber<=19;i++)
    {
        int y=0;
        if(noWord[i].type==0)
            y=noWord[i].rc.top()+10;
        noWord[i].rc.moveTop(y);
    }
    if(interval>0)
    {
        interval--;
        update();
        return;
    }
    if(e->timerId()==timer1)
    {
        newX=rand()%(520);
        while(newX-oldX<95&&newX-oldX>-95){
            newX=rand()%(520);
        }
        if(rand()%(520)>=200){
            word[keyWordNumber].type=0;
            word[keyWordNumber].rc=QRect(newX,77,100,100);
            keyWordNumber++;
        }else{
            if(rand()%(520)>=330){
                word[keyWordNumber].type=0;
                word[keyWordNumber].rc=QRect(newX,77,100,100);
                keyWordNumber++;
            }else{
                noWord[noKeyWordNumber].type=0;
                noWord[noKeyWordNumber].rc=QRect(newX,77,100,100);
                noKeyWordNumber++;
            }
        }
        oldX=newX;
    }
    interval=rand()%3+3;
    update();
}

void CollectGameWindow::closeEvent(QCloseEvent *e)   //关闭执行的操作
{
        if(stopWatch!=0){
            killTimer(timer0);
            killTimer(timer1);
        }
        qDebug()<<"游戏中途退出了";
        emit game1_Return();

}
