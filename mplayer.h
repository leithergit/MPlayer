﻿#ifndef MPLAYER_H
#define MPLAYER_H

#include <QDialog>
#include <QDialog>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include <QTime>
#include <QStandardItemModel>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QEvent>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MPlayer;
}
QT_END_NAMESPACE

class MPlayer : public QDialog
{
    Q_OBJECT

public:
    explicit  MPlayer(QWidget *parent = nullptr);
    ~MPlayer();

protected:
	void closeEvent(QCloseEvent* event) override;
private slots:
    void on_playModeButton_clicked();
    void on_playButton_clicked();
    void on_stopButton_clicked();
    void on_prevButton_clicked();
    void on_nextButton_clicked();
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_clearButton_clicked();
    void on_volumeSlider_valueChanged(int value);
    void on_positionSlider_sliderMoved(int position);
    void on_timerStopSpinBox_valueChanged(int arg1);
    void on_playlist_doubleClicked(const QModelIndex &index);

    void updateDurationInfo(qint64 currentInfo);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void metaDataChanged();

    void updatePlayMode();

    void on_SchuduleButton_clicked();

    void Update();
    void onPlaylistChanged();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
	void onCurrentMediaChanged(const QMediaContent& content);

private:
    enum PlayMode {
        Sequential,
        Random,
        SingleLoop
    };
	void updatePlaylistSelection();
	void updateWindowTitle();
	void volumeDecrease();
	int originalVolume;
	bool isVolumeFading;
    int remainingTime = 0;
    QTimer *scheduleTimer;
    bool isScheduleActive;
    PlayMode currentPlayMode;
    QIcon sequentialIcon;
    QIcon randomIcon;
    QIcon singleLoopIcon;
    Ui::MPlayer *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QTimer *fadeOutTimer;
    QStandardItemModel *playlistModel;
    void setupConnections();
    void updateButtons();
	void saveSettings();
	void loadSettings();
	void setDefaultSizeAndPosition();
	void ensureWindowIsOnScreen();
    void loadPlaylist();
    void savePlaylist();
    void updatePlaylistView();
    QString formatTime(qint64 milliseconds);
    void loadFileMetadata(const QString &filePath);

    QString lastPlayedFile;
    int lastPlayedPosition;

};
#endif // MPLAYER_H