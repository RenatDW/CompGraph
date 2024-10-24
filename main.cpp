#include <iostream>
#include <QApplication>
#include <QPushButton>
#include "headers/Vector2D.h"
#include "headers/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // QPushButton button(nullptr);
    // button.resize(200, 100);
    // button.show();

    return a.exec();
}
