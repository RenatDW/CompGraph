//
// Created by Ренат Асланов on 23.10.2024.
//

#include "../headers/GraphicConveyor.h"
#include "../headers/Vector3D.h"
#include <cmath>

Matrix4D GraphicConveyor::rotateScaleTranslate()
{
    // float matrix[4][4] = {
    //     {1, 0, 0, 0},
    //     {0, 1, 0, 0},
    //     {0, 0, 1, 0},
    //     {0, 0, 0, 1}};
    // return Matrix4D(matrix);
}
Matrix4D GraphicConveyor::lookAt(Vector3D eye, Vector3D target)
{
    return lookAt(eye, target,  Vector3D(0, 1.0F, 0)); // здесь у каждой переменной был F
}
Matrix4D GraphicConveyor::lookAt(Vector3D eye, Vector3D target, Vector3D up)
{
    Vector3D resultX = Vector3D();
    Vector3D resultY = Vector3D();
    Vector3D resultZ = Vector3D();

    // resultZ.sub(target, eye);
    // resultX.cross(up, resultZ);
    // resultY.cross(resultZ, resultX);
    //
    // resultX.normalize();
    // resultY.normalize();
    // resultZ.normalize();

    // float matrix[] = {
    //     resultX.getX(), resultY.getX(), resultZ.getX(), 0,
    //     resultX.getY(), resultY.getY(), resultZ.getY(), 0,
    //     resultX.getZ(), resultY.getZ(), resultZ.getZ(), 0,
    //     -resultX.dot(eye), -resultY.dot(eye), -resultZ.dot(eye), 1};
    // return Matrix4D(matrix);
}

Matrix4D GraphicConveyor::perspective(const float fov, const float aspectRatio, const float nearPlane, const float farPlane)
{
    Matrix4D result = Matrix4D();
    float tangentMinusOnDegree = (float) (1.0F / (tan(fov * 0.5F)));
    result.set(0,0,tangentMinusOnDegree / aspectRatio);
    result.set(1,1, tangentMinusOnDegree);
    result.set(2,2, (farPlane + nearPlane) / (farPlane - nearPlane));
    result.set(2,3, 1.0F);
    result.set(3,2, 2 * (nearPlane * farPlane) / (nearPlane - farPlane));
    return result;
}

Vector3D GraphicConveyor::multiplyMatrix4ByVector3(const Matrix4D matrix, const Vector3D vertex)
{
    const float x = (vertex.getX() * matrix.get(0,0) + (vertex.getY() * matrix.get(1,0)) + (vertex.getZ() * matrix.get(2,0)) + matrix.get(3,0));
    const float y = (vertex.getX() * matrix.get(0,1) ) + (vertex.getY()  * matrix.get(1,1) ) + (vertex.getZ() * matrix.get(2,1) ) + matrix.get(3,1) ;
    const float z = (vertex.getX() * matrix.get(0,2) ) + (vertex.getY()  * matrix.get(1,2) ) + (vertex.getZ() * matrix.get(2,2) ) + matrix.get(3,2) ;
    const float w = (vertex.getX() * matrix.get(0,3) ) + (vertex.getY() * matrix.get(1,3) ) + (vertex.getZ() * matrix.get(2,2) ) + matrix.get(3,3) ;
    return Vector3D(x / w, y / w, z / w);
}
