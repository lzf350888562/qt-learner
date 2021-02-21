#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CollectStartWindow.h"
#include "PuzzleStartWindow.h"
#include "AnswerStartWindow.h"
#include "LoginDialog.h"
#include "InformationDialog.h"
#include <QMainWindow>
#include <QtSql/QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //双击目录
    void on_tab1_TreeWidget_doubleClicked(const QModelIndex &index);
    //文本打开按钮
    void on_tab2_Btn1_clicked();
    //文本保存按钮
    void on_tab2_Btn2_clicked();
    //画板右击菜单的功能实现
    void on_drawingBoard_customContextMenuRequested(const QPoint &pos);

protected:
    //绘画指令
    void paintCommand(int);
    //通过事件过滤器绘图 否则绘画会被主界面拦截
    bool eventFilter(QObject *,QEvent *);
    void mousePressEvent(QMouseEvent *e);   //鼠标按下
    void mouseMoveEvent(QMouseEvent *e);    //鼠标移动
    void mouseReleaseEvent(QMouseEvent *e); //鼠标释放
    void closeEvent(QCloseEvent *e);
private:
    Ui::MainWindow *ui;
    QStringList chapterPath;    //章节文本路径
    QStringList chapterName;    //章节名
    QPixmap pix,pixTmp;         //两个位图类的交替实现动态绘图
    QPoint lastPt,endPt;    //前一个鼠标点和当前鼠标点
    int toolSelected;       //选择的绘图工具
    int isDrawing;          //鼠标状态 1：按下 2：按下并移动 3：松开 0：其他
    int isErasing;          //画板是否擦除
    QMenu *tabThreeMenu;    //右击菜单
    QSqlDatabase mysqldb;
    void run();             //模块化
    void tabOneInit();      //页面1功能
    void tabTwoInit();      //页面2功能
    void tabThreeInit();    //页面3功能
    void mysqlConnect();    //mysql连接
    CollectStartWindow *start1;         //游戏1开始界面
    PuzzleStartWindow *start2;         //游戏2开始界面
    AnswerStartWindow *start3;         //游戏3开始界面
    bool isLogined;
    LoginDialog *login;           //登录界面
    InformationDialog *info;         //个人信息界面
    int currentId;                  //当前用户
};

#endif // MAINWINDOW_H
