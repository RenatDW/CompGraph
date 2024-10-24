#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "headers/Vector2D.h"
#include "headers/mainwindow.h"
#include "headers/ObjReader.h"

int main(int argc, char *argv[]) {
    std::string filename("/Users/renat/IdeaProjects/CompGraphProject/3DModels/Faceform/WrapFemaleBodyPreview.png");
    Model ans(ObjReader::read(filename));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // QPushButton button(nullptr);
    // button.resize(200, 100);
    // button.show();

    return a.exec();
}
