#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "Camera.h"
#include "Model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
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
    const int TRANSLATION = 50;

private slots:
    void on_actionLoad_Model_triggered();

    void on_actionSave_Model_triggered();

    void on_actionUp_triggered();

    void on_actionDown_triggered();

    void on_actionLeft_triggered();

    void on_actionRight_triggered();

    void on_actionForward_triggered();

    void on_actionBack_triggered();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
