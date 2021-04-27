#include "VideoPlayer.h"
#include "ui_VideoPlayer.h"

VideoPlayer::VideoPlayer(int chapterNum,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);

    setWindowTitle("在线学习");
    QPixmap titlePix(":/img/book.png");
    setWindowIcon(QIcon(titlePix));
    m_pPlayer = new QMediaPlayer;
    m_pPlayerWidget = new QVideoWidget;
    m_pPlayer->setVideoOutput(m_pPlayerWidget);
    ui->verticalLayout->addWidget(m_pPlayerWidget);

    m_pPlayerWidget->setAutoFillBackground(true);
    QPalette qplte;
    qplte.setColor(QPalette::Window, QColor(0,0,0));
    m_pPlayerWidget->setPalette(qplte);
    //设置视频
    m_pPlayer->setMedia(QUrl::fromLocalFile(QString("E:\\Projects\\Qt Projects\\MyProject\\Learner\\Learner\\video\\chapter%1.flv").arg(chapterNum+1)));
    m_bReLoad = true;
    ui->slider->setValue(0);
    //播放
    connect(ui->BtnPlay, SIGNAL(clicked()), m_pPlayer, SLOT(play()));
    //停止
    connect(ui->BtnStop, SIGNAL(clicked()), m_pPlayer, SLOT(stop()));

    connect(m_pPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(OnStateChanged(QMediaPlayer::State)));

    ui->BtnStop->setEnabled(false);
    //设置滑块行为
    m_bReLoad = true;
    ui->slider->setEnabled(false);
    connect(m_pPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(OnSlider(qint64)));
    connect(m_pPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(OnDurationChanged(qint64)));
    //滑动条按下动态改变
    connect(ui->slider, SIGNAL(sigProgress(qint64)), m_pPlayer, SLOT(setPosition(qint64)));
}

VideoPlayer::~VideoPlayer()
{
    delete m_pPlayer;
    delete m_pPlayerWidget;
    delete ui;
}

void VideoPlayer::OnSlider(qint64 i64Pos)
{
    ui->slider->setProgress(i64Pos);
}

void VideoPlayer::OnDurationChanged(qint64 i64Duration)
{
    if(i64Duration > 0 && m_bReLoad)
    {
        ui->slider->setRange(0, i64Duration);
        m_bReLoad = false;
    }
}


void VideoPlayer::OnStateChanged(QMediaPlayer::State enumState)
{
    if(QMediaPlayer::StoppedState == enumState)
    {
        ui->BtnPlay->setEnabled(true);
        ui->BtnStop->setEnabled(false);
        ui->slider->setEnabled(false);
    }
    else if(QMediaPlayer::PlayingState == enumState)
    {
        ui->BtnPlay->setEnabled(false);
        ui->BtnStop->setEnabled(true);
        ui->slider->setEnabled(true);
    }
}

void VideoPlayer::closeEvent(QCloseEvent *e)
{
    m_pPlayer->stop();
}
