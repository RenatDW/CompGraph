#include "../headers/GraphicConveyor.h"
#include "../../math/headers/Vector3D.h"
#include "../../math/headers/Matrix4D.h"
#include "../../math/headers/Matrix3D.h"
#include "../../math/headers/Vector4D.h"
#include <iostream>
#include <cmath>

void GraphicConveyor::scale(Model& mesh, const float sx, const float sy, const float sz)
{
    Matrix3D matrix;
    matrix.set(0, 0, sx);
    matrix.set(1, 1, sy);
    matrix.set(2, 2, sz);

    for (auto& vertex : mesh.vertices)
    {
        vertex = matrix * vertex;
    }
}


Matrix4D GraphicConveyor::look_at(const Vector3D &eye,const Vector3D &target)
{
    return look_at(eye, target, Vector3D(0, 1.0f, 0)); // здесь у каждой переменной был F
}

Matrix4D GraphicConveyor::look_at(const Vector3D &eye, const Vector3D &target, const Vector3D &up)
{
    Vector3D resultX = Vector3D();
    Vector3D resultY = Vector3D();
    Vector3D resultZ = Vector3D();

    resultZ = (target - eye).normalize();

    //TODO это типо фикс только если смотреть перемещать по оY модель разворачивает во все стороны
    Vector3D adjustedUp = up;
    if (std::abs(resultZ * up) > 0.99f) {
        // Если вектор up слишком близок по направлению к resultZ, используем другой вектор для up
        adjustedUp = (resultZ.getX() ==  0.0f) ? Vector3D(0, 0, 1): Vector3D(1, 0, 0);
    }
    resultX = Vector3D::cross(adjustedUp, resultZ).normalize();
    resultY = Vector3D::cross(resultZ, resultX).normalize();


    std::vector<std::vector<float> > matrix = {
        {resultX.getX(), resultY.getX(), resultZ.getX(), 0},
        {resultX.getY(), resultY.getY(), resultZ.getY(), 0},
        {resultX.getZ(), resultY.getZ(), resultZ.getZ(), 0},
        {-(resultX * eye), -(resultY * eye), -(resultZ * eye), 1}
    };
    return Matrix4D(matrix);
}

Matrix4D GraphicConveyor::perspective(const float &fov, const float &aspect_ratio, const float &near_plane,
                                      const float &far_plane)
{
    Matrix4D result;
    const auto tangent_minus_on_degree = (1.0f / (std::tan(fov * 0.5f)));
    result.set(0, 0, tangent_minus_on_degree / aspect_ratio);
    result.set(1, 1, tangent_minus_on_degree);
    result.set(2, 2, (far_plane + near_plane) / (far_plane - near_plane));
    result.set(2, 3, 1.0f);
    result.set(3, 2, 2 * (near_plane * far_plane) / (near_plane - far_plane));
    return result;
}
