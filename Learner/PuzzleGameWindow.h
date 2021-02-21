#ifndef PUZZLEGAMEWINDOW_H
#define PUZZLEGAMEWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QLabel>
#include <QLCDNumber>
#include <BlockLabel.h>

class PuzzleGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PuzzleGameWindow(QWidget *parent = nullptr);
private:
    QTimer *timer;                          // 计时器
    QPixmap* image;                         // 原图
    BlockLabel* blocks[3][3];               // 图片块
    int flagOfImages[3][3];                 // 图片块标记，1为图片 0为空白
    unsigned int stopWatch;                 // 配合计时器按秒计时
    QLCDNumber *stopWatchLCD;               // LCD显示计时
    int stepTotal;                          // 总操作步数
    QLCDNumber *stepTotalLCD;               // LCD显示步数
    bool isFinished;                        // 游戏是否完成
    // 初始化图片块
    void imageInit();
    // 打乱图片块
    void upsetImage();
    // 计时器设置与开启
    void timerInit();
    // 交换图片块指针
    void swapBlocks(int x1,int y1,int x2,int y2);
    // 检查每个图片块是否归位
    bool check();
    //完成后执行的操作
    void finished();
protected:
    //鼠标点击事件
    void mousePressEvent(QMouseEvent *e);
    //点击关闭时的处理 需要关闭计时器
    void closeEvent(QCloseEvent *e); 
signals:
    //返回上一个界面的信号
    void game2_Return();
public slots:
};

#endif // PUZZLEGAMEWINDOW_H
