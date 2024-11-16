#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../render_engine/headers/Camera.h"
#include "../../model/headers/Model.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;

    ~MainWindow();

    std::vector<Model> models;
    std::string model_texture_path;
    QColor fill_model_color;
    Camera camera;
    bool show_mesh = false;
    bool show_texture = false;
    bool show_illumination = false;
    const int TRANSLATION = 5;

private slots:
    void on_actionLoad_Model_triggered();

    void on_actionSave_Model_triggered();

    void on_actionUp_triggered();

    void on_actionDown_triggered();

    void on_actionLeft_triggered();

    void on_actionRight_triggered();

    void on_actionForward_triggered();

    void on_actionBack_triggered();

    void on_actionLoad_Texture_triggered();

    void on_actionChose_Color_triggered();

    void on_actionTriangulation_changed();

    void on_checkBox_show_mesh_toggled(bool checked);

    void on_checkBox_show_texture_toggled(bool checked);

    void on_checkBox_show_illumination_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    bool triangulation = true;
};
#endif // MAINWINDOW_H
