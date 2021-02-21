#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFile>
#include <QDebug>
#include <QTreeWidgetItem>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QToolBar>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>



void MainWindow::run()
{
    //工具栏
    QToolBar *toolBar=new QToolBar(this);
    toolBar->setFixedHeight(30);
    QList<QAction *> actions;
    QActionGroup *actionGroup=new QActionGroup(this);
    QPixmap actGameIcon1(":/img/game.png");
    QPixmap actGameIcon2(":/img/game1.png");
    QPixmap actGameIcon3(":/img/game2.png");
    QPixmap actLoginIcon(":/img/login.png");
    actGameIcon1=actGameIcon1.scaled(15,15);
    actGameIcon2=actGameIcon2.scaled(15,15);
    actGameIcon3=actGameIcon3.scaled(15,15);
    QAction *actGame1=new QAction("游戏1");
    actGame1->setIcon(QIcon(actGameIcon1));
    actionGroup->addAction(actGame1);
    QAction *actGame2=new QAction("游戏2");
    actGame2->setIcon(QIcon(actGameIcon2));
    actionGroup->addAction(actGame2);
    QAction *actGame3=new QAction("游戏3");
    actGame3->setIcon(QIcon(actGameIcon3));
    actionGroup->addAction(actGame3);
    QAction *actLogin=new QAction("登录");
    actLogin->setIcon(QIcon(actLoginIcon));
    actionGroup->addAction(actLogin);
    actions<<actGame1<<actGame2<<actGame3<<actLogin;
    toolBar->addActions(actions);
    this->addToolBar(toolBar);
    connect(actionGroup,&QActionGroup::triggered,this,[=](QAction *a){
        this->hide();
        if(a==actGame1)
        {
            qDebug()<<"You will enter GAME 1";
            start1=new CollectStartWindow;
            start1->show();
            connect(start1,&CollectStartWindow::start1_Return,this,[=](){
                this->show();
            });
        }
        else if(a==actGame2)
        {
            qDebug()<<"You will enter GAME 2";
            start2=new PuzzleStartWindow;
            start2->show();
            connect(start2,&PuzzleStartWindow::start2_Return,this,[=](){
                this->show();
            });
        }
        else if(a==actGame3)
        {
            qDebug()<<"You will enter GAME 3";
            start3=new AnswerStartWindow;
            start3->show();
            connect(start3,&AnswerStartWindow::start3_Return,this,[=](){
                this->show();
            });

        }
        else if(a==actLogin)
        {
            if(isLogined==false){
                this->show();
                qDebug()<<"You will enter LOGIN";
                login= new LoginDialog;
                //需要先建立连接在执行对话框 否则连接不生效!!!
                connect(login,&LoginDialog::logined,this,[=](int id){
                    isLogined=true;
                    currentId=id;
                    qDebug()<<id<<": You have logined!!";
                });
                //模态对话框
                login->exec();
            }else {
                //lambda表达式传值测试
                qDebug()<<isLogined<<currentId;
                info = new InformationDialog(currentId);
                connect(info,&InformationDialog::isLogouted,this,[=](){
                    isLogined=false;
                });
                this->show();
                //非模态对话框
                info->show();
            }
        }
    });
    tabOneInit();
    tabTwoInit();
    tabThreeInit();
    mysqlConnect();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(757,550);
    setWindowTitle("Study");
    QPixmap pix(":/img/nologin.png");
    setWindowIcon(QIcon(pix));
    this->setMouseTracking(true);
    isLogined=false;
    run();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tabOneInit()   //tab1
{
    //取消焦点 让其只读
    ui->tab1_TextEdit->setFocusPolicy(Qt::NoFocus);

    //章节名和路径初始化
    chapterName<<"第1章 程序设计和C语言"<<"第2章 算法――程序的灵魂"<<"第3章 顺序程序设计"<<"第4章 选择结构程序设计"<<"第5章 循环结构程序设计"<<"第6章 数组"<<"第7章 函数"<<"第8章 指针"<<"第9章 结构体与共用体"<<"第10章 文件";
    for(int i=1;i<=10;i++)
        chapterPath<<QString(":/chapter/chapter%1.txt").arg(i);

    //默认显示的章节内容
    QFile *file=new QFile(chapterPath[0]);
    if(!file->open(QIODevice::ReadOnly))
        qDebug()<<"Cannot find file chapter1.txt";
    QByteArray array=file->readAll();
    ui->tab1_TextEdit->setText(array);
    file->close();

    //目录实现
    QList<QTreeWidgetItem *> rootList;
    QTreeWidgetItem *rootItem1=new QTreeWidgetItem(0);
    rootItem1->setText(0,tr("入门"));
    int i=0;
    for(;i<10;i++)
    {
        QTreeWidgetItem *secChild=new QTreeWidgetItem(rootItem1,QStringList(chapterName[i]));
        rootItem1->addChild(secChild);
    }
    rootList.append(rootItem1);
    ui->tab1_TreeWidget->insertTopLevelItems(0,rootList);

    //字体按钮
    connect(ui->tab1_Btn1,&QPushButton::clicked,ui->tab1,[=](){
        bool ok=true;
        QFont font=QFontDialog::getFont(&ok);
        if(ok)
            ui->tab1_TextEdit->setFont(font);
    });
    //颜色按钮
    connect(ui->tab1_Btn2,&QPushButton::clicked,ui->tab1,[=](){
        QColor color=QColorDialog::getColor(Qt::black);
        if(color.isValid())
        {
            QPalette p=palette();
            p.setColor(QPalette::Text,color);
            ui->tab1_TextEdit->setPalette(p);
        }
    });
    //背景按钮
    connect(ui->tab1_Btn3,&QPushButton::clicked,ui->tab1,[=](){
        QColor color=QColorDialog::getColor(Qt::black);
        if(color.isValid())
        {
            QPalette p=palette();
            p.setColor(QPalette::Base,color);
            ui->tab1_TextEdit->setPalette(p);
        }
    });
}

void MainWindow::tabTwoInit()
{   //字体按钮
    connect(ui->tab2_Btn3,&QPushButton::clicked,ui->tab1,[=](){
        bool ok=true;
        QFont font=QFontDialog::getFont(&ok);
        if(ok)
            ui->tab2_TextEdit->setFont(font);
    });
    //颜色按钮
    connect(ui->tab2_Btn4,&QPushButton::clicked,ui->tab1,[=](){
        QColor color=QColorDialog::getColor(Qt::black);
        if(color.isValid())
        {
            QPalette p=palette();
            p.setColor(QPalette::Text,color);
            ui->tab2_TextEdit->setPalette(p);
        }
    });
}

void MainWindow::tabThreeInit()
{
    isErasing=0;
    pix=QPixmap(711,391);
    pix.fill(Qt::white);
    pixTmp=QPixmap(711,391);
    pixTmp.fill(Qt::white);

    QButtonGroup *buttonGroup=new QButtonGroup(ui->tab3);
    //功能按钮
    ui->tab3_Btn1->setIcon(QIcon(":/img/tab1_pen.png"));
    ui->tab3_Btn2->setIcon(QIcon(":/img/tab1_line.png"));
    ui->tab3_Btn3->setIcon(QIcon(":/img/tab1_round.png"));
    ui->tab3_Btn4->setIcon(QIcon(":/img/tab1_rect.png"));
    ui->tab3_Btn5->setIcon(QIcon(":/img/tab1_save.png"));
    ui->tab3_Btn6->setIcon(QIcon(":/img/tab1_erase.png"));
    buttonGroup->addButton(ui->tab3_Btn1);
    buttonGroup->addButton(ui->tab3_Btn2);
    buttonGroup->addButton(ui->tab3_Btn3);
    buttonGroup->addButton(ui->tab3_Btn4);
    void (QButtonGroup::*clickedN)(int)=&QButtonGroup::buttonClicked;
    connect(buttonGroup,clickedN,this,&MainWindow::paintCommand);
    ui->drawingBoard->installEventFilter(this);
    //保存按钮
    connect(ui->tab3_Btn5,&QToolButton::clicked,this,[=](){
        QFileDialog saveDialog;
        //设置对话框打开的模式
        saveDialog.setAcceptMode(QFileDialog::AcceptSave);
        //设置对话框的标题
        saveDialog.setWindowTitle("0.0");
        //设置对话框的打开路径(只是路径，加上文件名失效)
        saveDialog.setDirectory("E:\\Projects\\Qt Projects\\MyProject\\build-StudyDemo1-Desktop_Qt_5_9_8_MinGW_32bit-Debug\\pictures");
        //设置对话框默认显示文件名
        saveDialog.selectFile("picture1.png");
        //设置文件过滤器
        saveDialog.setNameFilter("*.png");
        //设置默认选中文件保存类型
        saveDialog.selectNameFilter("*.png");
        if(saveDialog.exec()==QFileDialog::AcceptSave)
        {   QString pixPath=saveDialog.selectedFiles().first();
            qDebug()<<pixPath;
            pix.save(pixPath);
        }
    });
    //擦除按钮
    connect(ui->tab3_Btn6,&QToolButton::clicked,this,[=](){
        isErasing=1;
        update();
    });
}

void MainWindow::mysqlConnect()
{
   mysqldb=QSqlDatabase::addDatabase("QMYSQL");
   mysqldb.setHostName("localhost");
   mysqldb.setUserName("root");
   mysqldb.setPassword("350562");
   mysqldb.setPort(3306);
   mysqldb.setDatabaseName("qtstuinfo");
   if(mysqldb.open()){
       qDebug()<<"mysql连接成功";
   }
   else {
       qDebug()<<"mysql连接失败,无法登录";
   }
}

void MainWindow::paintCommand(int a)
{
    qDebug()<<a<<endl;
    if(a==-2){
        toolSelected=0;
        qDebug()<<toolSelected<<endl;
    }else if (a==-3) {
        toolSelected=1;
        qDebug()<<toolSelected<<endl;
    }else if(a==-4){
        toolSelected=2;
        qDebug()<<toolSelected<<endl;
    }else if(a==-5){
        toolSelected=3;
        qDebug()<<toolSelected<<endl;
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if(obj == ui->drawingBoard && e->type() == QEvent::Paint&&isErasing==1)
    {
        pixTmp.fill();
        pix.fill();
        QPainter painter(ui->drawingBoard);
        painter.drawPixmap(0,0,pix);
        isErasing=0;
    }
    if(obj == ui->drawingBoard && e->type() == QEvent::Paint)
    {
        QPainter painter(ui->drawingBoard);
        if(toolSelected==0)                         //随手画
        {
            QPainter painter2(&pix);                //在pix上画
            if(isDrawing>1)                         //鼠标在移动或者松开
            {
                painter2.drawLine(lastPt,endPt);    //连接最近两点
            }
            lastPt=endPt;                            //将目前坐标作为前一个坐标，为下次画线接收新坐标做准备
            pixTmp=pix;                             //pixtmp和pix保持一致
        }
        else                                        //不是随手画
        {
            if(isDrawing>=2)
            {
                pix=pixTmp;
                QRect obj(lastPt,endPt);
                QPainter painter2(&pix);
                if(toolSelected==1)
                {
                    painter2.drawLine(lastPt,endPt);
                }else if(toolSelected==2)
                    {
                        painter2.drawEllipse(obj);
                    }else if(toolSelected==3)
                         {
                        painter2.drawRect(obj);
                        }
            }
            if(isDrawing==3)    //鼠标已经释放  最终成像画之前初始化isDrawing，并保存当前成像
            {
                isDrawing=0;
                pixTmp=pix;
            }
        }
        painter.drawPixmap(0,0,pix);
    }

   return QWidget::eventFilter(obj,e);     //将事件传递给父类 //将事件传递给父类
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        lastPt=e->pos();
        lastPt.setY(lastPt.y()-110);  //向下移动
        endPt.setX(endPt.x()-25);
        isDrawing=1;                //左键按下
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    statusBar()->showMessage(QString::number(e->x())+" "+QString::number(e->y()));
    if(isDrawing==0)
        return;
    if(e->buttons()==Qt::LeftButton)   // 获取按钮组 而不是按钮
    {
        endPt=e->pos();             //按下鼠标并移动时获取第二个点
        endPt.setY(endPt.y()-110);
        endPt.setX(endPt.x()-25);
        isDrawing=2;            //按下并拖动
        update();        //进行绘制
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        endPt=e->pos();
        endPt.setY(endPt.y()-110);
        endPt.setX(endPt.x()-25);
        isDrawing=3;
        update();
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    mysqldb.close();
}

void MainWindow::on_tab1_TreeWidget_doubleClicked(const QModelIndex &index)
{
    qDebug()<<QString("You clicked chapter%1").arg(index.row()+1);
    QFile *file=new QFile(chapterPath[index.row()]);
    if(!file->open(QIODevice::ReadOnly))
        qDebug()<<QString("Cannot find file chapter%1.txt").arg(index.row()+1);
    QByteArray array=file->readAll();
    ui->tab1_TextEdit->setText(array);
    file->close();
}

void MainWindow::on_tab2_Btn1_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(),
            tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            }
            QByteArray array=file.readAll();
            ui->tab2_TextEdit->setText(array);
            file.close();
        }
}

