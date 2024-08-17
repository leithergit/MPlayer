﻿#pragma execution_character_set("utf-8")
#include "mplayer.h"
#include "ui_mplayer.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QProcess>
#include <QSettings>

#include <QDesktopWidget>
#include <QOperatingSystemVersion>  

#include "taglib/fileref.h"
#include "taglib/tag.h"
#include "taglib/mpegfile.h"
#include "taglib/id3v2tag.h"
#include "taglib/attachedpictureframe.h"

#include <taglib/taglib.h>  
#include <taglib/fileref.h>  
#include <taglib/tag.h>  
#include <taglib/tpropertymap.h>  

// For MP3 files  
#include <taglib/mpegfile.h>  
#include <taglib/id3v2tag.h>  
#include <taglib/attachedpictureframe.h>  

// For FLAC files  
#include <taglib/flacfile.h>  
#include <taglib/flacpicture.h>  

// For MP4/M4A files  
#include <taglib/mp4file.h>  
#include <taglib/mp4tag.h>  
#include <taglib/mp4coverart.h>  


MPlayer::MPlayer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MPlayer)
    , player(new QMediaPlayer(this))
    , playlist(new QMediaPlaylist(this))
    , playlistModel(new QStandardItemModel(this))
{
#ifdef Q_OS_WIN  
	if (QOperatingSystemVersion::current() >= QOperatingSystemVersion::Windows10) {
		HWND hwnd = (HWND)this->winId();
		BOOL value = TRUE;
		DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));

		// 设置标题栏颜色  
		COLORREF darkColor = RGB(53, 53, 53);  // 深灰色  
		DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &darkColor, sizeof(darkColor));

		// 设置标题文本颜色  
		COLORREF textColor = RGB(255, 255, 255);  // 白色  
		DwmSetWindowAttribute(hwnd, DWMWA_TEXT_COLOR, &textColor, sizeof(textColor));
	}
#endif 

    ui->setupUi(this);
    loadSettings();
    setWindowFlags( Qt::WindowCloseButtonHint);
    loadPlaylist();
    player->setPlaylist(playlist);
    ui->playlist->setModel(playlistModel);
    setupConnections();

    currentPlayMode = Sequential;

    sequentialIcon.addFile(QString::fromUtf8(":/Sequential"), QSize(), QIcon::Normal, QIcon::Off);
    randomIcon.addFile(QString::fromUtf8(":/Shuffle"), QSize(), QIcon::Normal, QIcon::Off);
    singleLoopIcon.addFile(QString::fromUtf8(":/Loop"), QSize(), QIcon::Normal, QIcon::Off);
    PlayIcon.addFile(QString::fromUtf8(":/Play"), QSize(), QIcon::Normal, QIcon::Off);
    PauseIcon.addFile(QString::fromUtf8(":/Pause"), QSize(), QIcon::Normal, QIcon::Off);

    scheduleTimer = new QTimer(this);
    isScheduleActive = false;
	connect(player, &QMediaPlayer::currentMediaChanged, this, &MPlayer::onCurrentMediaChanged);

	// 禁用编辑  
	ui->playlist->setEditTriggers(QAbstractItemView::NoEditTriggers);

    updatePlayMode();
}

void MPlayer::closeEvent(QCloseEvent* event)
{
	saveSettings();
	event->accept();
}

MPlayer::~MPlayer()
{
    if (player)
        player->stop();
    saveSettings();
    if (scheduleTimer)
        scheduleTimer->stop();
    delete ui;
}

void MPlayer::saveSettings()
{
	QSettings settings("MyHome", "MPlayer");
	settings.setValue("geometry", saveGeometry());
}

void MPlayer::setDefaultSizeAndPosition()
{
	// 设置默认大小  
	resize(500, 700);

	// 将窗口移动到屏幕中央  
	QRect screenGeometry = QApplication::desktop()->availableGeometry();
	int x = (screenGeometry.width() - width()) / 2;
	int y = (screenGeometry.height() - height()) / 2;
	move(x, y);
}

