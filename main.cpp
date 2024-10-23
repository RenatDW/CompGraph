#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "headers/Vector2D.h"

int main(int argc, char *argv[]) {
    Vector2D ar = Vector2D(1,2);
    Vector2D ar2;
    ar2.setX(0);
    ar2.setY(0);
    std::cout << ar.getX() << " " << ar2.getY() << std::endl;


    QApplication a(argc, argv);
    QPushButton button(nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
