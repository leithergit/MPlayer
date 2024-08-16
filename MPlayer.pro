QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++17

QMAKE_CXXFLAGS += -Wall

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mplayer.cpp

HEADERS += \
    mplayer.h

FORMS += \
    mplayer.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32 {
INCLUDEPATH += $$PWD/TagLib/include
LIBS += -L$$PWD/TagLib/lib -ltag
#QT += json
}

android {
    QT += androidextras

    ANDROID_EXTRA_LIBS += $$[QT_INSTALL_PLUGINS]/platforms/libplugins_platforms_qtforandroid_armeabi-v7a.so
    # LIBS += -L$$PWD/TagLib.Android/lib/ -ltag
    # INCLUDEPATH += $$PWD/TagLib.Android/include
    DISTFILES += \
        android/AndroidManifest.xml \
        android/build.gradle \
        android/gradle.properties \
        android/gradle/wrapper/gradle-wrapper.jar \
        android/gradle/wrapper/gradle-wrapper.properties \
        android/gradlew \
        android/gradlew.bat \
        android/res/values/libs.xml \
        android/res/xml/qtprovider_paths.xml

}

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    resource.qrc


