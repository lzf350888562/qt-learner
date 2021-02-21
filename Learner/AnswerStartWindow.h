#ifndef ANSWERSTARTWINDOW_H
#define ANSWERSTARTWINDOW_H


#include  "DoubleFaceButton.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QLabel>

class AnswerStartWindow : public QMainWindow
{
    Q_OBJECT
    DoubleFaceButton *returnBtn;
public:
    explicit AnswerStartWindow(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *e);
    void closeEvent(QCloseEvent *e);
signals:
    void start3_Return();
public slots:
};

#endif // ANSWERSTARTWINDOW_H
