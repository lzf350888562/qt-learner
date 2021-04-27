#include "RegisterDialog.h"

#include <QPushButton>
#include <QSqlQuery>
#include <QMessageBox>

void RegisterDialog::run()
{
    userName = new QLabel("用户名:");
    passWord = new QLabel("密码:");
    rePassWord = new QLabel("确认密码:");
    school = new QLabel("学校:");
    email = new QLabel("邮箱:");
    userNameEdit = new QLineEdit();
    passWordEdit = new QLineEdit();
    rePassWordEdit = new QLineEdit();
    schoolEdit = new QLineEdit();
    emailEdit = new QLineEdit();
    registerBtn = new QPushButton("注册");
    resetBtn = new QPushButton("重置");

    passWordEdit->setEchoMode(QLineEdit::Password);
    rePassWordEdit->setEchoMode(QLineEdit::Password);

    msgLayout = new QGridLayout();
    msgLayout->addWidget(userName,0,0);
    msgLayout->addWidget(userNameEdit,0,1);
    msgLayout->addWidget(passWord,1,0);
    msgLayout->addWidget(passWordEdit,1,1);
    msgLayout->addWidget(rePassWord,2,0);
    msgLayout->addWidget(rePassWordEdit,2,1);
    msgLayout->addWidget(school,3,0);
    msgLayout->addWidget(schoolEdit,3,1);
    msgLayout->addWidget(email,4,0);
    msgLayout->addWidget(emailEdit,4,1);

    btnLayout = new QGridLayout();
    btnLayout->addWidget(registerBtn,0,0);
    btnLayout->addWidget(resetBtn,0,1);

    mainLayout = new QGridLayout(this);
    mainLayout->addLayout(msgLayout,0,0);
    mainLayout->addLayout(btnLayout,1,0);

    connect(registerBtn,&QPushButton::clicked,this,&RegisterDialog::on_Register_registerBtn_clicked);
    connect(resetBtn,&QPushButton::clicked,this,[=](){
        userNameEdit->clear();
        passWordEdit->clear();
        rePassWordEdit->clear();
        schoolEdit->clear();
        emailEdit->clear();
    });
}

RegisterDialog::RegisterDialog(QWidget *parent) : QDialog (parent)
{
    setWindowTitle("注册");
    QPixmap pix(":/img/book.png");
    setWindowIcon(QIcon(pix));
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint&~Qt::WindowMinimizeButtonHint&~Qt::MSWindowsFixedSizeDialogHint);
    run();

}

void RegisterDialog::closeEvent(QCloseEvent *e)
{

    QMessageBox::StandardButton sb = QMessageBox::question(this,"确认","确定要离开吗？");
    if(sb == QMessageBox::Yes){
        e->accept();
    }else if(sb==QMessageBox::No){
        e->ignore();
    }
}

void RegisterDialog::on_Register_registerBtn_clicked()
{
    QSqlQuery query;
    if(passWordEdit->text() == rePassWordEdit->text()){
        QString userNameText = userNameEdit->text();
        QString passWordText = passWordEdit->text();
        QString schoolText = schoolEdit->text();
        QString emailText = emailEdit->text();

        QString insert = QString("insert into stuinfo values(null,'%1','%2','%3','%4');").arg(userNameText).arg(passWordText).arg(schoolText).arg(emailText);
        QString select = QString("select * from stuinfo where username='%1'").arg(userNameText);
        if(query.exec(select)&&query.first()){
            QMessageBox::warning(this,"错误","注册失败，用户名重复!!!");
        }else if (query.exec(insert)) {
            QMessageBox::information(this,"信息","注册成功!");
        }else {
            QMessageBox::warning(this,"错误","注册失败!!!");
        }
    }else {
        QMessageBox::warning(this,"错误","两次密码不相同!!!");
    }
}
