//
// Created by Ренат Асланов on 24.10.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "../headers/mainwindow.h"

#include <iostream>

#include "../ui_MainWindow.h"
#include "../headers/RenderEngine.h"
#include <QMessageBox>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
camera(Vector3D(0, 0, 100),Vector3D(0, 0, 0),
    1.0F, 1, 0.01F, 100),
ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QMainWindow::paintEvent(event);

    QPainter painter(this); // Создаем объект QPainter

    // Здесь можно использовать painter для рисования на окне
    for(const Model &model : models) { // Используйте ссылку на модель
        RenderEngine::render(painter, camera, model,this->width(), this->height(), 0); // Передаем painter по ссылке
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_Model_triggered()
{
    QMessageBox::information(this, "Load model", "Coming soon...");
}

void MainWindow::on_actionSave_Model_triggered()
{
    QMessageBox::information(this, "Save", "Coming soon...");
}


void MainWindow::on_actionUp_triggered()
{
    camera.movePosition(Vector3D(0, TRANSLATION, 0));
    repaint();
}

void MainWindow::on_actionDown_triggered()
{
    camera.movePosition(Vector3D(0, -TRANSLATION, 0));
    repaint();

}
void MainWindow::on_actionLeft_triggered()
{
    camera.movePosition(Vector3D(TRANSLATION, 0, 0));
    repaint();

}
void MainWindow::on_actionRight_triggered()
{
    camera.movePosition(Vector3D(-TRANSLATION, 0, 0));
    repaint();

}
void MainWindow::on_actionForward_triggered()
{
    camera.movePosition(Vector3D(0, 0, -TRANSLATION));
    repaint();

}
void MainWindow::on_actionBack_triggered()
{
    camera.movePosition(Vector3D(0, 0, TRANSLATION));
    repaint();

}