void MPlayer::ensureWindowIsOnScreen()
{
	QRect screenGeometry = QApplication::desktop()->availableGeometry();
	QRect windowGeometry = geometry();

	// 确保窗口至少部分可见  
	if (!screenGeometry.intersects(windowGeometry))
	{
		// 如果完全不可见，则重置到默认位置和大小  
		setDefaultSizeAndPosition();
	}
	else
	{
		// 调整位置以确保完全在屏幕内  
		int x = qMax(windowGeometry.x(), screenGeometry.x());
		int y = qMax(windowGeometry.y(), screenGeometry.y());
		x = qMin(x, screenGeometry.right() - width());
		y = qMin(y, screenGeometry.bottom() - height());
		move(x, y);
	}
}

void MPlayer::loadSettings()
{
	QSettings settings("MyHome", "MPlayer");
	QByteArray geometryData = settings.value("geometry").toByteArray();
	if (geometryData.isEmpty() || !restoreGeometry(geometryData))
		setDefaultSizeAndPosition();
	else
		ensureWindowIsOnScreen();
}

void MPlayer::setupConnections()
{
    connect(player, &QMediaPlayer::positionChanged, this, &MPlayer::positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MPlayer::durationChanged);
    //connect(player, &QMediaPlayer::metaDataChanged, this, &MPlayer::metaDataChanged);
    connect(player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &MPlayer::metaDataChanged);

    connect(playlist, &QMediaPlaylist::mediaInserted, this, &MPlayer::onPlaylistChanged);
    connect(playlist, &QMediaPlaylist::mediaRemoved, this, &MPlayer::onPlaylistChanged);
    connect(playlist, &QMediaPlaylist::mediaChanged, this, &MPlayer::onPlaylistChanged);
	connect(playlist, &QMediaPlaylist::currentIndexChanged, this, [this](int index) {
		qDebug() << "Playlist current index changed to:" << index;
		if (index != -1) {
			QUrl mediaUrl = playlist->media(index).canonicalUrl();
			qDebug() << "Current media URL:" << mediaUrl.toString();
		}
	});

	connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
		qDebug() << "Media status changed:" << status;
	});

	connect(player, &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State state) {
		qDebug() << "Player state changed:" << state;
	});
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MPlayer::onMediaStatusChanged);
    connect(player, &QMediaPlayer::stateChanged, this, [this](QMediaPlayer::State state)
    {
        ui->playButton->setToolTip(state == QMediaPlayer::PlayingState ? "暂停" : "播放");
    });

}


void MPlayer::savePlaylist()
{
    QJsonObject playlistObject;
    QJsonArray tracksArray;

    for (int i = 0; i < playlist->mediaCount(); ++i) {
        QJsonObject trackObject;
        trackObject["url"] = playlist->media(i).request().url().toString();
        tracksArray.append(trackObject);
    }

    playlistObject["tracks"] = tracksArray;
    playlistObject["lastPlayed"] = player->currentMedia().request().url().toString();
    playlistObject["position"] = player->position();

    QJsonDocument doc(playlistObject);
    QFile file("playlist.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void MPlayer::loadPlaylist()
{
    QFile file("playlist.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(data));
        QJsonObject playlistObject = doc.object();

        QJsonArray tracksArray = playlistObject["tracks"].toArray();
        for (const QJsonValue &value : tracksArray) {
            QJsonObject trackObject = value.toObject();
            playlist->addMedia(QUrl(trackObject["url"].toString()));
        }
		qDebug() << "Songs = " << playlist->mediaCount();
        lastPlayedFile = playlistObject["lastPlayed"].toString();
        lastPlayedPosition = playlistObject["position"].toInt();

        file.close();
    }
    updatePlaylistView();
}

void MPlayer::onPlaylistChanged()
{
    savePlaylist();
}

void MPlayer::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::LoadedMedia && player->currentMedia().canonicalUrl().toString() == lastPlayedFile) {
        player->setPosition(lastPlayedPosition);
        if (player->state() != QMediaPlayer::PlayingState) {
            player->pause(); // 确保不自动播放
        }
    }
}

void MPlayer::updatePlaylistView()
{
    playlistModel->clear();
    for (int i = 0; i < playlist->mediaCount(); ++i) 
    {
        QUrl url = playlist->media(i).canonicalUrl();
        QStandardItem *item = new QStandardItem(url.fileName());
        item->setData(url, Qt::UserRole);
        playlistModel->appendRow(item);
    }
}

