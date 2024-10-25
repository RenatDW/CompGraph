#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "headers/Vector2D.h"
#include "headers/mainwindow.h"
#include "headers/ObjReader.h"

int main(int argc, char *argv[]) {

    // std::string filename("/Users/renat/IdeaProjects/CompGraphProject/3DModels/Faceform/WrapBody.obj");
    // std::string filename("/Users/renat/IdeaProjects/CompGraphProject/3DModels/Faceform/WrapHand.obj");
    // std::string filename("/Users/renat/IdeaProjects/CompGraphProject/3DModels/Faceform/WrapHead.obj");
    // std::string filename("/Users/renat/IdeaProjects/CompGraphProject/3DModels/Faceform/WrapLowerTeeth.obj");
    // std::string filename("/Users/renat/IdeaProjects/CompGraphProject/3DModels/Faceform/WrapSkull.obj");
    // std::string filename("/Users/renat/IdeaProjects/CompGraphProject/3DModels/Faceform/WrapUpperTeeth.obj");
    // std::string filename("/Users/renat/IdeaProjects/CompGraphProject/3DModels/Faceform/WrapFemaleBody.obj");
    std::string filename("/Users/renat/IdeaProjects/CompGraphProject/3DModels/CaracalCube/caracal_cube.obj");
    Model ans(ObjReader::read(filename));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // QPushButton button(nullptr);
    // button.resize(200, 100);
    // button.resize(200, 100);∂
    // button.show();

    return a.exec();
}
