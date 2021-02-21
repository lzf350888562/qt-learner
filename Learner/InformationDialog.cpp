#include "InformationDialog.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

InformationDialog::InformationDialog(int id):id(id)
{
    setWindowTitle("Info");
    setWindowFlags(this->windowFlags()|Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);
    run();
    init();
}

void InformationDialog::on_Login_logoutBtn_clicked()
{
    //注销确认
    QMessageBox::StandardButton sb = QMessageBox::question(this,"Exit","Do you want to logout?");
    if(sb == QMessageBox::Yes){
        QSqlQuery query;
        query.prepare(QString("delete from stuinfo where userid=%1;").arg(id));
        if(query.exec()){
            //注销信号
            emit isLogouted();
            qDebug()<<"You have logged out!!";
            QMessageBox::information(this,"Information","Logout successful!!!");
            this->close();
        }
    }
}

void InformationDialog::on_Login_logoffBtn_clicked()
{
    //退出登录确认
    QMessageBox::StandardButton sb = QMessageBox::question(this,"Exit","Do you want to logoff?");
    if(sb == QMessageBox::Yes){
        //信号
        emit isLogouted();
        qDebug()<<"You have logged off!!";
        QMessageBox::information(this,"Information","Logoff successful!!!");
        this->close();
    }
}

void InformationDialog::run()
{
    userId = new QLabel("学号");
    userName = new QLabel("用户名:");
    school = new QLabel("学校");
    email = new QLabel("邮箱");
    userIdEdit = new QLineEdit();
    userNameEdit = new QLineEdit();
    schoolEdit = new QLineEdit();
    emailEdit = new QLineEdit();
    closeBtn = new QPushButton("确认");
    logoffBtn= new QPushButton("退出登录");
    logoutBtn = new QPushButton("注销");

    msgLayout = new QGridLayout();
    msgLayout->addWidget(userName,0,0);
    msgLayout->addWidget(userNameEdit,0,1);
    msgLayout->addWidget(userId,1,0);
    msgLayout->addWidget(userIdEdit,1,1);
    msgLayout->addWidget(school,2,0);
    msgLayout->addWidget(schoolEdit,2,1);
    msgLayout->addWidget(email,3,0);
    msgLayout->addWidget(emailEdit,3,1);

    btnLayout = new QGridLayout();
    btnLayout->addWidget(closeBtn,0,0);
    btnLayout->addWidget(logoffBtn,0,1);
    btnLayout->addWidget(logoutBtn,0,2);
    btnLayout->setSpacing(15);

    mainLayout = new QGridLayout(this);
    mainLayout->addLayout(msgLayout,0,0);
    mainLayout->addLayout(btnLayout,1,0);
    mainLayout->setMargin(15);
    mainLayout->setSpacing(10);

    userNameEdit->setReadOnly(true);
    userIdEdit->setReadOnly(true);
    schoolEdit->setReadOnly(true);
    emailEdit->setReadOnly(true);

    QPalette palette1 = userIdEdit->palette();
    palette1.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    userIdEdit->setPalette(palette1);
    userNameEdit->setPalette(palette1);
    schoolEdit->setPalette(palette1);
    emailEdit->setPalette(palette1);

    //确认按钮 返回上个页面
    connect(closeBtn,&QPushButton::clicked,this,[=](){
        this->close();
    });
    //退出登录按钮
    connect(logoffBtn,&QPushButton::clicked,this,&InformationDialog::on_Login_logoffBtn_clicked);
    //注销用户按钮
    connect(logoutBtn,&QPushButton::clicked,this,&InformationDialog::on_Login_logoutBtn_clicked);
}

void InformationDialog::init()
{
    QSqlQuery query1;
    query1.exec(QString("select username,school,email from stuinfo where userid=%1;").arg(id));
    if(query1.first()){
        userIdEdit->setText(QString::number(id));
        userNameEdit->setText(query1.value(0).toString());
        schoolEdit->setText(query1.value(1).toString());
        emailEdit->setText(query1.value(2).toString());
    }
}
