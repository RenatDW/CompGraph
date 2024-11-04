#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../render_engine/headers/Camera.h"
#include "../../model/headers/Model.h"

#include <QMainWindow>
#include <QPainter>

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
    Camera camera;
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

    void on_actionTriangulation_changed();

private:
    Ui::MainWindow *ui;
    bool triangulation = false;
};
#endif // MAINWINDOW_H
