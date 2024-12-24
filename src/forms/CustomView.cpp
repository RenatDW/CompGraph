#include "CustomView.h"
#include "mainwindow.h"
#include "../render_engine/headers/GraphicConveyor.h"
#include "../math/headers/MathCast.h"

#include <QDebug>

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

		float deltaX = static_cast<float>(current_mouse_position.x() - last_mouse_position.x());
		float deltaY = static_cast<float>(current_mouse_position.y() - last_mouse_position.y());

		constexpr float ROTATION_SPEED = 0.1f;
		constexpr float EPSILON = 1e-2f;
		constexpr float DEG_TO_RAD = static_cast<float>(M_PI) / 180.0f;

		theta -= deltaX * ROTATION_SPEED;
		phi = std::clamp(phi - deltaY * ROTATION_SPEED, EPSILON, 180.0f - EPSILON);

		float theta_rad = theta * DEG_TO_RAD;
		float phi_rad = phi * DEG_TO_RAD;

		float radius = mainWindow->camera.get_position().length();

		Vector3D new_position(
				radius * std::sin(phi_rad) * std::cos(theta_rad),
				radius * std::cos(phi_rad),
				radius * std::sin(phi_rad) * std::sin(theta_rad)
		);

		mainWindow->camera.set_position(new_position);
		mainWindow->camera.set_target(Vector3D(0.0f, 0.0f, 0.0f));

		last_mouse_position = current_mouse_position;
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
	if (event->button() == Qt::LeftButton && mainWindow->vertex_id != -1)
	{
		RemoveElements::delete_vertex(mainWindow->models[mainWindow->selected_model].triangles[mainWindow->triangle_id]
			.get_vertex_indices()[mainWindow->vertex_id], mainWindow->models[mainWindow->selected_model]);
	}else if(mainWindow->triangle_id != -1){
		RemoveElements::delete_triangle(mainWindow->triangle_id, mainWindow->models[mainWindow->selected_model]);
	}

	last_mouse_position = event->pos();

	Vector3D camera_position = mainWindow->camera.get_position();
	float radius = camera_position.length();

	if (radius > 1e-5f)
	{
		constexpr float RAD_TO_DEG = 180.0f / static_cast<float>(M_PI);
		theta = std::atan2(camera_position.getZ(), camera_position.getX()) * RAD_TO_DEG;
		phi = std::acos(camera_position.getY() / radius) * RAD_TO_DEG;
	}

}

void CustomView::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPointF scenePos = mapToScene(event->pos());
		//qDebug() << "Mouse Release at:" << scenePos;
	}
}
