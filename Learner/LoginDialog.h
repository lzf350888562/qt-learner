#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "RegisterDialog.h"
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class LoginDialog : public QDialog
{
    Q_OBJECT
    QGridLayout* msgLayout;
    QGridLayout* btnLayout;
    QGridLayout* mainLayout;
    QLabel* userName;
    QLabel* passWord;
    QLineEdit* userNameEdit;
    QLineEdit* passWordEdit;
    QPushButton* loginBtn;
    QPushButton* registerBtn;
    RegisterDialog* reg;
    int FlagofLogin;
    void run();
public:
    explicit LoginDialog(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *e);
signals:
    void logined(int id);
public slots:
    void on_Login_loginBtn_clicked();
    void on_Login_registerBtn_clicked();

};
#endif // LOGINDIALOG_H
