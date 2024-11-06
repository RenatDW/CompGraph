//
// Created by Ренат Асланов on 03.11.2024.
//

#include "../headers/Point3D.h"
#include "../headers/Vector3D.h"
Point3D::Point3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Point3D::getX()
{
    return x;
}

float Point3D::getY()
{
    return y;
}

float Point3D::getZ()
{
    return z;
}

void Point3D::setX(float x)
{
    this->x = x;
}

void Point3D::setY(float y)
{
    this->y = y;
}

void Point3D::setZ(float z)
{
    this->z = z;
}

void Point3D::set(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point3D Point3D::operator*(const float a) const
{
    return {this->x * a, this->y * a, this->z * a};
}

Point3D Point3D::operator+(Point3D &v2) const
{
    return {this->x + v2.x, this->y + v2.y, this->z + v2.z};
}

Point3D Point3D::normalize()
{
    float len = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
    return  {this->x / len, this->y / len, this->z / len};
}

Point3D Point3D::operator-(const Point3D &point_3d) const
{
    return {this->x - point_3d.x, this->y - point_3d.y, this->z - point_3d.z};
}

float Point3D::dot(Point3D &v)
{
    return this->x * v.getX() + this->y * v.getY() + this->z * v.getZ();

}

Point3D Point3D::operator*(const Point3D &cam) const
{

}


Point3D Point3D::vertex_to_point(Vector3D vertex, int width, int height)
{
    return Point3D(vertex.getX() * width + width / 2.0F, -vertex.getY() * height + height / 2.0F, vertex.getZ());
}

Vector3D Point3D::point_to_vector(Point3D point)
{
    return Vector3D(point.getX(), point.getY(), point.getZ());
}
