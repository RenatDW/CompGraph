#include "../headers/Camera.h"
#include "../headers/GraphicConveyor.h"

Camera::Camera(
    const Vector3D &position,
    const Vector3D &target,
    float fov,
    float aspectRatio,
    float nearPlane,
    float farPlane)
{
    this->position = position;
    this->target = target;
    this->fov = fov;
    this->aspectRatio = aspectRatio;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
};

void Camera::set_position(const Vector3D &position)
{
    this->position = position;
}

void Camera::set_target(const Vector3D &target)

{
    this->target = position;
}

void Camera::set_aspect_ratio(const float &aspectRatio)
{
    this->aspectRatio = aspectRatio;
};

Vector3D Camera::get_position()
{
    return this->position;
}

Vector3D Camera::get_target()
{
    return this->target;
}

void Camera::move_position(const Vector3D &translation)
{
	this->set_position({
			position.getX() + translation.getX(), position.getY() + translation.getY(),
			position.getZ() + translation.getZ()
	});
}

void Camera::move_target(const Vector3D &translation)
{
    this->target = target + translation;
}

Matrix4D Camera::get_view_matrix()
{
    return GraphicConveyor::look_at(position, target);
}

Matrix4D Camera::get_projection_matrix() const
{
    return GraphicConveyor::perspective(fov, aspectRatio, nearPlane, farPlane);
};

