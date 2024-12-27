#include "../headers/Point3D.h"
#include "../headers/Vector3D.h"

#include <cmath>

Point3D::Point3D() : x(0.0f), y(0.0f), z(0.0f) {}
Point3D::Point3D(const Vector3D &a): x(a.getX()), y(a.getY()), z(a.getZ()){}

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

float Point3D::operator * (const Point3D& point) const
{
    return this->x * point.getX() + this->y * point.getY() + this->z * point.getZ();
}

Point3D Point3D::operator + (const Point3D& point) const
{
    return {this->x + point.x, this->y + point.y, this->z + point.z};
}

Point3D Point3D::normalize() const
{

    const float len = 1/std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return  {this->x * len, this->y * len, this->z * len};
}

Point3D Point3D::operator - (const Point3D& point) const
{
    return {this->x - point.x, this->y - point.y, this->z - point.z};
}
