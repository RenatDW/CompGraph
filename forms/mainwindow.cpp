//
// Created by Ренат Асланов on 24.10.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "../headers/mainwindow.h"
#include "../ui_MainWindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
