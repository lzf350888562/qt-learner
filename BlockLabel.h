#ifndef BLOCKLABEL_H
#define BLOCKLABEL_H

#include <QLabel>
#include<QPropertyAnimation>

class BlockLabel : public QLabel
{
    Q_OBJECT
    QImage myImage;                                 // 块图片
    int currentX,currentY;                          // 当前位置
    int positive;                                   // 旋转位置是否正确
    QPropertyAnimation *animation;                  // 动画效果
public:
    enum direction{up=1,down=-1,left=2,right=-2};   // 方向枚举
    int positionX,positionY;                        // 预设位置
    explicit BlockLabel(QImage image,QWidget *parent = nullptr);
    // 是否有图片正在运行改变动画,如果有则禁用鼠标点击事件
    static int isChanging;
    void rotation();                                // 旋转
    void moveAnimation(direction d);                // 移动
    bool isOk();                                    // 该块图片是否归位
    void setPosition(int x,int y);                  // 设置X,Y
    void haveRotated();                             // 旋转了
signals:

public slots:
};

#endif // BLOCKLABEL_H
