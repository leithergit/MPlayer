#include "mplayer.h"

#include <QApplication>
#include <QDebug>
#include <QIcon>  
#include <QStyle>
#include <QStyleFactory>

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

	// 设置兼容的样式
	QApplication::setStyle(QStyleFactory::create("Fusion"));
	// 创建并应用暗色调色板
	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::WindowText, Qt::white);
	darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
	darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
	darkPalette.setColor(QPalette::ToolTipText, QColor(162, 162, 162));
	darkPalette.setColor(QPalette::Text, Qt::white);
	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ButtonText, Qt::white);
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(255, 183, 47));
	darkPalette.setColor(QPalette::Highlight, QColor(255, 183, 47));
	darkPalette.setColor(QPalette::HighlightedText, Qt::black);
	// 设置禁用状态下的窗口文本颜色
	darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, Qt::gray);
	// 设置禁用状态下的按钮文本颜色
	darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::gray);
	a.setPalette(darkPalette);

	//QString styleSheet = R"(  
 //   //QDialog {  
 //   //    background-color: #353535;  
 //   //}  
 //   QDialog::title {  
 //       background-color: #353535;  
 //       color: white;  
 //       padding-top: 4px;  
 //   } )";

	//a.setStyleSheet(styleSheet);


    MPlayer w;
    w.show();
    return a.exec();
}
