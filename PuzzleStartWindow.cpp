#include "PuzzleStartWindow.h"

#include "MyPushButton.h"
#include <QTimer>

PuzzleStartWindow::PuzzleStartWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("流程拼图");
    QPixmap titlePix(":/img/book.png");
    setWindowIcon(QIcon(titlePix));
    setFixedSize(700,400);
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint& ~Qt::WindowMinimizeButtonHint);
    //设置背景
    bg=new QLabel(this);
    QPixmap pix(":/img/game2_background.png");
    pix=pix.scaled(700,400);
    bg->setPixmap(pix);
    bg->setGeometry(0,0,700,400);
    //开始按钮
    MyPushButton *btn=new MyPushButton(":/img/start.png",this);
    btn->move(500,160);
    connect(btn,&MyPushButton::clicked,this,[=](){
        btn->shake();
        QTimer::singleShot(1000,this,[=](){
            game2=new PuzzleGameWindow;
            this->hide();
            game2->show();
            connect(game2,&PuzzleGameWindow::game2_Return,this,[=](){
                this->show();
                delete game2;
            });
        });
    });
    //返回按钮
    returnBtn = new DoubleFaceButton(":/img/return1.png",":/img/return2.png",this);
    returnBtn->move(580,330);
    connect(returnBtn,&DoubleFaceButton::clicked,this,[=](){
        QTimer::singleShot(1000,this,[=](){
            this->hide();
            emit start2_Return();
        });
    });
}

void PuzzleStartWindow::closeEvent(QCloseEvent *e)
{
    emit start2_Return();
}
