#include "../headers/GraphicConveyor.h"
#include "../headers/Vector3D.h"

Matrix4D GraphicConveyor::look_at(const Vector3D &eye, const Vector3D &target)
{
    return look_at(eye, target, Vector3D(0, 1.0F, 0)); // здесь у каждой переменной был F
}

Matrix4D GraphicConveyor::look_at(const Vector3D &eye, const Vector3D &target, const Vector3D &up)
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
    const auto tangent_minus_on_degree = (1.0F / (std::tan(fov * 0.5F)));
    result.set(0, 0, tangent_minus_on_degree / aspect_ratio);
    result.set(1, 1, tangent_minus_on_degree);
    result.set(2, 2, (far_plane + near_plane) / (far_plane - near_plane));
    result.set(2, 3, 1.0F);
    result.set(3, 2, 2 * (near_plane * far_plane) / (near_plane - far_plane));
    return result;
}
