#include "DoubleFaceButton.h"

#include <QMessageBox>

DoubleFaceButton::DoubleFaceButton(QString normalImg, QString pressImg, QWidget *parent):QPushButton (parent),normalImgPath(normalImg),pressImgPath(pressImg)
{
    QPixmap pixmap;
    if(!pixmap.load(normalImgPath))
        QMessageBox().warning(this,"Error","START Button Picture path missing");
    setFixedSize(50,50);
    setStyleSheet("QPushButton{border:0px;}");
    setIcon(QIcon(pixmap));
    setIconSize(QSize(50,50));
}

void DoubleFaceButton::mousePressEvent(QMouseEvent *e)
{
    if(pressImgPath!="")   //拦截带有两个路径的按钮功能
        {
        QPixmap pixmap;
        if(!pixmap.load(pressImgPath))
            QMessageBox().warning(this,"Error","Button Picture 2 path missing");
        setFixedSize(50,50);
        setStyleSheet("QPushButton{border:0px;}");  //如果不加这个语句 按钮为带背景的矩形图片
        setIcon(QIcon(pixmap));
        setIconSize(QSize(50,50));
    }
    return QPushButton::mousePressEvent(e);  //剩下的交给父类处理,如果没有这条语句，前面的开始按钮功能将被拦截
}

void DoubleFaceButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath!="")   //拦截带有两个路径的按钮功能
        {
        QPixmap pixmap;
        if(!pixmap.load(normalImgPath))
            QMessageBox().warning(this,"Error","Button Picture 1 path missing");
        setFixedSize(50,50);
        setStyleSheet("QPushButton{border:0px;}");  //如果不加这个语句 按钮为带背景的矩形图片
        setIcon(QIcon(pixmap));
        setIconSize(QSize(50,50));
    }
    return QPushButton::mouseReleaseEvent(e);
}