void MPlayer::on_playButton_clicked()
{
    if (player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
        ui->playButton->setToolTip("播放");
		ui->playButton->setIcon(PlayIcon);
    } 
    else 
    {
        if (playlist->currentIndex() == -1 && playlist->mediaCount() > 0) {
            playlist->setCurrentIndex(0);
        }
        
        player->setVolume(ui->volumeSlider->value());
        player->play();
        ui->playButton->setToolTip("暂停");
		ui->playButton->setIcon(PauseIcon);
        updatePlaylistSelection();
    }
}

void MPlayer::on_stopButton_clicked()
{
    player->stop();
    ui->playButton->setToolTip("播放");
}

void MPlayer::on_prevButton_clicked()
{
    playlist->previous();
    updatePlaylistSelection();
}

void MPlayer::on_nextButton_clicked()
{
    playlist->next();
    updatePlaylistSelection();
}

void MPlayer::updatePlaylistSelection()
{
	int currentIndex = playlist->currentIndex();
	ui->playlist->setCurrentIndex(playlistModel->index(currentIndex, 0));
}

void MPlayer::on_addButton_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "添加文件", QStandardPaths::writableLocation(QStandardPaths::MusicLocation), "音频文件 (*.mp3 *.mp4 *.aac *.wav *.m4a)");
    for (const QString &file : files) 
    {
        playlist->addMedia(QUrl::fromLocalFile(file));
    }
    updatePlaylistView();
    savePlaylist();
}

void MPlayer::on_removeButton_clicked()
{
    QItemSelectionModel *selectionModel = ui->playlist->selectionModel();
    QModelIndexList indexes = selectionModel->selectedIndexes();

    for (int i = indexes.count() - 1; i >= 0; --i) {
        int row = indexes.at(i).row();
        if (row == playlist->currentIndex()) {
            player->stop();
        }
        playlist->removeMedia(row);
        playlistModel->removeRow(row);
    }
    savePlaylist();
}

void MPlayer::on_clearButton_clicked()
{
    player->stop();
    playlist->clear();
    playlistModel->clear();
    savePlaylist();
}

void MPlayer::on_volumeSlider_valueChanged(int value)
{
    player->setVolume(value);
}

void MPlayer::on_positionSlider_sliderMoved(int position)
{
    player->setPosition(position);
}

void MPlayer::updateDurationInfo(qint64 currentInfo)
{
    QString tStr = formatTime(currentInfo) + " / " + formatTime(player->duration());
    ui->timeLabel->setText(tStr);
}

void MPlayer::positionChanged(qint64 position)
{
    ui->positionSlider->setValue(position);
    updateDurationInfo(position);
}

void MPlayer::durationChanged(qint64 duration)
{
    ui->positionSlider->setRange(0, duration);
}

void MPlayer::on_playlist_doubleClicked(const QModelIndex &index)
{
	int row = index.row();
	playlist->setCurrentIndex(row);
    player->setVolume(ui->volumeSlider->value());
	player->play();
	ui->playButton->setToolTip("暂停");
	updatePlaylistSelection();
}

QString MPlayer::formatTime(qint64 milliseconds)
{
    qint64 seconds = milliseconds / 1000;
    qint64 minutes = seconds / 60;
    seconds %= 60;
    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}

void MPlayer::metaDataChanged()
{
    if (player->isMetaDataAvailable()) {
        /*QString title = player->metaData("Title").toString();
        QString artist = player->metaData("Artist").toString();*/        

        QUrl currentMedia = playlist->currentMedia().canonicalUrl();
        QString strFileName = QFileInfo(currentMedia.toLocalFile()).fileName();
        ui->songInfoLabel->setText(strFileName);
        loadFileMetadata(currentMedia.toLocalFile());
    }
}

