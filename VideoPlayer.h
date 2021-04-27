#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>

namespace Ui {
class VideoPlayer;
}


class VideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VideoPlayer(int chapterNum,QWidget *parent = 0);
    ~VideoPlayer();
    //是否加载视频
    bool            m_bReLoad;
public slots:
    //滑动条变化
    void            OnSlider(qint64);
    //持续时间
    void            OnDurationChanged(qint64);
    //状态改变
    void            OnStateChanged(QMediaPlayer::State);
private:
    //播放窗口
    QVideoWidget    *       m_pPlayerWidget;
    //播放器
    QMediaPlayer    *       m_pPlayer;
    Ui::VideoPlayer *       ui;
protected:
    void closeEvent(QCloseEvent *e);

};

#endif // VIDEOPLAYER_H
