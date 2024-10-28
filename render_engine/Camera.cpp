//
// Created by Ренат Асланов on 23.10.2024.
//

#include "../headers/Camera.h"
#include "../headers/GraphicConveyor.h"


Camera::Camera(
    const Vector3D position,
    const Vector3D target,
    const float fov,
    const float aspectRatio,
    const float nearPlane,
    const float farPlane)
{
    this->position = position;
    this->target = target;
    this->fov = fov;
    this->aspectRatio = aspectRatio;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
};

void Camera::setPosition(const Vector3D position)
{
    this->position= position;
}
void Camera::setTarget(const Vector3D target)

{
    this->target= position;
    }

void Camera::setAspectRatio(const float aspectRatio)
{
    this->aspectRatio = aspectRatio;
};

Vector3D Camera::getPosition()
{
    return this->position;
}

Vector3D Camera::getTarget()
{
    return this->target;
}

void Camera::movePosition(const Vector3D translation)
{
    this->setPosition({position.getX() + translation.getX(),position.getY() + translation.getY(),position.getZ() + translation.getZ()});
    // this->position.setX(position.getX() + translation.getX() + 50);
    // this->position.setY(position.getY() + translation.getY());
    // this->position.setZ(position.getZ() + translation.getZ());
    // this->position = position + translation;
}

void Camera::moveTarget(const Vector3D translation)
{
    this->target = target + translation;
}

Matrix4D Camera::getViewMatrix()
{
    return GraphicConveyor::lookAt(position, target);
}

Matrix4D Camera::getProjectionMatrix()
{
return GraphicConveyor::perspective(fov, aspectRatio, nearPlane, farPlane);
};
