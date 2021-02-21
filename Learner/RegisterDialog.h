#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QCloseEvent>

class RegisterDialog : public QDialog
{
    Q_OBJECT
    QGridLayout* msgLayout;
    QGridLayout* btnLayout;
    QGridLayout* mainLayout;
    QLabel* userName;
    QLabel* passWord;
    QLabel* rePassWord;
    QLabel* school;
    QLabel* email;
    QLineEdit* userNameEdit;
    QLineEdit* passWordEdit;
    QLineEdit* rePassWordEdit;
    QLineEdit* schoolEdit;
    QLineEdit* emailEdit;
    QPushButton* registerBtn;
    QPushButton* resetBtn;
    void run();
public:
    explicit RegisterDialog(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *e);
signals:

public slots:
    void on_Register_registerBtn_clicked();

};

#endif // REGISTERDIALOG_H
