//
// Created by Ренат Асланов on 23.10.2024.
//

#ifndef CAMERS_H
#define CAMERS_H

#include "math.Vector3D.h" // Include the Vector3D class header
#include "math/Matrix4D.h" // Assuming you have a Matrix4f class

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


};



#endif //CAMERS_H
