#include "AnswerStartWindow.h"

#include"AnswerGameWindow.h"
#include "MyPushButton.h"
#include <QTimer>
#include <QDebug>
#include <QPainter>

AnswerStartWindow::AnswerStartWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("章节测试");
    QPixmap titlePix(":/img/book.png");
    setWindowIcon(QIcon(titlePix));
    setFixedSize(700,400);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);
    //设置背景颜色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background,QColor(255, 226, 202));
    this->setAutoFillBackground(true);
    this->setPalette(palette);
    //返回按钮
    returnBtn = new DoubleFaceButton(":/img/return1.png",":/img/return2.png",this);
    returnBtn->move(580,330);
    connect(returnBtn,&DoubleFaceButton::clicked,this,[=](){
        QTimer::singleShot(1000,this,[=](){
            this->hide();
            emit start3_Return();
        });
    });
    //关卡选择按钮
    for(int i=0;i<8;i++)
    {
        //关卡按钮
        QPushButton *roundBtn=new QPushButton(this);
        roundBtn->setFixedSize(120,120);
        roundBtn->setStyleSheet("QPushButton{border:0px;}");
        roundBtn->setIcon(QIcon(QPixmap(":/img/round1.png").scaled(120,120)));
        roundBtn->setIconSize(QSize(120,120));
        roundBtn->move(30+i%4*120,100+i/4*120);
        //关卡标签
        QLabel *label=new QLabel(QString::number(i+1),this);
        label->setFont(QFont("Autumn",30));
        label->move(30+i%4*120,100+i/4*120);
        label->setFixedSize(roundBtn->width(),roundBtn->height());
        label->setAlignment(Qt::AlignCenter);
        //给按钮点击事件绑定槽,实现关卡跳转
        connect(roundBtn,&QPushButton::clicked,this,[=](){    //标签叠加在按钮上面，需要给标签设置穿透属性
            qDebug()<<QString("You choosed level %1").arg(i+1);
            AnswerGameWindow* playi=new AnswerGameWindow(i);
            this->hide();
            playi->show();
            //监听游戏页面的返回按钮
            connect(playi,&AnswerGameWindow::game3_Return,this,[=](){
                this->show();
                delete playi;
            });
        });
        //设置穿透鼠标事件
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}

void AnswerStartWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QFont font("Autumn",30,QFont::DemiBold              );
    painter.setFont(font);
    painter.setPen(QPen(QColor(255, 165, 33)));
    painter.drawText(QPoint(40,70),"请选择需要测试关卡");
}

void AnswerStartWindow::closeEvent(QCloseEvent *e)
{
    emit start3_Return();
}
