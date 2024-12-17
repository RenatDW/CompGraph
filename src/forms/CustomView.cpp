#include "CustomView.h"
#include "mainwindow.h"
#include "../render_engine/headers/GraphicConveyor.h"
#include "../math/headers/MathCast.h"

#include <QDebug>

QPoint CustomView::last_mouse_position;

CustomView::CustomView(QWidget* parent) : QGraphicsView(parent)
{
	setMouseTracking(true);
}

void CustomView::set_main_window_pointer(MainWindow* t_mainWindow)
{
	this->mainWindow = t_mainWindow;
}

void CustomView::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		QPoint current_mouse_position = event->pos();

		auto deltaX = static_cast<float>(current_mouse_position.x() - last_mouse_position.x());
		auto deltaY = static_cast<float>(current_mouse_position.y() - last_mouse_position.y());

		static float theta = 0.0f;
		static float phi = 90.0f;
		const float RADIUS = this->mainWindow->camera.get_position().length();

		theta -= deltaX * 0.01f;
		phi -= deltaY * 0.01f;

		const float EPSILON = 1e-2f;
		phi = std::clamp(phi, EPSILON, 180.0f - EPSILON);

		float theta_rad = theta * static_cast<float>(M_PI) / 180.0f;
		float phi_rad = phi * static_cast<float>(M_PI) / 180.0f;

		Vector3D new_position;
		new_position.setX(RADIUS * std::sin(phi_rad) * std::cos(theta_rad));
		new_position.setY(RADIUS * std::cos(phi_rad));
		new_position.setZ(RADIUS * std::sin(phi_rad) * std::sin(theta_rad));

		mainWindow->camera.set_position(new_position);
		mainWindow->camera.set_target(Vector3D(0.0f, 0.0f, 0.0f));
	}
	else
	{
		last_mouse_position = event->pos();
	}
}

void CustomView::wheelEvent(QWheelEvent* event)
{
	int delta = event->angleDelta().y();
	const float zoom_speed = 0.1f;

	Vector3D camera_position = mainWindow->camera.get_position();
	float radius = camera_position.length();

	radius -= static_cast<float>(delta) * zoom_speed;
	radius = std::max(1.0f, radius);

	float theta = std::atan2(camera_position.getY(), camera_position.getX());
	float phi = std::acos(camera_position.getZ() / camera_position.length());

	float newX = radius * std::sin(phi) * std::cos(theta);
	float newY = radius * std::sin(phi) * std::sin(theta);
	float newZ = radius * std::cos(phi);

	mainWindow->camera.set_position(Vector3D(newX, newY, newZ));
	mainWindow->camera.set_target(Vector3D(0, 0, 0));
//	std::string ans = "{" + std::to_string(mainWindow->camera.get_position().getX()) + ", " + std::to_string(camera.get_position().getY()) + ", " + std::to_string(
//	mainWindow->camera.get_position().getZ()) + "}";
//	ui->listWidget_2->item(selected_camera_list_id)->setText(QString::fromStdString(ans));
//	QVariant cord;
//	std::array<float, 4> coord { camera.get_position().getX(), camera.get_position().getY(), camera.get_position().getZ(), static_cast<float>(selected_camera_model_id)};
//	cord.setValue(coord);
//	ui->listWidget_2->item(selected_camera_list_id)->setData(Qt::UserRole, cord);

	mainWindow->update_scene();
}


void CustomView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPointF scenePos = mapToScene(event->pos());
		//qDebug() << "Mouse PRESS at:" << scenePos;
	}

	mainWindow->update_scene();
}

void CustomView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPointF scenePos = mapToScene(event->pos());
		//qDebug() << "Mouse Release at:" << scenePos;
	}
}
