#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../render_engine/headers/Camera.h"
#include "../model/headers/Model.h"
#include "../render_engine/headers/Material.h"
#include <QElapsedTimer>
#include <QTimer>
#include <QMainWindow>

#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsScene>
#include <memory>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QListWidgetItem>

static const int VERTEX_RADIUS = 10;

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
    explicit MainWindow(QWidget *parent = nullptr);

	void update_scene();

    ~MainWindow() override;

	std::map<int, Model> models;
	std::map<int, Material> materials;
    std::string model_texture_path{};
    Camera camera;
    bool show_mesh = false;
    bool show_texture = false;
    bool show_illumination = false;
	int selected_model;
	int triangle_id = -1;
	int vertex_id = -1;

private slots:
    void on_actionLoad_Model_triggered();
    void on_actionSave_Model_triggered();
    void on_actionLoad_Texture_triggered();

private slots:
    void on_checkBox_show_mesh_toggled(bool checked);
    void on_checkBox_show_texture_toggled(bool checked);
    void on_checkBox_show_illumination_toggled(bool checked);

private slots:
	void on_addCamera_clicked();
	void on_useCamera_clicked();
	void on_deleteCamera_clicked();

private slots:

	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();

	void on_rotate_clicked();
	void on_scale_clicked();
	void on_translate_clicked();

	void onListClicked();

	void slotCustomMenuRequested(QPoint pos);
	void slotEditRecord();
	void slotRemoveRecord();
	void slotRotateRecord();

private:
	Ui::MainWindow* ui;
	std::unique_ptr<QGraphicsScene> scene;

private:
	int model_cnt = 0;
	int selected_camera_model_id = 0;
	int selected_camera_list_id = 0;

private:
	void add_camera_to_list(float x, float y, float z);
	void add_camera_to_list(QString t_x, QString t_y, QString t_z);
	void add_model(Model& md);

private:
	QTimer frameTimer;
	QElapsedTimer fpsTimer;
	int frameCount;
	float fps;
	void onFrameUpdate();
};

#endif
