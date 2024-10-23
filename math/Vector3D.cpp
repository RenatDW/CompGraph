#include "headers/Vector3D.h"

Vector3D::Vector3D() = default;

Vector3D::Vector3D(double x, double y, double z) : 
	x(x), y(y), z(z) {};

double Vector3D::getX() const 
{ 
	return x;
}

void Vector3D::setX(double x) 
{ 
	this->x = x;
}

double Vector3D::getY() const 
{ 
	return y; 
};

void Vector3D::setY(double y) 
{ 
	this->y = y; 
}

double Vector3D::getZ() const
{
	return z;
};

void Vector3D::setZ(double z)
{
	this->z = z;
}

Vector3D::~Vector3D() = default;