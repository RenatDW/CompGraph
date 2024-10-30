#include "../headers/mainwindow.h"
#include "../ui_MainWindow.h"
#include "../headers/RenderEngine.h"

#include <QMessageBox>
#include <QPainter>
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      camera(Vector3D(0, 0, 100), Vector3D(0, 0, 0),
             1.0f, 1, 0.01f, 100),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QMainWindow::paintEvent(event);

    QPainter painter(this); // Создаем объект QPainter

    camera.setAspectRatio((float) (this->width()) / (float) (this->height()));

    // Здесь можно использовать painter для рисования на окне
    for (const Model &model: models) {
        // Используйте ссылку на модель
        RenderEngine::render(painter, camera, model, this->width(), this->height(), triangulation);
        // Передаем painter по ссылке
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
    camera.movePosition(Vector3D(0, (float) TRANSLATION, 0));
    repaint();
}

void MainWindow::on_actionDown_triggered()
{
    camera.movePosition(Vector3D(0, (float) -TRANSLATION, 0));
    repaint();
}

void MainWindow::on_actionLeft_triggered()
{
    camera.movePosition(Vector3D((float) TRANSLATION, 0, 0));
    repaint();
}

void MainWindow::on_actionRight_triggered()
{
    camera.movePosition(Vector3D((float) -TRANSLATION, 0, 0));
    repaint();
}

void MainWindow::on_actionForward_triggered()
{
    camera.movePosition(Vector3D(0, 0, (float) -TRANSLATION));
    repaint();
}

void MainWindow::on_actionBack_triggered()
{
    camera.movePosition(Vector3D(0, 0, (float) TRANSLATION));
    repaint();
}

void MainWindow::on_actionTriangulation_changed()
{
    triangulation = !triangulation;
    repaint();
}
