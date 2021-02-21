#include "AnswerGameWindow.h"
#include "ui_AnswerGameWindow.h"

#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>

AnswerGameWindow::AnswerGameWindow(int i, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnswerGameWindow),
    level(i)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/img/nopass.png"));
    setWindowTitle("Answer");
    setFixedSize(this->width(),this->height());
    //设置背景色
    QPalette bgPalette(this->palette());
    bgPalette.setColor(QPalette::Background,QColor(255, 226, 202));
    this->setAutoFillBackground(true);
    this->setPalette(bgPalette);
    //设置按钮背景色
    QPalette palette(QColor(0, 120, 215));
    ui->pushButton->setPalette(palette);
    ui->pushButton->setAutoFillBackground(true);
    ui->pushButton_2->setPalette(palette);
    ui->pushButton_2->setAutoFillBackground(true);
    ui->pushButton_3->setPalette(palette);
    ui->pushButton_3->setAutoFillBackground(true);
    //进度标签初始化
    myLabelInit();
    //查看答案按钮初始化并隐藏
    ui->pushButton_4->setText("查看答案");
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_4->hide();
    //初始化成员变量
    results<<false<<false<<false<<false<<false<<false<<false<<false<<false<<false;
    score=0;
    current=0;
    stop=false;
    //lcd计时
    ui->lcdNumber->display(10);
    //计时器开启
    timerId=startTimer(1000);
    //录入题目
    randomSelect();
    //第一题内容
    ui->textEdit->setText(listName.at(current));
    ui->pushButton->setText(listA.at(current));
    ui->pushButton_2->setText(listB.at(current));
    ui->pushButton_3->setText(listC.at(current));
}

AnswerGameWindow::~AnswerGameWindow()
{
    delete ui;
}

void AnswerGameWindow::closeEvent(QCloseEvent *e)
{
    emit game3_Return();
}

void AnswerGameWindow::timerEvent(QTimerEvent *e)
{
    //LCD事件显示更新
    ui->lcdNumber->display(ui->lcdNumber->value()-1);
    //如果计时到了0
    if(ui->lcdNumber->value() == 0.0){
        //如果当前的的题目为最后一题
        if(current==9){
            //执行完成后的工作
            finished();
            killTimer(timerId);
            QMessageBox::information(this,"Finished",QString("测试结束,您的得分为:%1").arg(score));
            //需要返回 否则if外语句执行将导致集合下标越界
            return;
        }
        if(results.at(current)){
            decorate->moveAnimation();
        }
        current++;
        //进度标签更新
        step();
        //重置当题结束标记
        stop=false;
        //LCD重新从0开始
        ui->lcdNumber->display(10);
        ui->textEdit->setText(listName.at(current));
        ui->pushButton->setText(listA.at(current));
        ui->pushButton_2->setText(listB.at(current));
        ui->pushButton_3->setText(listC.at(current));
        //重启所有按钮
        if(ui->pushButton->isFlat())
            ui->pushButton->setFlat(false);
        if(ui->pushButton_2->isFlat())
            ui->pushButton_2->setFlat(false);
        if(ui->pushButton_3->isFlat())
            ui->pushButton_3->setFlat(false);
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
    }
}

void AnswerGameWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QImage destination(":/img/destination.png");
    destination=destination.scaled(50,50);
    QMatrix matrix;
    matrix.rotate(270);
    destination=destination.transformed(matrix,Qt::FastTransformation);
    painter.drawPixmap(750,270,destination.width(),destination.height(),QPixmap::fromImage(destination));
}