void MainWindow::on_tab2_Btn2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QString(),
            tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                // error message
            }
            else {
                QByteArray array=ui->tab2_TextEdit->toPlainText().toUtf8();
                file.write(array);
                file.close();
            }
        }
}


void MainWindow::on_drawingBoard_customContextMenuRequested(const QPoint &pos)
{
    tabThreeMenu=new QMenu("工具菜单",ui->tab3);
    QAction *action1=new QAction("随手画",ui->tab3);
    QAction *action2=new QAction("直线",ui->tab3);
    QAction *action3=new QAction("圆形",ui->tab3);
    QAction *action4=new QAction("矩形",ui->tab3);
    QAction *action5=new QAction("清除",ui->tab3);
    QList<QAction*> tabThreeActions;
    tabThreeActions<<action1<<action2<<action3<<action4<<action5;
    tabThreeMenu->addActions(tabThreeActions);
    connect(action1,&QAction::triggered,ui->tab3,[=](){
        paintCommand(-2);
    });
    connect(action2,&QAction::triggered,ui->tab3,[=](){
        paintCommand(-3);
    });
    connect(action3,&QAction::triggered,ui->tab3,[=](){
        paintCommand(-4);
    });
    connect(action4,&QAction::triggered,ui->tab3,[=](){
        paintCommand(-5);
    });
    connect(action5,&QAction::triggered,ui->tab3,[=](){
        isErasing=1;
        update();
    });
    tabThreeMenu->exec(QCursor::pos());

}
