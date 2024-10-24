//
// Created by Ренат Асланов on 23.10.2024.
//

#ifndef GRAPHICCONVEYOR_H
#define GRAPHICCONVEYOR_H

#include "Vector3D.h"
#include "Matrix4D.h"

class GraphicConveyor
{
    public:
    static Matrix4D rotateScaleTranslate();

    static Matrix4D lookAt(Vector3D eye, Vector3D target);

    static Matrix4D lookAt(Vector3D eye, Vector3D target, Vector3D up);

    static Matrix4D perspective(const float fov,
            const float aspectRatio,
            const float nearPlane,
            const float farPlane);

    static Vector3D multiplyMatrix4ByVector3(const Matrix4D matrix, const Vector3D vertex);

    // static Point2D vertexToPoint(const Vector3D vertex, const int width, const int height);
};

#endif //GRAPHICCONVEYOR_H