void AnswerGameWindow::myLabelInit()
{
    //当前位置标签
    location=new QLabel(this);
    location->setPixmap(QPixmap(":/img/location1.png").scaled(50,50));
    location->setFixedSize(50,50);
    //题目标签
    myLables<<new MyLable(this)<<new MyLable(this)<<new MyLable(this)<<new MyLable(this)<<new MyLable(this)<<new MyLable(this)<<new MyLable(this)<<new MyLable(this)<<new MyLable(this)<<new MyLable(this);
    myLables[0]->setPixmap(QPixmap(":/img/empty.png").scaled(60,50));
    for(int i=0;i<10;i++)
        myLables[i]->move(100+60*i,30);
    location->move(105,30);
    //错题标记 默认隐藏
    for (int i=0;i<10;i++) {
        redPoint.append(new QLabel(this));
        redPoint[i]->setPixmap(QPixmap(":/img/redpoint.png").scaled(40,40));
        redPoint[i]->setFixedSize(40,40);
        redPoint[i]->move(110+i*60,80);
        redPoint[i]->hide();
    }
    //及格进度装饰
    decorate = new DecorationLable(2,6,this);
    decorate->move(600,520);
    fireworks = new QLabel(this);
    QPixmap fw(":/img/fireworks.png");
    fw=fw.scaled(150,200);
    fireworks->setFixedSize(150,200);
    fireworks->setPixmap(fw);
    fireworks->move(-fireworks->width(),300);
    fireworks->setAttribute(Qt::WA_TransparentForMouseEvents);
    fireworks->setWindowOpacity(0.5);
}

void AnswerGameWindow::randomSelect()
{
    QSqlQuery query;
    query.exec(QString("select * from mydb%1 order by rand() limit 10;").arg(level+1));
    while(query.next()){
        listName.append(query.value(1).toString());
        listA.append(query.value(2).toString());
        listB.append(query.value(3).toString());
        listC.append(query.value(4).toString());
        listD.append(query.value(5).toString());
    }
    //录入测试
    qDebug()<<listName<<endl;
    qDebug()<<listA<<endl;
    qDebug()<<listB<<endl;
    qDebug()<<listC<<endl;
    qDebug()<<listD<<endl;
}

void AnswerGameWindow::step()
{
    //当前位置标签更新
    location->move(105+current*60,30);
    //题目标签更新,已答的题和未答的题标签更新
    MyLable::step(myLables,current);
}

void AnswerGameWindow::finished()
{
    //删除当前位置标签
    delete location;
    //显示查看答案按钮
    ui->pushButton_4->show();
    ui->pushButton_4->setEnabled(true);
    myLables[current]->setPixmap(QPixmap(":/img/yes.png").scaled(60,50));
    qDebug()<<results;
    //显示对应错题的错误标志
    for (int i=0;i<10;i++) {
        if(!results[i]){
            redPoint[i]->show();
        }
    }
    //如果及格
    if(score>59)
    {
        qDebug() << "Win!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1";
        animation =  new QPropertyAnimation(fireworks,"geometry");
        animation->setDuration(1000);
        animation->setStartValue(QRect(fireworks->x(),fireworks->y(),fireworks->width(),fireworks->height()));
        animation->setEndValue(QRect(fireworks->x()+fireworks->width(),fireworks->y(),fireworks->width(),fireworks->height()));
        animation->setEasingCurve(QEasingCurve::OutBounce);
        animation->start();
        setWindowIcon(QIcon(":/img/pass.png"));
    }
}

void AnswerGameWindow::on_pushButton_clicked()
{   //如果还没有选答案
    if(!stop){
        //如果选择正确
        if(listD.at(current)=="A"){
            score+=10;
            results[current]=true;
        }
        stop=true;
        //禁用所有按钮
        ui->pushButton->setFlat(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}

void AnswerGameWindow::on_pushButton_2_clicked()
{   //如果还没有选答案
    if(!stop){
        //如果选择正确
        if(listD.at(current)=="B"){
            score+=10;
            results[current]=true;
        }
        //禁用按钮
        stop=true;
        ui->pushButton_2->setFlat(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}

void AnswerGameWindow::on_pushButton_3_clicked()
{   //如果还没有选答案
    if(!stop){
        //如果选择正确
        if(listD.at(current)=="C"){
            score+=10;
            results[current]=true;
        }
        //禁用按钮
        stop=true;
        ui->pushButton_3->setFlat(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}

void AnswerGameWindow::on_pushButton_4_clicked()
{
    solution = new Solution(results,listName,listA,listB,listC,listD);
    solution->show();
}
