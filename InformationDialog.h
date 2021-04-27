#ifndef INFOMATIONDIALOG_H
#define INFOMATIONDIALOG_H

#include <QDialog>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class InformationDialog :public QDialog
{
    Q_OBJECT
public:
    InformationDialog(int id);      //传递用户主键
protected:
    void on_Login_logoutBtn_clicked();
    void on_Login_logoffBtn_clicked();
    void on_Login_addBtn_clicked();
private:
    QGridLayout* msgLayout;
    QGridLayout* btnLayout;
    QGridLayout* mainLayout;
    int id;
    QLabel* userId;
    QLabel* userName;
    QLabel* school;
    QLabel* email;
    QLineEdit* userIdEdit;
    QLineEdit* userNameEdit;
    QLineEdit* schoolEdit;
    QLineEdit* emailEdit;
    QPushButton* closeBtn;
    QPushButton* logoffBtn;
    QPushButton* logoutBtn;
    QPushButton* addBtn;
    void run();                 //模块编程
    void init();                //信息初始化
signals:
    void isLogouted();
};


#endif // INFOMATIONDIALOG_H
