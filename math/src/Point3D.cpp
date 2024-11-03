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

Point3D Point3D::vertex_to_point(Vector3D vertex, int width, int height, float z)
{
    return Point3D(vertex.getX() * width + width / 2.0F, -vertex.getY() * height + height / 2.0F, z);
}
