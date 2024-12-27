#include "src/math/headers/Vector2D.h"
#include "src/forms/mainwindow.h"
#include "src/obj_utils/objreader/ObjReader.h"

#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <omp.h>

int main(int argc, char *argv[])
{
	//Model ans(ObjReader::read(filename));
	omp_set_dynamic(1); // Enable dynamic adjustment
	std::cout << std::filesystem::current_path();
    QApplication a(argc, argv);

	QFile file(":/buttonStyle.css");
	if (file.open(QFile::ReadOnly)) {
		QString styleSheet = QTextStream(&file).readAll();
		a.setStyleSheet(styleSheet);
		file.close();
	}
    MainWindow w;
	w.setMinimumSize(800, 600);
	w.setMaximumSize(1920, 1080);
	w.setWindowTitle("Toster");
	w.setWindowIcon(QIcon(":/toster.png"));

	//w.models[0] = ObjReader::read(filename);

//	w.models[0] = ObjReader::read(filename);
//	w.materials[0] = Material(0,0,0);

//    w.models.emplace_back();
    // w.models.emplace_back(ans);
	w.setWindowFlags(Qt::FramelessWindowHint);
    w.showFullScreen();

    return a.exec();
}
