#include "../headers/Vector3D.h"

Vector3D::Vector3D() = default;

Vector3D::Vector3D(float x, float y, float z) :
	x(x), y(y), z(z) {};

float Vector3D::getX() const
{ 
	return x;
}

float Vector3D::getY() const
{ 
	return y; 
};

float Vector3D::getZ() const
{
	return z;
};

void Vector3D::setX(float x)
{
	this->x = x;
}

void Vector3D::setY(float y)
{ 
	this->y = y; 
}

void Vector3D::setZ(float z)
{
	this->z = z;
}

Vector3D::~Vector3D() = default;