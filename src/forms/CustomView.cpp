#include "CustomView.h"
#include "mainwindow.h"

#include <QDebug>

CustomView::CustomView(QWidget* parent) : QGraphicsView(parent)
{
	setMouseTracking(true);
}

void CustomView::wheelEvent(QWheelEvent* event)
{
	int delta = event->angleDelta().y();
	const float zoom_speed = 0.1f;
	mainWindow->camera.move_position(Vector3D(0, 0, static_cast<float>(delta) * zoom_speed * (-1)));

//	std::string ans = "{" + std::to_string(mainWindow->camera.get_position().getX()) + ", " + std::to_string(camera.get_position().getY()) + ", " + std::to_string(
//			mainWindow->camera.get_position().getZ()) + "}";
//	ui->listWidget_2->item(selected_camera_list_id)->setText(QString::fromStdString(ans));
//	QVariant cord;
//	std::array<float, 4> coord { camera.get_position().getX(), camera.get_position().getY(), camera.get_position().getZ(), static_cast<float>(selected_camera_model_id)};
//	cord.setValue(coord);
//	ui->listWidget_2->item(selected_camera_list_id)->setData(Qt::UserRole, cord);

	mainWindow->update_scene();
}

void CustomView::set_main_window_pointer(MainWindow* t_mainWindow)
{
	this->mainWindow = t_mainWindow;
}

void CustomView::mouseMoveEvent(QMouseEvent* event)
{
	QPointF scenePos = mapToScene(event->pos());
	//qDebug() << "Mouse move at:" << scenePos;

	mainWindow->update_scene();
}

void CustomView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPointF scenePos = mapToScene(event->pos());
		qDebug() << "Mouse PRESS at:" << scenePos;
	}

	mainWindow->update_scene();
}

void CustomView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPointF scenePos = mapToScene(event->pos());
		qDebug() << "Mouse Release at:" << scenePos;
	}
}
