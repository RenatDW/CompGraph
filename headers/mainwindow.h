#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

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

private slots:
    void on_actionLoad_Model_triggered();

    void on_actionSave_Model_triggered();

private:

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
