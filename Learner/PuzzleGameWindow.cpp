#include "PuzzleGameWindow.h"

#include<QTimer>
#include<QStatusBar>
#include<QDebug>
#include<QtGlobal>
#include<QTime>
#include<QMessageBox>


PuzzleGameWindow::PuzzleGameWindow(QWidget *parent) : QMainWindow(parent)
{
    setMouseTracking(true);
    setWindowTitle("Puzzle");
    setFixedSize(760,500);
    setWindowFlags(Qt::WindowCloseButtonHint);
    isFinished=false;                           //默认未完成
    imageInit();                                //图块初始化
    upsetImage();                               //打乱图片
    timerInit();                                //启动计时器
}
//初始化图片块，设置块的初始位置和初始二维坐标与标记
void PuzzleGameWindow::imageInit()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            flagOfImages[i][j]=1;
            if(i==2&&j==2)
            {
               break;
            }
            blocks[i][j]=new BlockLabel(QImage(QString(":/img/flowchart%1.jpg").arg(i*3+j+1)),this);

            blocks[i][j]->move(30+j*200,20+i*150);
            blocks[i][j]->positionX=i;
            blocks[i][j]->positionY=j;
            blocks[i][j]->raise();  //让图片优先重叠
        }
    }
    blocks[2][2]=new BlockLabel(QImage(":/img/game2_white.png"),this);
    blocks[2][2]->move(430,320);
    blocks[2][2]->positionX=2;
    blocks[2][2]->positionY=2;
    flagOfImages[2][2]=0;
}
//打乱图块 并交换相关属性
void PuzzleGameWindow::upsetImage()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    blocks[0][0]->move(230,320);
    blocks[2][1]->move(30,20);
    blocks[0][0]->setPosition(2,1);
    blocks[2][1]->setPosition(0,0);
    swapBlocks(0,0,2,1);
    blocks[0][2]->move(430,170);
    blocks[1][2]->move(430,20);
    blocks[0][2]->setPosition(1,2);
    blocks[1][2]->setPosition(0,2);
    swapBlocks(0,2,1,2);
    if(qrand()%2)
    {
        blocks[0][1]->move(30,320);
        blocks[2][0]->move(230,20);
        blocks[0][1]->setPosition(2,0);
        blocks[2][0]->setPosition(0,1);
        swapBlocks(0,1,2,0);
        blocks[1][0]->move(230,170);
        blocks[1][1]->move(30,170);
        blocks[1][0]->setPosition(1,1);
        blocks[1][1]->setPosition(1,0);
        swapBlocks(1,0,1,1);
    }
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if(i!=2&&j!=2){
                if(qrand()%2){
                    blocks[i][j]->rotation();
                    blocks[i][j]->haveRotated();
                }
            }
        }
    }
}
//计时器开启动态更新时间和操作步数
void PuzzleGameWindow::timerInit()
{
    stopWatch=0;                                //时间
    stepTotal=0;                                    //操作步数
    stopWatchLCD=new QLCDNumber(this);
    stopWatchLCD->move(640,200);
    stopWatchLCD->display(QString::number(stopWatch));
    stopWatchLCD->setSegmentStyle(QLCDNumber::Flat);
    stepTotalLCD=new QLCDNumber(this);
    stepTotalLCD->move(640,250);
    stepTotalLCD->display(QString::number(stepTotal));
    stepTotalLCD->setSegmentStyle(QLCDNumber::Flat);
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,[=](){
        stopWatch++;
        stopWatchLCD->display(QString::number(stopWatch));   //更新lcd显示
        stepTotalLCD->display(QString::number(stepTotal));
        if(check())
        {
            isFinished=true;
            timer->stop();
            finished();
        }
    });
    timer->start(1000);
}
//利用中间变量交换两个块指针
void PuzzleGameWindow::swapBlocks(int x1, int y1, int x2, int y2)
{
    BlockLabel *tmpBlockPoint=nullptr;
    tmpBlockPoint=blocks[x1][y1];
    blocks[x1][y1]=blocks[x2][y2];
    blocks[x2][y2]=tmpBlockPoint;
}
//遍历块数组检查每个块是否归为
bool PuzzleGameWindow::check()
{
    bool isFinished=true;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            if(!blocks[i][j]->isOk())
            {
                isFinished=false;
                break;
            }
        }
    return isFinished;
}
//显示完成提示 可添加动画与声效
void PuzzleGameWindow::finished()
{
    QTimer::singleShot(500,this,[=](){
        QMessageBox::information(this,"Congratulation","恭喜，您已完成拼图！\n您的用时为"+QString::number(stopWatch)+"秒.\n您的操作次数为"+QString::number(stepTotal)+"次.");
    });
}


