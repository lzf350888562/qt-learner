#ifndef PUZZLESTARTWINDOW_H
#define PUZZLESTARTWINDOW_H

#include"PuzzleGameWindow.h"
#include"DoubleFaceButton.h"
#include <QMainWindow>
#include <QCloseEvent>
#include <QLabel>

class PuzzleStartWindow : public QMainWindow
{
    Q_OBJECT
    PuzzleGameWindow *game2;
    QLabel *bg;
    DoubleFaceButton *returnBtn;
public:
    explicit PuzzleStartWindow(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *e);
signals:
    void start2_Return();
public slots:
};

#endif // PUZZLESTARTWINDOW_H
