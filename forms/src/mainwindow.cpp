#include "../headers/mainwindow.h"
#include "../ui_MainWindow.h"
#include "../../render_engine/headers/RenderEngine.h"
#include "../../math/headers/Vector3D.h"
#include "../../objreader/headers/ObjReader.h"
#include "../../objwriter/headers/ObjWriter.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QPainter>

#include "../../render_engine/headers/GraphicConveyor.h"

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

    camera.setAspectRatio(static_cast<float>(this->width()) / static_cast<float>(this->height()));
    int width = this->width();
    int height = this->height();
    std::vector<TypeOfRender> render_types;
    // render_types.emplace_back(TypeOfRender::mesh);
    render_types.emplace_back(TypeOfRender::normal_vectors);
    render_types.emplace_back(TypeOfRender::texture);


    for (Model &model: models) {
        QColor basic_color = QColor(255,255,255);
        //При цвете 0,0,0 все ломается
        RenderEngine renderEngine(painter, camera, model_texture_path, basic_color, model,width,
                                  height);
        renderEngine.render(render_types);
        //Добавить варианты отрисовки
        // RenderEngine::render(painter, camera, model_texture_path, fill_model_color, model, this->width(), this->height(), triangulation);
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
    if (models.size() == 1) {
        models[0] = (ObjReader::read(file_name));
    } else {
        models.emplace_back(ObjReader::read(file_name));
    }
}

void MainWindow::on_actionSave_Model_triggered()
{
    if (models.empty()) {
        QMessageBox::information(this, "Save model", "You haven't selected a model");
        return;
    }
    std::string file_name = QFileDialog::getSaveFileName(this, tr("Save Object"),
                                                         ":/",
                                                         tr("Objects (*.obj)")).toStdString();
    ObjWriter::write(models[0], file_name);
}

void MainWindow::on_actionUp_triggered()
{
    camera.movePosition(Vector3D(0, static_cast<float>(TRANSLATION), 0));
    repaint();
}

void MainWindow::on_actionDown_triggered()
{
    camera.movePosition(Vector3D(0, static_cast<float>(-TRANSLATION), 0));
    repaint();
}

void MainWindow::on_actionLeft_triggered()
{
    camera.movePosition(Vector3D(static_cast<float>(TRANSLATION), 0, 0));
    repaint();
}

void MainWindow::on_actionRight_triggered()
{
    camera.movePosition(Vector3D(static_cast<float>(-TRANSLATION), 0, 0));
    repaint();
}

void MainWindow::on_actionForward_triggered()
{
    camera.movePosition(Vector3D(0, 0, static_cast<float>(-TRANSLATION)));
    repaint();
}

void MainWindow::on_actionBack_triggered()
{
    camera.movePosition(Vector3D(0, 0, static_cast<float>(TRANSLATION)));
    repaint();
}
void MainWindow::on_actionLoad_Texture_triggered()
{
    std::string file_name = QFileDialog::getOpenFileName(this,
                                                         tr("Open Texture"), ":/",
                                                         tr("Object Image (*.png *.jpg *.bmp)")).toStdString();
       //TODO Переделать когда нужно будет делать сценку
    model_texture_path = file_name;


}
void MainWindow::on_actionChose_Color_triggered()
{
    QColor color = QColorDialog::getColor(QColor(255,100,200,255));
    fill_model_color = color;
    repaint();
    // if (!color.isValid()) {
        // Cancel
    // }
    // QMessageBox::information(this, "Choose Color", "Cooming soon...");

}

void MainWindow::on_actionTriangulation_changed()
{
    triangulation = !triangulation;
    repaint();
}


void MainWindow::on_actionScale_triggered()
{
    GraphicConveyor::scale(models[0], 1, 1, 10);

    repaint();
}

void MainWindow::on_actionRotate_triggered()
{
    GraphicConveyor::rotate(models[0], 2, 1, 1);

    repaint();
}

void MainWindow::on_actionTranslate_triggered()
{
    GraphicConveyor::translate(models[0], 10, 10, 10);

    repaint();
}