void MPlayer::loadFileMetadata(const QString &filePath)
{
     TagLib::FileRef f(filePath.toLocal8Bit().toStdString().c_str());
     if (!f.isNull() && f.tag())
     {
     	TagLib::Tag* tag = f.tag();
     	QString title = QString::fromStdString(tag->title().to8Bit(true));
     	QString artist = QString::fromStdString(tag->artist().to8Bit(true));
     	QString album = QString::fromStdString(tag->album().to8Bit(true));

     	// 显示元数据
     	ui->coverLabel->setText(album.isEmpty() ? "Unknown Album" : album);

     	// 提取封面图片
     	QPixmap coverArtImage;
     	QString fileExtension = QFileInfo(filePath).suffix().toLower();

     	if (fileExtension == "mp3")
     	{
             TagLib::MPEG::File mpegFile(filePath.toLocal8Bit().toStdString().c_str());
     		if (mpegFile.isValid() && mpegFile.ID3v2Tag())
     		{
     			TagLib::ID3v2::FrameList frameList = mpegFile.ID3v2Tag()->frameList("APIC");
     			if (!frameList.isEmpty())
     			{
     				TagLib::ID3v2::AttachedPictureFrame* coverFrame = static_cast<TagLib::ID3v2::AttachedPictureFrame*>(frameList.front());
                     coverArtImage.loadFromData(reinterpret_cast<const uchar*>(coverFrame->picture().data()), coverFrame->picture().size());
     			}
     		}
     	}
     	else if (fileExtension == "flac")
     	{
             TagLib::FLAC::File flacFile(filePath.toLocal8Bit().toStdString().c_str());
     		if (flacFile.isValid() && !flacFile.pictureList().isEmpty())
     		{
     			TagLib::FLAC::Picture* cover = flacFile.pictureList().front();
                 coverArtImage.loadFromData(reinterpret_cast<const uchar*>(cover->data().data()), cover->data().size());
     		}
     	}
     	else if (fileExtension == "m4a" || fileExtension == "mp4")
     	{
             TagLib::MP4::File mp4File(filePath.toLocal8Bit().toStdString().c_str());
     		if (mp4File.isValid() && mp4File.tag())
     		{
     			TagLib::MP4::Tag* mp4tag = mp4File.tag();
     			TagLib::MP4::ItemMap items = mp4tag->itemMap();
     			if (items.contains("covr"))
     			{
     				TagLib::MP4::CoverArtList coverArtList = items["covr"].toCoverArtList();
     				if (!coverArtList.isEmpty())
     				{
     					TagLib::MP4::CoverArt coverArt = coverArtList.front();
                         TagLib::MP4::CoverArt::Format  nF = coverArt.format();
     					QByteArray imageData(coverArt.data().data(), coverArt.data().size());
     					coverArtImage.loadFromData(imageData);
     				}
     			}
     		}
     	}

     	// 显示封面图片
     	if (!coverArtImage.isNull())
     	{
             ui->coverLabel->show();
			 ui->label_Title->show();
			 ui->label_Artist->show();
			 ui->label_Album->show();
     		 ui->coverLabel->setPixmap(coverArtImage.scaled(ui->coverLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
             ui->label_Title->setText(title);
             ui->label_Artist->setText(artist);
             ui->label_Album->setText(album);
     	}
     	else
     	{
             ui->coverLabel->hide();
			 ui->label_Title->hide();
			 ui->label_Artist->hide();
			 ui->label_Album->hide();
     	}
     }
     else
     {
         ui->coverLabel->hide();
		 ui->label_Title->hide();
		 ui->label_Artist->hide();
		 ui->label_Album->hide();
     }
}

void MPlayer::updatePlayMode()
{
    switch(currentPlayMode) {
    case Sequential:
        ui->playModeButton->setIcon(sequentialIcon);
        //ui->playModeButton->setText("顺序播放");
        ui->playModeButton->setToolTip("顺序播放");
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
        break;
    case Random:
        ui->playModeButton->setIcon(randomIcon);
        //ui->playModeButton->setText("随机播放");
        ui->playModeButton->setToolTip("随机播放");
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        break;
    case SingleLoop:
        ui->playModeButton->setIcon(singleLoopIcon);
        //ui->playModeButton->setText("单曲循环");
        ui->playModeButton->setToolTip("单曲循环");
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        break;
    }
}

void MPlayer::on_playModeButton_clicked()
{
    switch(currentPlayMode) {
    case Sequential:
        currentPlayMode = Random;
        break;
    case Random:
        currentPlayMode = SingleLoop;
        break;
    case SingleLoop:
        currentPlayMode = Sequential;
        break;
    }
    updatePlayMode();
}


void MPlayer::on_SchuduleButton_clicked()
{
    if (!isScheduleActive) 
    {
        isVolumeFading = false;
        // 激活定时器
        int minutes = ui->timerStopSpinBox->value();
        if (minutes > 0) 
        {
            remainingTime = minutes * 60;
			connect(scheduleTimer, &QTimer::timeout, this, QOverload<>::of(&MPlayer::Update));
            scheduleTimer->start(1000);
            ui->SchuduleButton->setChecked(true);
            ui->timerStopSpinBox->setReadOnly(true);
           
            updateWindowTitle();
            isScheduleActive = true;
        }
    } 
    else
    {
        // 停止定时器
        isScheduleActive = false;
        scheduleTimer->stop();
        ui->SchuduleButton->setChecked(false);
        ui->timerStopSpinBox->setReadOnly(false);
		disconnect(scheduleTimer, &QTimer::timeout, this, &MPlayer::Update);
		setWindowTitle("MPlayer");
    }
}

void MPlayer::updateWindowTitle()
{
	int minutes = remainingTime / 60;
	int seconds = remainingTime % 60;
	setWindowTitle(QString("MPlayer - (%1:%2)").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0')));
}

void MPlayer::Update()
{
    if (remainingTime <= 30 && !isVolumeFading)  // 最后30秒  
    {
		originalVolume = (float)player->volume();
		nDecreaseVolumeStep = (float)originalVolume / 30;
		isVolumeFading = true;
    }
	
	if (isVolumeFading) 
    {
		if (originalVolume > 0)
        {
            originalVolume -= nDecreaseVolumeStep;
            if (originalVolume <= 0.0f)
            {
				originalVolume = 0.0f;
			}
			player->setVolume((int)originalVolume);
			ui->volumeSlider->setValue((int)originalVolume);
		}
	}

	if (remainingTime <= 0) {
		scheduleTimer->stop();
		isScheduleActive = false;
		player->stop();
		setWindowTitle("MPlayer");
		
		QString operation = ui->OperationcomboBox->currentText();

		if (operation == "停止") {
			player->stop();
		}
		else if (operation == "休眠") {
			QProcess::startDetached("rundll32.exe", QStringList() << "powrprof.dll,SetSuspendState" << "0,1,0");
		}
		else if (operation == "关机") {
			QProcess::startDetached("shutdown", QStringList() << "-s" << "-t" << "0");
		}

		// 重置定时器状态
		ui->SchuduleButton->setChecked(false);
		ui->timerStopSpinBox->setReadOnly(false);
		isScheduleActive = false;
		
	}
	else 
    {
		updateWindowTitle();
	}
    
	remainingTime--;
}

void MPlayer::volumeDecrease()
{
    originalVolume = player->volume();
    isVolumeFading = true;
}

void MPlayer::onCurrentMediaChanged(const QMediaContent& content)
{
    updatePlaylistSelection();

    // 更新播放列表项的颜色  
	for (int i = 0; i < playlistModel->rowCount(); ++i) {
		QModelIndex index = playlistModel->index(i, 0);
		if (i == playlist->currentIndex()) {
			playlistModel->setData(index, QBrush(Qt::red), Qt::ForegroundRole);
		}
		else {
			playlistModel->setData(index, QBrush(Qt::white), Qt::ForegroundRole);
		}
	}
}

#ifdef Q_OS_WIN  

// 在您的主窗口类中  
//bool MPlayer::nativeEvent(const QByteArray& eventType, void* message, long* result)
//{
//	Q_UNUSED(eventType);
//	Q_UNUSED(result);
//
//	MSG* msg = static_cast<MSG*>(message);
//	if (msg->message == WM_NCCALCSIZE && msg->wParam == TRUE) {
//		DWORD style = GetWindowLong((HWND)winId(), GWL_STYLE);
//		if (style & WS_MAXIMIZE) {
//			NCCALCSIZE_PARAMS* params = reinterpret_cast<NCCALCSIZE_PARAMS*>(msg->lParam);
//			params->rgrc[0].top += 1;
//		}
//	}
//	else if (msg->message == WM_CREATE) {
//		COLORREF darkColor = RGB(53, 53, 53);  // 使用您想要的深色  
//		DwmSetWindowAttribute((HWND)winId(), DWMWA_CAPTION_COLOR, &darkColor, sizeof(darkColor));
//	}
//
//	return false;
//}
#endif