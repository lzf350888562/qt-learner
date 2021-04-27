#ifndef DOUBLEFACEBUTTON_H
#define DOUBLEFACEBUTTON_H

#include <QPushButton>

class DoubleFaceButton : public QPushButton
{
    Q_OBJECT
    QString normalImgPath,pressImgPath;
public:
    explicit DoubleFaceButton(QString normalImg,QString pressImg,QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // DOUBLEFACEBUTTON_H
