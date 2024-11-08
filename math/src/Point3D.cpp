#include "../headers/Point3D.h"
#include "../headers/Vector3D.h"

#include <cmath>

Point3D::Point3D() : x(0.0f), y(0.0f), z(0.0f) {}

Point3D::Point3D(const float x, const float y, const float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Point3D::getX() const
{
    return x;
}

float Point3D::getY() const
{
    return y;
}

float Point3D::getZ() const
{
    return z;
}

void Point3D::setX(const float x)
{
    this->x = x;
}

void Point3D::setY(const float y)
{
    this->y = y;
}

void Point3D::setZ(const float z)
{
    this->z = z;
}

void Point3D::set(const float x, const float y, const float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point3D Point3D::operator * (const float a) const
{
    return {this->x * a, this->y * a, this->z * a};
}

float Point3D::operator * (const Point3D& cam) const
{
    return this->x * cam.getX() + this->y * cam.getY() + this->z * cam.getZ();
}

Point3D Point3D::operator + (const Point3D &v2) const
{
    return {this->x + v2.x, this->y + v2.y, this->z + v2.z};
}

Point3D Point3D::normalize() const
{
    const float len = std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return  {this->x / len, this->y / len, this->z / len};
}

Point3D Point3D::operator - (const Point3D &point_3d) const
{
    return {this->x - point_3d.x, this->y - point_3d.y, this->z - point_3d.z};
}
