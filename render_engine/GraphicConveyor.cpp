#include "../headers/GraphicConveyor.h"
#include "../headers/Vector3D.h"
#include <cmath>

Matrix4D GraphicConveyor::lookAt(Vector3D eye, Vector3D target)
{
    return lookAt(eye, target,  Vector3D(0, 1.0F, 0)); // здесь у каждой переменной был F
}
Matrix4D GraphicConveyor::lookAt(Vector3D eye, Vector3D target, Vector3D up)
{
    Vector3D resultX = Vector3D();
    Vector3D resultY = Vector3D();
    Vector3D resultZ = Vector3D();

    resultZ = target - eye;
    resultX = Vector3D::cross(up, resultZ);
    resultY = Vector3D::cross(resultZ, resultX);

    resultX = resultX.normalize();
    resultY = resultY.normalize();
    resultZ = resultZ.normalize();

    std::vector<std::vector<float>> matrix = {
        {resultX.getX(), resultY.getX(), resultZ.getX(), 0},
        {resultX.getY(), resultY.getY(), resultZ.getY(), 0},
        {resultX.getZ(), resultY.getZ(), resultZ.getZ(), 0},
        {-(resultX * eye), -(resultY * eye), -(resultZ * eye), 1}
    };
    return Matrix4D(matrix);
}

Matrix4D GraphicConveyor::perspective(const float fov, const float aspectRatio, const float nearPlane, const float farPlane)
{
    Matrix4D result;
    float tangentMinusOnDegree = (float) (1.0F / (tan(fov * 0.5F)));
    result.set(0, 0, tangentMinusOnDegree / aspectRatio);
    result.set(1, 1, tangentMinusOnDegree);
    result.set(2, 2, (farPlane + nearPlane) / (farPlane - nearPlane));
    result.set(2, 3, 1.0F);
    result.set(3, 2, 2 * (nearPlane * farPlane) / (nearPlane - farPlane));
    return result;
}

