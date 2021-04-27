#ifndef ANSWERGAMEWINDOW_H
#define ANSWERGAMEWINDOW_H

#include "MyLable.h"
#include "Solution.h"
#include "DecorationLable.h"
#include <QMainWindow>
#include <QPropertyAnimation>

namespace Ui {
class AnswerGameWindow;
}

class AnswerGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnswerGameWindow(int i,QWidget *parent = nullptr);
    ~AnswerGameWindow();
protected:
    void closeEvent(QCloseEvent *e);
    void timerEvent(QTimerEvent *e);
    void paintEvent(QPaintEvent *e);
private:
    Ui::AnswerGameWindow *ui;
    int level;                  //关卡
    Solution* solution;         //答案界面
    QList<MyLable *> myLables;  //进度标签集合
    QLabel *location;           //当前进度
    QList<bool> results;        //测试结果对错集合
    QList<QLabel *> redPoint;   //测试完成对错标记
    QList<QString> listId;      //题目id 为数据库的primary key
    QList<QString> listName;    //题目名字
    QList<QString> listA;       //A选项
    QList<QString> listB;       //B选项
    QList<QString> listC;       //C选项
    QList<QString> listD;       //答案
    int timerId;                //计时器
    int score;                  //成绩
    int current;                //当前题目索引
    bool stop;                  //当前题目结束标记
    DecorationLable *decorate;  //动画装饰
    QLabel *fireworks;           //烟花
    QPropertyAnimation *animation;//动画
    void myLabelInit();         //初始化进度标签
    void randomSelect();        //随机从题库中选题并存入集合
    void step();                //一题结束后对进度标签更新
    void finished();            //测试结束的工作
signals:
    void game3_Return();        //关闭信号
private slots:
    void on_pushButton_clicked();   //A选项按钮
    void on_pushButton_2_clicked(); //B选项按钮
    void on_pushButton_3_clicked(); //C选项按钮
    void on_pushButton_4_clicked(); //查看答案按钮
};

#endif // ANSWERGAMEWINDOW_H
