#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../render_engine/headers/Camera.h"
#include "../model/headers/Model.h"
#include "../render_engine/headers/Material.h"

#include <QElapsedTimer>
#include <QTimer>
#include <QMainWindow>
#include <QGraphicsScene>
#include <memory>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QListWidgetItem>

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

    //void paintEvent(QPaintEvent *event) override;

	void update_scene();

    ~MainWindow();
	std::map<int, Model> models;
	std::map<int, Material> materials;
    std::string model_texture_path{};
    QColor fill_model_color;
    Camera camera;
    bool show_mesh = false;
    bool show_texture = false;
    bool show_illumination = false;
    const int TRANSLATION = 5;
	int selected_model;

private slots:
    void on_actionLoad_Model_triggered();
    void on_actionSave_Model_triggered();
    void on_actionUp_triggered();
    void on_actionDown_triggered();
    void on_actionLeft_triggered();
    void on_actionRight_triggered();
    void on_actionLoad_Texture_triggered();
    void on_actionChose_Color_triggered();
    void on_actionTriangulation_changed();
    void on_actionRotate_Scale_Translate_triggered();
    void on_checkBox_show_mesh_toggled(bool checked);
    void on_checkBox_show_texture_toggled(bool checked);
    void on_checkBox_show_illumination_toggled(bool checked);
	void on_pushButton_2_clicked();
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
	void onListClicked();
	void slotCustomMenuRequested(QPoint pos);
	void slotEditRecord();
	void slotRemoveRecord();
	void slotRotateRecord();

	void wheelEvent(QWheelEvent* event) override;

private:
	QTimer frameTimer;         // Timer for frame updates
	QElapsedTimer fpsTimer;    // Timer to measure frame duration
	int frameCount;            // Count frames for FPS calculation
	float fps;
	Ui::MainWindow* ui;
    bool triangulation = true;
	std::unique_ptr<QGraphicsScene> scene;
	int model_cnt = 0;
	int selected_camera_model_id = model_cnt;
	int selected_camera_list_id = model_cnt;
	void add_camera_to_list(QString x, QString y, QString z, QDialog* dialog1);
	void add_camera_to_list(QString t_x, QString t_y, QString t_z);
	void add_model(Model& md);
	void onFrameUpdate();
};

#endif
