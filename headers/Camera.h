//
// Created by Ренат Асланов on 23.10.2024.
//

#ifndef CAMERS_H
#define CAMERS_H

#include "math/Vector2D.h" // Include the Vector3D class header
#include "Vector3D.h" // Include the Vector3D class header
#include "Matrix4D.h" // Assuming you have a Matrix4f class

class Camera
{
    public:

    void setPosition(const Vector2D::Vector2D position);

    void setTarget(const Vector3D target);

    void setAspectRatio(const float aspectRatio);

    Vector3D getPosition();

    Vector3D getTarget();

    void movePosition(const Vector3D translation);

    void moveTarget(const Vector3D translation);

    Matrix4D getViewMatrix();

    Matrix4D getProjectionMatrix();

    Camera(const Vector3D position,
            const Vector3D target,
            const float fov,
            const float aspectRatio,
            const float nearPlane,
            const float farPlane);
    private:
    Vector3D position;
    Vector3D target;
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;

};



#endif //CAMERS_H
