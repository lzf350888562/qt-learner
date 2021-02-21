#ifndef COLLECTGAMEWINDOW_H
#define COLLECTGAMEWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QTimer>

struct keyWord{
    QRect rc;
    int type;      //是否隐藏
};

class CollectGameWindow : public QMainWindow
{
    Q_OBJECT
    QRect pplRect;
    QPixmap picPPL,picBack,picScore,picTime;
    QPixmap wordPic;
    keyWord word[44];
    int timer0;
    int timer1;
    int keyWordNumber;
    int interval,score,stopWatch;
public:
    explicit CollectGameWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void timerEvent(QTimerEvent *e);
    void closeEvent(QCloseEvent *e);

signals:
    void game1_Return();

public slots:
};
#endif // COLLECTGAMEWINDOW_H