//鼠标在块上按下，如果旁边有空块则移动
void PuzzleGameWindow::mousePressEvent(QMouseEvent *e)
{
    //状态栏显示坐标 用作测试
    statusBar()->showMessage(QString::number(e->x())+" "+QString::number(e->y()));
    //如果已经完成禁用鼠标效果 交给父类处理
    if(isFinished)
        return QMainWindow::mousePressEvent(e);
    if(e->button()==Qt::LeftButton&&BlockLabel::isChanging==0)
    {
             if(e->pos().x()>30&&e->pos().x()<230&&e->pos().y()>20&&e->pos().y()<170)
        {   //0,0移动
            if(flagOfImages[0][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[0][0]->moveAnimation(BlockLabel::right);
                blocks[0][1]->moveAnimation(BlockLabel::left);
                blocks[0][0]->setPosition(0,1);
                blocks[0][1]->setPosition(0,0);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[0][0]=0;
                flagOfImages[0][1]=1;
                swapBlocks(0,0,0,1);
                stepTotal++;
            }
            else if(flagOfImages[1][0]==0)
            {
                BlockLabel::isChanging=1;
                blocks[0][0]->moveAnimation(BlockLabel::down);
                blocks[1][0]->moveAnimation(BlockLabel::up);
                blocks[0][0]->setPosition(1,0);
                blocks[1][0]->setPosition(0,0);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[0][0]=0;
                flagOfImages[1][0]=1;
                swapBlocks(0,0,1,0);
                stepTotal++;
            }
        }
        else if(e->pos().x()>430&&e->pos().x()<630&&e->pos().y()>20&&e->pos().y()<170)
        {   //0,2移动
            if(flagOfImages[0][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[0][2]->moveAnimation(BlockLabel::left);
                blocks[0][1]->moveAnimation(BlockLabel::right);
                blocks[0][2]->setPosition(0,1);
                blocks[0][1]->setPosition(0,2);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[0][2]=0;
                flagOfImages[0][1]=1;
                swapBlocks(0,2,0,1);
                stepTotal++;
            }
            else if(flagOfImages[1][2]==0)
            {
                BlockLabel::isChanging=1;
                blocks[0][2]->moveAnimation(BlockLabel::down);
                blocks[1][2]->moveAnimation(BlockLabel::up);
                blocks[0][2]->setPosition(1,2);
                blocks[1][2]->setPosition(0,2);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[0][2]=0;
                flagOfImages[1][2]=1;
                swapBlocks(0,2,1,2);
                stepTotal++;
            }
        }
        else if(e->pos().x()>30&&e->pos().x()<230&&e->pos().y()>320&&e->pos().y()<470)
        {   //2,0移动
            if(flagOfImages[1][0]==0)
            {
                BlockLabel::isChanging=1;
                blocks[2][0]->moveAnimation(BlockLabel::up);
                blocks[1][0]->moveAnimation(BlockLabel::down);
                blocks[2][0]->setPosition(1,0);
                blocks[1][0]->setPosition(2,0);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[2][0]=0;
                flagOfImages[1][0]=1;
                swapBlocks(2,0,1,0);
                stepTotal++;
            }
            else if(flagOfImages[2][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[2][0]->moveAnimation(BlockLabel::right);
                blocks[2][1]->moveAnimation(BlockLabel::left);
                blocks[2][0]->setPosition(2,1);
                blocks[2][1]->setPosition(2,0);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[2][0]=0;
                flagOfImages[2][1]=1;
                swapBlocks(2,0,2,1);
                stepTotal++;
            }
        }
        else if(e->pos().x()>430&&e->pos().x()<630&&e->pos().y()>320&&e->pos().y()<470)
        {   //2,2移动
            if(flagOfImages[1][2]==0)
            {
                BlockLabel::isChanging=1;
                blocks[2][2]->moveAnimation(BlockLabel::up);
                blocks[1][2]->moveAnimation(BlockLabel::down);
                blocks[2][2]->setPosition(1,2);
                blocks[1][2]->setPosition(2,2);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[2][2]=0;
                flagOfImages[1][2]=1;
                swapBlocks(2,2,1,2);
                stepTotal++;
            }
            else if(flagOfImages[2][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[2][2]->moveAnimation(BlockLabel::left);
                blocks[2][1]->moveAnimation(BlockLabel::right);
                blocks[2][2]->setPosition(2,1);
                blocks[2][1]->setPosition(2,2);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[2][2]=0;
                flagOfImages[2][1]=1;
                swapBlocks(2,2,2,1);
                stepTotal++;
            }
        }
        else if(e->pos().x()>230&&e->pos().x()<430&&e->pos().y()>20&&e->pos().y()<170)
        {   //0,1移动
            if(flagOfImages[0][0]==0)
            {
                BlockLabel::isChanging=1;
                blocks[0][1]->moveAnimation(BlockLabel::left);
                blocks[0][0]->moveAnimation(BlockLabel::right);
                blocks[0][1]->setPosition(0,0);
                blocks[0][0]->setPosition(0,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[0][1]=0;
                flagOfImages[0][0]=1;
                swapBlocks(0,1,0,0);
                stepTotal++;
            }
            else if(flagOfImages[0][2]==0)
            {
                BlockLabel::isChanging=1;
                blocks[0][1]->moveAnimation(BlockLabel::right);
                blocks[0][2]->moveAnimation(BlockLabel::left);
                blocks[0][1]->setPosition(0,2);
                blocks[0][2]->setPosition(0,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[0][1]=0;
                flagOfImages[0][2]=1;
                swapBlocks(0,1,0,2);
                stepTotal++;
            }
            else if(flagOfImages[1][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[0][1]->moveAnimation(BlockLabel::down);
                blocks[1][1]->moveAnimation(BlockLabel::up);
                blocks[0][1]->setPosition(1,1);
                blocks[1][1]->setPosition(0,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[0][1]=0;
                flagOfImages[1][1]=1;
                swapBlocks(0,1,1,1);
                stepTotal++;
            }
        }
        else if(e->pos().x()>30&&e->pos().x()<230&&e->pos().y()>170&&e->pos().y()<320)
        {   //1,0移动
            if(flagOfImages[0][0]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][0]->moveAnimation(BlockLabel::up);
                blocks[0][0]->moveAnimation(BlockLabel::down);
                blocks[1][0]->setPosition(0,0);
                blocks[0][0]->setPosition(1,0);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][0]=0;
                flagOfImages[0][0]=1;
                swapBlocks(1,0,0,0);
                stepTotal++;
            }
            else if(flagOfImages[2][0]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][0]->moveAnimation(BlockLabel::down);
                blocks[2][0]->moveAnimation(BlockLabel::up);
                blocks[1][0]->setPosition(2,0);
                blocks[2][0]->setPosition(1,0);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][0]=0;
                flagOfImages[2][0]=1;
                swapBlocks(1,0,2,0);
                stepTotal++;
            }
            else if(flagOfImages[1][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][0]->moveAnimation(BlockLabel::right);
                blocks[1][1]->moveAnimation(BlockLabel::left);
                blocks[1][0]->setPosition(1,1);
                blocks[1][1]->setPosition(1,0);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][0]=0;
                flagOfImages[1][1]=1;
                swapBlocks(1,0,1,1);
                stepTotal++;
            }
        }
        else if(e->pos().x()>430&&e->pos().x()<630&&e->pos().y()>170&&e->pos().y()<320)
        {   //1,2移动
            if(flagOfImages[0][2]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][2]->moveAnimation(BlockLabel::up);
                blocks[0][2]->moveAnimation(BlockLabel::down);
                blocks[1][2]->setPosition(0,2);
                blocks[0][2]->setPosition(1,2);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][2]=0;
                flagOfImages[0][2]=1;
                swapBlocks(1,2,0,2);
                stepTotal++;
            }
            else if(flagOfImages[2][2]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][2]->moveAnimation(BlockLabel::down);
                blocks[2][2]->moveAnimation(BlockLabel::up);
                blocks[1][2]->setPosition(2,2);
                blocks[2][2]->setPosition(1,2);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][2]=0;
                flagOfImages[2][2]=1;
                swapBlocks(1,2,2,2);
                stepTotal++;
            }
            else if(flagOfImages[1][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][2]->moveAnimation(BlockLabel::left);
                blocks[1][1]->moveAnimation(BlockLabel::right);
                blocks[1][2]->setPosition(1,1);
                blocks[1][1]->setPosition(1,2);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][2]=0;
                flagOfImages[1][1]=1;
                swapBlocks(1,2,1,1);
                stepTotal++;
            }
        }
        else if(e->pos().x()>230&&e->pos().x()<430&&e->pos().y()>320&&e->pos().y()<470)
        {   //2,1移动
            if(flagOfImages[2][0]==0)
            {
                BlockLabel::isChanging=1;
                blocks[2][1]->moveAnimation(BlockLabel::left);
                blocks[2][0]->moveAnimation(BlockLabel::right);
                blocks[2][1]->setPosition(2,0);
                blocks[2][0]->setPosition(2,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[2][1]=0;
                flagOfImages[2][0]=1;
                swapBlocks(2,1,2,0);
                stepTotal++;
            }
            else if(flagOfImages[2][2]==0)
            {
                BlockLabel::isChanging=1;
                blocks[2][1]->moveAnimation(BlockLabel::right);
                blocks[2][2]->moveAnimation(BlockLabel::left);
                blocks[2][1]->setPosition(2,2);
                blocks[2][2]->setPosition(2,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[2][1]=0;
                flagOfImages[2][2]=1;
                swapBlocks(2,1,2,2);
                stepTotal++;
            }
            else if(flagOfImages[1][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[2][1]->moveAnimation(BlockLabel::up);
                blocks[1][1]->moveAnimation(BlockLabel::down);
                blocks[2][1]->setPosition(1,1);
                blocks[1][1]->setPosition(2,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[2][1]=0;
                flagOfImages[1][1]=1;
                swapBlocks(2,1,1,1);
                stepTotal++;
            }
        }
        else if(e->pos().x()>230&&e->pos().x()<430&&e->pos().y()>170&&e->pos().y()<320)
        {   //1,1移动
            if(flagOfImages[0][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][1]->moveAnimation(BlockLabel::up);
                blocks[0][1]->moveAnimation(BlockLabel::down);
                blocks[1][1]->setPosition(0,1);
                blocks[0][1]->setPosition(1,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][1]=0;
                flagOfImages[0][1]=1;
                swapBlocks(1,1,0,1);
                stepTotal++;
            }
            else if(flagOfImages[1][0]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][1]->moveAnimation(BlockLabel::left);
                blocks[1][0]->moveAnimation(BlockLabel::right);
                blocks[1][1]->setPosition(1,0);
                blocks[1][0]->setPosition(1,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][1]=0;
                flagOfImages[1][0]=1;
                swapBlocks(1,1,1,0);
                stepTotal++;
            }
            else if(flagOfImages[1][2]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][1]->moveAnimation(BlockLabel::right);
                blocks[1][2]->moveAnimation(BlockLabel::left);
                blocks[1][1]->setPosition(1,2);
                blocks[1][2]->setPosition(1,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][1]=0;
                flagOfImages[1][2]=1;
                swapBlocks(1,1,1,2);
                stepTotal++;
            }
            else if(flagOfImages[2][1]==0)
            {
                BlockLabel::isChanging=1;
                blocks[1][1]->moveAnimation(BlockLabel::down);
                blocks[2][1]->moveAnimation(BlockLabel::up);
                blocks[1][1]->setPosition(2,1);
                blocks[2][1]->setPosition(1,1);
                QTimer::singleShot(800,this,[=](){
                    BlockLabel::isChanging=0;
                });
                flagOfImages[1][1]=0;
                flagOfImages[2][1]=1;
                swapBlocks(1,1,2,1);
                stepTotal++;
            }
        }
    }
    else if (e->button()==Qt::RightButton) {
        if(e->pos().x()>30&&e->pos().x()<230&&e->pos().y()>20&&e->pos().y()<170)
        {   //0,0旋转
            blocks[0][0]->rotation();
            blocks[0][0]->haveRotated();
            stepTotal++;
        }
        else if(e->pos().x()>430&&e->pos().x()<630&&e->pos().y()>20&&e->pos().y()<170)
        {   //0,2旋转
            blocks[0][2]->rotation();
            blocks[0][2]->haveRotated();
            stepTotal++;
        }
        else if(e->pos().x()>30&&e->pos().x()<230&&e->pos().y()>320&&e->pos().y()<470)
        {   //2,0旋转
            blocks[2][0]->rotation();
            blocks[2][0]->haveRotated();
            stepTotal++;
        }
        else if(e->pos().x()>430&&e->pos().x()<630&&e->pos().y()>320&&e->pos().y()<470)
        {   //2,2旋转
            blocks[2][2]->rotation();
            blocks[2][2]->haveRotated();
            stepTotal++;
        }
        else if(e->pos().x()>230&&e->pos().x()<430&&e->pos().y()>20&&e->pos().y()<170)
        {   //0,1旋转
            blocks[0][1]->rotation();
            blocks[0][1]->haveRotated();
            stepTotal++;
        }
        else if(e->pos().x()>30&&e->pos().x()<230&&e->pos().y()>170&&e->pos().y()<320)
        {   //1,0旋转
            blocks[1][0]->rotation();
            blocks[1][0]->haveRotated();
            stepTotal++;
        }
        else if(e->pos().x()>430&&e->pos().x()<630&&e->pos().y()>170&&e->pos().y()<320)
        {   //1,2旋转
            blocks[1][2]->rotation();
            blocks[1][2]->haveRotated();
            stepTotal++;
        }
        else if(e->pos().x()>230&&e->pos().x()<430&&e->pos().y()>320&&e->pos().y()<470)
        {   //2,1旋转
            blocks[2][1]->rotation();
            blocks[2][1]->haveRotated();
            stepTotal++;
        }
        else if(e->pos().x()>230&&e->pos().x()<430&&e->pos().y()>170&&e->pos().y()<320)
        {   //1,1旋转
            blocks[1][1]->rotation();
            blocks[1][1]->haveRotated();
            stepTotal++;
         }
    }
}

void PuzzleGameWindow::closeEvent(QCloseEvent *e)
{
    QMessageBox::StandardButton sb = QMessageBox::question(this,"Exit","Do you want to exit?");
    if(sb == QMessageBox::Yes){
        emit game2_Return();
        timer->stop();
        qDebug()<<"游戏中途退出了";
        e->accept();
    }else if(sb==QMessageBox::No){
        e->ignore();
    }


}

