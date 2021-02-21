#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
//动画按钮
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QString imgPath, QWidget *parent = nullptr);
    void shake();
protected:

signals:

public slots:
};
#endif // MYPUSHBUTTON_H
