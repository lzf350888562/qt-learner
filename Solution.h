#ifndef SOLUTION_H
#define SOLUTION_H

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>

namespace Ui {
class Solution;
}

class Solution : public QWidget
{
    Q_OBJECT

public:
    explicit Solution(QList<bool> &res,QList<QString> &names,QList<QString> &as,QList<QString> &bs,QList<QString> &cs,QList<QString> &ds,QWidget *parent = nullptr);
    ~Solution();
private:
    QList<bool> results;
    QList<QString> listName;
    QList<QString> listA;
    QList<QString> listB;
    QList<QString> listC;
    QList<QString> listD;
    Ui::Solution *ui;
    int current;                    //当前查阅的题目
    QButtonGroup *bg;               //按钮组,聚集事件处理
    QList<QPushButton *> bList;     //按钮集合
    void init();                    //初始化控件信息
    void link();                    //绑定事件更新相应信息
};

#endif // SOLUTION_H
