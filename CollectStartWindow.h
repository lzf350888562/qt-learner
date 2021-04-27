#ifndef COLLECTSTARTWINDOW_H
#define COLLECTSTARTWINDOW_H

#include"CollectGameWindow.h"
#include "DoubleFaceButton.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QLabel>

class CollectStartWindow : public QMainWindow
{
    Q_OBJECT
    CollectGameWindow *game1;
    QLabel *bg;
    DoubleFaceButton *returnBtn;
public:
    explicit CollectStartWindow(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *e);
signals:
    void start1_Return();

public slots:
};


#endif // COLLECTSTARTWINDOW_H
