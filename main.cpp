#include "mplayer.h"

#include <QApplication>
#include <QDebug>
#include <QIcon>  
#include <QStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	// 设置 Windows Media Foundation 后端  
	QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
	QIcon::setThemeName("QIcon::ThemeIcon");  // 或其他适当的主题名称  
	// 设置媒体后端  
	qputenv("QT_MULTIMEDIA_PREFERRED_PLUGINS", "windowsmediafoundation");
    MPlayer w;
    w.show();
    return a.exec();
}
