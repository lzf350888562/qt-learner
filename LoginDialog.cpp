#include "LoginDialog.h"

#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>

void LoginDialog::run()
{
    //初始时未登录
    FlagofLogin=0;
    //登录界面布局
    userName = new QLabel("用户名:");
    passWord = new QLabel("密码:");
    userNameEdit = new QLineEdit();
    passWordEdit = new QLineEdit();
    loginBtn = new QPushButton("登录");
    registerBtn = new QPushButton("注册");

    passWordEdit->setEchoMode(QLineEdit::Password);

    msgLayout = new QGridLayout();
    msgLayout->addWidget(userName,0,0);
    msgLayout->addWidget(userNameEdit,0,1);
    msgLayout->addWidget(passWord,1,0);
    msgLayout->addWidget(passWordEdit,1,1);

    btnLayout = new QGridLayout();
    btnLayout->addWidget(loginBtn,0,0);
    btnLayout->addWidget(registerBtn,0,1);
    btnLayout->setSpacing(15);

    mainLayout = new QGridLayout(this);
    mainLayout->addLayout(msgLayout,0,0);
    mainLayout->addLayout(btnLayout,1,0);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);
    //事件绑定
    connect(loginBtn,&QPushButton::clicked,this,&LoginDialog::on_Login_loginBtn_clicked);
    connect(registerBtn,&QPushButton::clicked,this,&LoginDialog::on_Login_registerBtn_clicked);
}

LoginDialog::LoginDialog(QWidget *parent) : QDialog (parent)
{
    setWindowTitle("登录");
    QPixmap pix(":/img/book.png");
    setWindowIcon(QIcon(pix));
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint&~Qt::MSWindowsFixedSizeDialogHint);
    run();
}

void LoginDialog::closeEvent(QCloseEvent *e)
{
    //退出确认
    if(FlagofLogin==0){
        QMessageBox::StandardButton sb = QMessageBox::question(this,"确认","确定要离开吗?");
        if(sb == QMessageBox::Yes){
            e->accept();
        }else if(sb==QMessageBox::No){
            e->ignore();
        }
    }
}
//登录按钮
void LoginDialog::on_Login_loginBtn_clicked()
{
    QString userNameText = userNameEdit->text();
    QString passWordText = passWordEdit->text();
    QString select=QString("select * from stuinfo where username='%1' and password='%2' ;").arg(userNameText).arg(passWordText);
    qDebug()<<select;
    QSqlQuery query;
    query.exec(select);
    if(query.first()){
        qDebug()<<query.value(0).toString()+"   "<<query.value(1).toString()+"    "  <<query.value(2).toString();
        emit logined(query.value(0).toInt());
        FlagofLogin=1;
        QMessageBox::information(this,"信息",QString("登录成功!\n您已经打卡了%1次了，请继续坚持打卡！").arg(query.value(5).toInt()));
        this->close();
    }else {
        QMessageBox::warning(this,"警告","登录失败，请重试.");
    }
}
//注册按钮
void LoginDialog::on_Login_registerBtn_clicked()
{
    reg = new RegisterDialog();
    reg->exec();
}
