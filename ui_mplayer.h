/********************************************************************************
** Form generated from reading UI file 'mplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MPLAYER_H
#define UI_MPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MPlayer
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QLabel *coverLabel;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_Title;
    QLabel *label_Artist;
    QLabel *label_Album;
    QSpacerItem *horizontalSpacer_2;
    QLabel *songInfoLabel;
    QHBoxLayout *horizontalLayout_5;
    QSlider *positionSlider;
    QLabel *timeLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *playModeButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QSlider *volumeSlider;
    QLabel *label_2;
    QSpinBox *timerStopSpinBox;
    QPushButton *SchuduleButton;
    QComboBox *OperationcomboBox;
    QListView *playlist;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addButton;
    QPushButton *removeButton;
    QPushButton *clearButton;

    void setupUi(QDialog *MPlayer)
    {
        if (MPlayer->objectName().isEmpty())
            MPlayer->setObjectName(QString::fromUtf8("MPlayer"));
        MPlayer->resize(246, 407);
        verticalLayout = new QVBoxLayout(MPlayer);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        coverLabel = new QLabel(MPlayer);
        coverLabel->setObjectName(QString::fromUtf8("coverLabel"));
        coverLabel->setMinimumSize(QSize(64, 64));
        coverLabel->setMaximumSize(QSize(128, 128));
        coverLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_4->addWidget(coverLabel);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        label_Title = new QLabel(MPlayer);
        label_Title->setObjectName(QString::fromUtf8("label_Title"));
        label_Title->setMinimumSize(QSize(160, 0));

        verticalLayout_2->addWidget(label_Title);

        label_Artist = new QLabel(MPlayer);
        label_Artist->setObjectName(QString::fromUtf8("label_Artist"));
        label_Artist->setMinimumSize(QSize(160, 0));

        verticalLayout_2->addWidget(label_Artist);

        label_Album = new QLabel(MPlayer);
        label_Album->setObjectName(QString::fromUtf8("label_Album"));
        label_Album->setMinimumSize(QSize(160, 0));

        verticalLayout_2->addWidget(label_Album);


        horizontalLayout_4->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);

        songInfoLabel = new QLabel(MPlayer);
        songInfoLabel->setObjectName(QString::fromUtf8("songInfoLabel"));
        songInfoLabel->setMinimumSize(QSize(0, 25));
        songInfoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        songInfoLabel->setWordWrap(true);

        verticalLayout->addWidget(songInfoLabel);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, 6, -1, 6);
        positionSlider = new QSlider(MPlayer);
        positionSlider->setObjectName(QString::fromUtf8("positionSlider"));
        positionSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_5->addWidget(positionSlider);

        timeLabel = new QLabel(MPlayer);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_5->addWidget(timeLabel);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        playButton = new QPushButton(MPlayer);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setMinimumSize(QSize(40, 24));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Play"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon);
        playButton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(playButton);

        stopButton = new QPushButton(MPlayer);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setMinimumSize(QSize(40, 24));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Stop"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon1);
        stopButton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(stopButton);

        prevButton = new QPushButton(MPlayer);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));
        prevButton->setMinimumSize(QSize(40, 24));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Pre"), QSize(), QIcon::Normal, QIcon::Off);
        prevButton->setIcon(icon2);
        prevButton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(prevButton);

        nextButton = new QPushButton(MPlayer);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setMinimumSize(QSize(40, 24));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Next"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon3);
        nextButton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(nextButton);

        playModeButton = new QPushButton(MPlayer);
        playModeButton->setObjectName(QString::fromUtf8("playModeButton"));
        playModeButton->setMinimumSize(QSize(40, 24));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Loop"), QSize(), QIcon::Normal, QIcon::Off);
        playModeButton->setIcon(icon4);
        playModeButton->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(playModeButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label = new QLabel(MPlayer);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        volumeSlider = new QSlider(MPlayer);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setMaximum(100);
        volumeSlider->setValue(50);
        volumeSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(volumeSlider);

        label_2 = new QLabel(MPlayer);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        timerStopSpinBox = new QSpinBox(MPlayer);
        timerStopSpinBox->setObjectName(QString::fromUtf8("timerStopSpinBox"));
        timerStopSpinBox->setMaximum(120);
        timerStopSpinBox->setValue(15);

        horizontalLayout_3->addWidget(timerStopSpinBox);

        SchuduleButton = new QPushButton(MPlayer);
        SchuduleButton->setObjectName(QString::fromUtf8("SchuduleButton"));
        SchuduleButton->setMinimumSize(QSize(40, 0));
        SchuduleButton->setMaximumSize(QSize(60, 16777215));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/Schedule"), QSize(), QIcon::Normal, QIcon::Off);
        SchuduleButton->setIcon(icon5);
        SchuduleButton->setIconSize(QSize(24, 24));
        SchuduleButton->setCheckable(true);

        horizontalLayout_3->addWidget(SchuduleButton);

        OperationcomboBox = new QComboBox(MPlayer);
        OperationcomboBox->addItem(QString());
        OperationcomboBox->addItem(QString());
        OperationcomboBox->addItem(QString());
        OperationcomboBox->setObjectName(QString::fromUtf8("OperationcomboBox"));
        OperationcomboBox->setMinimumSize(QSize(40, 0));
        OperationcomboBox->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_3->addWidget(OperationcomboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        playlist = new QListView(MPlayer);
        playlist->setObjectName(QString::fromUtf8("playlist"));
        playlist->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

        verticalLayout->addWidget(playlist);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addButton = new QPushButton(MPlayer);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        addButton->setMinimumSize(QSize(40, 24));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/Add"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon6);
        addButton->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(addButton);

        removeButton = new QPushButton(MPlayer);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setMinimumSize(QSize(40, 24));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/Remove"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon7);
        removeButton->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(removeButton);

        clearButton = new QPushButton(MPlayer);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setMinimumSize(QSize(40, 24));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/Clear"), QSize(), QIcon::Normal, QIcon::Off);
        clearButton->setIcon(icon8);
        clearButton->setIconSize(QSize(24, 24));

        horizontalLayout_2->addWidget(clearButton);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(MPlayer);

        QMetaObject::connectSlotsByName(MPlayer);
    } // setupUi

    void retranslateUi(QDialog *MPlayer)
    {
        MPlayer->setWindowTitle(QCoreApplication::translate("MPlayer", "MPlayer", nullptr));
        label_Title->setText(QString());
        label_Artist->setText(QString());
        label_Album->setText(QString());
        songInfoLabel->setText(QString());
        timeLabel->setText(QCoreApplication::translate("MPlayer", "00:00 / 00:00", nullptr));
#if QT_CONFIG(tooltip)
        playButton->setToolTip(QCoreApplication::translate("MPlayer", "\346\222\255\346\224\276", nullptr));
#endif // QT_CONFIG(tooltip)
        playButton->setText(QString());
#if QT_CONFIG(tooltip)
        stopButton->setToolTip(QCoreApplication::translate("MPlayer", "\345\201\234\346\255\242", nullptr));
#endif // QT_CONFIG(tooltip)
        stopButton->setText(QString());
#if QT_CONFIG(tooltip)
        prevButton->setToolTip(QCoreApplication::translate("MPlayer", "\344\270\212\344\270\200\351\246\226", nullptr));
#endif // QT_CONFIG(tooltip)
        prevButton->setText(QString());
#if QT_CONFIG(tooltip)
        nextButton->setToolTip(QCoreApplication::translate("MPlayer", "\344\270\213\344\270\200\351\246\226", nullptr));
#endif // QT_CONFIG(tooltip)
        nextButton->setText(QString());
#if QT_CONFIG(tooltip)
        playModeButton->setToolTip(QCoreApplication::translate("MPlayer", "\351\232\217\346\234\272\346\222\255\346\224\276", nullptr));
#endif // QT_CONFIG(tooltip)
        playModeButton->setText(QString());
        label->setText(QCoreApplication::translate("MPlayer", "\351\237\263\351\207\217", nullptr));
        label_2->setText(QCoreApplication::translate("MPlayer", "\346\227\266\351\225\277(\345\210\206)", nullptr));
#if QT_CONFIG(tooltip)
        SchuduleButton->setToolTip(QCoreApplication::translate("MPlayer", "\345\256\232\346\227\266", nullptr));
#endif // QT_CONFIG(tooltip)
        SchuduleButton->setText(QString());
        OperationcomboBox->setItemText(0, QCoreApplication::translate("MPlayer", "\345\201\234\346\255\242", nullptr));
        OperationcomboBox->setItemText(1, QCoreApplication::translate("MPlayer", "\344\275\223\347\234\240", nullptr));
        OperationcomboBox->setItemText(2, QCoreApplication::translate("MPlayer", "\345\205\263\346\234\272", nullptr));

#if QT_CONFIG(tooltip)
        addButton->setToolTip(QCoreApplication::translate("MPlayer", "\346\267\273\345\212\240", nullptr));
#endif // QT_CONFIG(tooltip)
        addButton->setText(QString());
#if QT_CONFIG(tooltip)
        removeButton->setToolTip(QCoreApplication::translate("MPlayer", "\347\247\273\351\231\244", nullptr));
#endif // QT_CONFIG(tooltip)
        removeButton->setText(QString());
#if QT_CONFIG(tooltip)
        clearButton->setToolTip(QCoreApplication::translate("MPlayer", "\346\270\205\347\251\272", nullptr));
#endif // QT_CONFIG(tooltip)
        clearButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MPlayer: public Ui_MPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MPLAYER_H
