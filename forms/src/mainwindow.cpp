#include "../headers/mainwindow.h"
#include "../ui_MainWindow.h"
#include "../../render_engine/headers/RenderEngine.h"
#include "../../math/headers/Vector3D.h"
#include "../../objreader/headers/ObjReader.h"
#include "../../objwriter/headers/ObjWriter.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>

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
    std::string file_name = QFileDialog::getOpenFileName(this,
                                                         tr("Open Object"), ":/",
                                                         tr("Object Files (*.obj)")).toStdString();
    //TODO Переделать когда нужно будет делать сценку
    if(models.size() ==1) {
        models[0] =(ObjReader::read(file_name));

    }else {
        models.emplace_back(ObjReader::read(file_name));

    }
}

void MainWindow::on_actionSave_Model_triggered()
{
    if(models.empty()) {
        QMessageBox::information(this, "Save model", "You haven't selected a model");
        return;
    }
    std::string file_name = QFileDialog::getSaveFileName(this, tr("Save Object"),
                                                         ":/",
                                                         tr("Objects (*.obj)")).toStdString();
    ObjWriter writer(file_name);
    writer.write(models[0]);
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
