#ifndef CAMERS_H
#define CAMERS_H

#include "Vector3D.h"
#include "../headers/Matrix4D.h"

class Camera
{
public:
    void setPosition(const Vector3D &position);

    void setTarget(const Vector3D &target);

    void setAspectRatio(const float &aspectRatio);

    Vector3D getPosition();

    Vector3D getTarget();

    void movePosition(const Vector3D &translation);

    void moveTarget(const Vector3D &translation);

    Matrix4D getViewMatrix();

    Matrix4D getProjectionMatrix() const;

    Camera(const Vector3D &position,
           const Vector3D &target,
           float fov,
           float aspectRatio,
           float nearPlane,
           float farPlane);

private:
    Vector3D position;
    Vector3D target;
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
};

#endif