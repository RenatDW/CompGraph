#include <QApplication>
#include <QPushButton>
#include "headers/Vector2D.h"

int main(int argc, char *argv[]) {
    Vector2D* ar = new Vector2D(1, 2);


    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
