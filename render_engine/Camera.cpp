//
// Created by Ренат Асланов on 23.10.2024.
//

#include "../headers/Camera.h"

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

