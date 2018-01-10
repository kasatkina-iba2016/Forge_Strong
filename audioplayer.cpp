#include "audioplayer.h"
#include "ui_audioplayer.h"
#include <QFileDialog>
#include <QDir>
#include <QTime>

audioPlayer::audioPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::audioPlayer)
{

    ui->setupUi(this);
    playListModel=new QStandardItemModel(this);
    player=new QMediaPlayer(this);
    playList=new QMediaPlaylist(player);
    player->setPlaylist(playList);
    player->setVolume(20);
    ui->playListView->setModel(playListModel);
    playListModel->setHorizontalHeaderLabels(QStringList()<<tr("Audio Track")<<tr("File Path"));
    ui->playListView->hideColumn(1);
    ui->playListView->verticalHeader()->setVisible(false);
    ui->playListView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playListView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->playListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playListView->horizontalHeader()->setStretchLastSection(true);
    ui->playListView->setStyleSheet("QTableView {background:grey;}");

    ui->playButton->setStyleSheet("QToolButton:hover {background-color: transparent;}");
    ui->addButton->setStyleSheet("QToolButton:hover {background-color: transparent;}");
    ui->stopButton->setStyleSheet("QToolButton:hover {background-color: transparent;}");
    ui->prevButton->setStyleSheet("QToolButton:hover {background-color: transparent;}");
    ui->pauseButton->setStyleSheet("QToolButton:hover {background-color: transparent;}");
    ui->nextButton->setStyleSheet("QToolButton:hover {background-color: transparent;}");
    ui->volumeButton->setStyleSheet("QToolButton:hover {background-color: transparent;}");


    this->setStyleSheet("audioPlayer { background:qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #4c4e5a, stop:1 #2c2d33);}");
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    VolumeBefore=20;
    connect(ui->prevButton,&QToolButton::clicked,playList,&QMediaPlaylist::previous);
    connect(ui->nextButton,&QToolButton::clicked,playList,&QMediaPlaylist::next);
    connect(ui->playButton,&QToolButton::clicked,player,&QMediaPlayer::play);
    connect(ui->pauseButton,&QToolButton::clicked,player,&QMediaPlayer::pause);
    connect(ui->stopButton,&QToolButton::clicked,player,&QMediaPlayer::stop);

    connect(ui->playListView,&QTableView::doubleClicked, [this](const QModelIndex &index){
           playList->setCurrentIndex(index.row());
       });
    connect(playList, &QMediaPlaylist::currentIndexChanged, [this](int index){
           ui->currentTrack->setText(playListModel->data(playListModel->index(index, 0)).toString());
       });
    ui->volumeSlider->setRange(0,100);

    connect(ui->volumeSlider,SIGNAL(valueChanged(int)),SLOT(setNewVolume(int)));
    connect(ui->volumeButton,SIGNAL(clicked(bool)),SLOT(volumeButtonClicked()));
    connect(player,SIGNAL(positionChanged(qint64)),SLOT(setSliderPosition(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),SLOT(slotSetDuration(qint64)));
}

audioPlayer::~audioPlayer()
{
    delete ui;
    delete playListModel;
    delete playList;
    delete player;
}

void audioPlayer::on_addButton_clicked()
{
    QStringList files=QFileDialog::getOpenFileNames
                     (this,tr("Открыть файлы"),QString(),tr ("Аудио файлы(*.mp3)"));
    foreach (QString filePath, files) {
        QList<QStandardItem*> items;

        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        playListModel->appendRow(items);
        playList->addMedia(QUrl(filePath));
    }
}

void audioPlayer::setNewVolume(int vol)
{
  player->setVolume(vol);
  if (vol==0) ui->volumeButton->setIcon(QIcon(":/Pict/noVolume.png"));
  else ui->volumeButton->setIcon(QIcon(":/Pict/volume.png"));
  VolumeBefore=vol;
}

void audioPlayer::volumeButtonClicked()
{
    if (player->volume()==0)
    {
        ui->volumeButton->setIcon(QIcon(":/Pict/volume.png"));
        player->setVolume(VolumeBefore);
    }
    else
    {
        ui->volumeButton->setIcon(QIcon(":/Pict/noVolume.png"));
        player->setVolume(0);
    }

}

void audioPlayer::on_songPosition_sliderMoved(int position)
{
    player->setPosition(position);
}

void audioPlayer::setSliderPosition(qint64 position)
{
    ui->songPosition->setValue(position);
    ui->lblCurrent->setText(msecsToString(position));
    int nDuration=ui->songPosition->maximum();
    ui->lblRemember->setText(msecsToString(nDuration));
}

void audioPlayer::slotSetDuration(qint64 n)
{
    ui->songPosition->setRange(0,n);
    ui->lblCurrent->setText(msecsToString(0));
    ui->lblRemember->setText(msecsToString(n));
}

QString audioPlayer::msecsToString(qint64 position)
{
  int nHours=(position/(60*60*1000));
  int nMinutes=((position%(60*60*1000))/(60*1000));
  int nSeconds=((position%(60*1000))/1000);
  return QTime(nHours,nMinutes,nSeconds).toString("hh:mm:ss");
}

