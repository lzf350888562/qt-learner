#include "CollectStartWindow.h"
#include "MyPushButton.h"

CollectStartWindow::CollectStartWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("收集C语言关键字");
    QPixmap titlePix(":/img/book.png");
    setWindowIcon(QIcon(titlePix));
    setFixedSize(700,400);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);
    //背景图
    bg=new QLabel(this);
    QPixmap pix(":/img/game1_background.png");
    pix=pix.scaled(700,400);
    bg->setPixmap(pix);
    bg->setGeometry(0,0,700,400);
    //开始游戏按钮
    MyPushButton *btn=new MyPushButton(":/img/start.png",this);
    btn->move(500,140);
    //对按钮事件绑定槽
    connect(btn,&MyPushButton::clicked,this,[=](){
        btn->shake();
        QTimer::singleShot(1000,this,[=](){
            game1=new CollectGameWindow;
            this->hide();
            game1->show();
            connect(game1,&CollectGameWindow::game1_Return,this,[=](){
                this->show();
                delete game1;
            });
        });
    });
    //返回按钮
    returnBtn = new DoubleFaceButton(":/img/return1.png",":/img/return2.png",this);
    returnBtn->move(580,330);
    connect(returnBtn,&DoubleFaceButton::clicked,this,[=](){
        QTimer::singleShot(1000,this,[=](){
            this->hide();
            emit start1_Return();
        });
    });
}

void CollectStartWindow::closeEvent(QCloseEvent *e)
{
    emit start1_Return();
}
