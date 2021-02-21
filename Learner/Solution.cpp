#include "Solution.h"
#include "ui_Solution.h"

#include<QDebug>
#include<QtMath>
#include<cmath>


Solution::Solution(QList<bool> &res,QList<QString> &names, QList<QString> &as, QList<QString> &bs, QList<QString> &cs, QList<QString> &ds, QWidget *parent) :
    QWidget(parent),
    results(res),
    listName(names),
    listA(as),
    listB(bs),
    listC(cs),
    listD(ds),
    ui(new Ui::Solution)
{
    ui->setupUi(this);
    this->setWindowTitle("Solution");
    this->setFixedSize(this->width(),this->height());
    current=0;
    //错误标志
    ui->label_2->setPixmap(QPixmap(":/img/redpoint.png").scaled(40,40));
    ui->label_2->setFixedSize(40,40);
    ui->label_2->hide();
    //初始化控件
    init();
    //事件绑定处理
    link();
}

Solution::~Solution()
{
    delete ui;
}
void Solution::init()
{
    //默认显示第一题信息
    ui->textEdit->setText(listName.at(current));
    if(listD.at(current).compare("A")){
        ui->textEdit_2->setText(listA.at(current));
    }else if(listD.at(current).compare("B")){
        ui->textEdit_2->setText(listB.at(current));
    }else if(listD.at(current).compare("C")){
        ui->textEdit_2->setText(listC.at(current));
    }
    //禁用第一题按钮
    ui->pushButton_1->setEnabled(false);
    //如果第一题错误则显示错误标志
    if(!results.at(current)){
        ui->label_2->show();
    }
}

void Solution::link()
{
    //创建与初始化按钮组
    bg = new QButtonGroup(this);
    bList<<ui->pushButton_1<<ui->pushButton_2<<ui->pushButton_3<<ui->pushButton_4<<ui->pushButton_5<<ui->pushButton_6<<ui->pushButton_7<<ui->pushButton_8<<ui->pushButton_9<<ui->pushButton_10;
    for (int i=0;i<10;i++) {
        bg->addButton(bList.at(i));
    }
    //按钮组信号有参数,将信号传给函数指针
    void (QButtonGroup::*func)(int)=&QButtonGroup::buttonClicked;
    connect(bg,func,this,[=](int id){
        //如果错误标注未隐藏则隐藏
        if(!ui->label_2->isHidden()){
            ui->label_2->hide();
        }
        //测试按钮组信号传过来的id
        qDebug()<<id;
        //按钮组信号传过来的id值为-2~-11,所以需要改变
        int i=abs(id)-2;
        //取消前一个题的按钮的禁用
        bList.at(current)->setEnabled(true);
        //更新当前题目
        current=i;
        //更新控件内文本
        ui->textEdit->setText(listName.at(current));
        if(listD.at(current).compare("A")){
            ui->textEdit_2->setText(listA.at(current));
        }else if(listD.at(current).compare("B")){
            ui->textEdit_2->setText(listB.at(current));
        }else if(listD.at(current).compare("C")){
            ui->textEdit_2->setText(listC.at(current));
        }
        bList.at(current)->setEnabled(false);
        //如果这题答错了则红点标注
        if(!results.at(current)){
            ui->label_2->show();
        }
    });
}
