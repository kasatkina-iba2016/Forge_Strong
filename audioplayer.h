#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace Ui {
class audioPlayer;
}

class audioPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit audioPlayer(QWidget *parent = 0);
    ~audioPlayer();
     QMediaPlayer *player;
     int VolumeBefore;

private slots:

    void on_addButton_clicked();
    void setNewVolume(int vol);
    void volumeButtonClicked();
    void on_songPosition_sliderMoved(int position);
    void setSliderPosition(qint64 position);
    void slotSetDuration(qint64 n);
private:
    Ui::audioPlayer *ui;
    QStandardItemModel *playListModel;
    QMediaPlaylist *playList;
    QString msecsToString (qint64 position);

};

#endif // AUDIOPLAYER_H
