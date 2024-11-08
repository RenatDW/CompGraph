#include "../headers/Point2D.h"
#include "../headers/Point3D.h"
#include "../headers/Vector3D.h"
#include "../headers/Vector4D.h"
#include "../headers/Matrix3D.h"
#include "../headers/Matrix4D.h"
#include "../headers/MathCast.h"

Point2D MathCast::to_Point2D(const Vector3D& vertex, const int width, const int height)
{
    return{vertex.getX() * static_cast<float>(width) + static_cast<float>(width) / 2.0f,
        -vertex.getY() * static_cast<float>(height) + static_cast<float>(height) / 2.0f};
}

Point3D MathCast::to_Point3D(const Vector3D& vertex, const int width, const int height)
{
    return {vertex.getX() * static_cast<float>(width) + static_cast<float>(width) / 2.0f,
        -vertex.getY() * static_cast<float>(height) + static_cast<float>(height) / 2.0f,
        vertex.getZ()};
}

Vector3D MathCast::to_Vector3D(const Point3D& point)
{
    return {point.getX(), point.getY(), point.getZ()};
}

Vector3D MathCast::to_Vector3D(const Vector4D& v)
{
    return {v.getX() / v.getW(), v.getY() / v.getW(), v.getZ() / v.getW()};
}

Vector4D MathCast::to_Vector4D(const Vector3D& v)
{
    return {v.getX(), v.getY(), v.getZ(), 1};
}