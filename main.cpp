#include "src/math/headers/Vector2D.h"
#include "src/forms/mainwindow.h"
#include "src/obj_utils/objreader/ObjReader.h"

#include <iostream>
#include <QApplication>
#include <QPushButton>
#include <omp.h>

int main(int argc, char *argv[])
{
    //std::string filename("C:/Users/Пользователь/CLionProjects/3DModels/Faceform/WrapBody.obj");
    // std::string filename("C:/Users/Пользователь/CLionProjects/3DModels/Faceform/WrapBody.obj");
    // std::string filename("C:/Users/Пользователь/CLionProjects/3DModels/Faceform/WrapBody.obj");
    //std::string filename("C:/Users/Пользователь/CLionProjects/3DModels/Faceform/WrapBody.obj");

    // std::string filename("/Users/renat/CLionProjects/3DModels/Faceform/WrapHand.obj");
    //std::string filename("/Users/renat/CLionProjects/3DModels/Faceform/WrapHand.obj");

    // std::string filename("/Users/renat/CLionProjects/3DModels/CaracalCube/caracal_cube.obj");
    // std::string filename("/Users/renat/CLionProjects/3DModels/Faceform/WrapBody.obj");
    // std::string filename("/Users/renat/CLionProjects/3DModels/Faceform/WrapHead.obj");
    // std::string filename("/Users/renat/CLionProjects/3DModels/Faceform/WrapLowerTeeth.obj");
    // std::string filename("C:/Users/Пользователь/CLionProjects/3DModels/Faceform/WrapSkull.obj");
    // std::string filename("/Users/renat/CLionProjects/3DModels/Faceform/WrapSkull.obj");
    //std::string filename("/Users/renat/CLionProjects/3DModels/SimpleModelsForReaderTests/NonManifold2.obj");
    // std::string filename("/Users/renat/CLionProjects/3DModels/Faceform/WrapUpperTeeth.obj");
    // std::string filename("/Users/renat/CLionProjects/3DModels/Faceform/WrapFemaleBody.obj");
//    std::string filename( "/Users/Пользователь/CLionProjects/3DModels/CaracalCube/caracal_cube.obj"); // МОЙ КУБИК :3


/* ЭТОТ КУБИК ТОЖЕ БУДЕТ МОИМ БУГАГА*/
//	std::string filename( "/Users/Пользователь/CLionProjects/3DModels/CaracalCube/caracal_cube.obj");
//МОЖЕТ ТЫ ВСЕ ТАКИ БУДЕШЬ КОПИРОВАТЬ КУБИК, А ПОТОМ ЕГО РЕДАКТИРОВАТЬ, А НЕ ИЗМЕНЯТЬ УЖЕ СУЩЕСТВУЮЩИЙ!??!?!?!?!!?
	//std::string filename("/Users/Пользователь/CLionProjects/3DModels/CaracalCube/caracal_cube.obj");
	//std::string filename("/Users/Пользователь/CLionProjects/3DModels/SimpleModelsForReaderTests/Teapot.obj");

	//Model ans(ObjReader::read(filename));
	omp_set_dynamic(1); // Enable dynamic adjustment
    QApplication a(argc, argv);
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
