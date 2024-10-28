#include "../headers/Vector3D.h"

#include <cmath>

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

Vector3D Vector3D::operator + (const Vector3D& v)
{
	return Vector3D(this->x + v.getX(), this->y + v.getY(), this->z + v.getZ());
}

Vector3D Vector3D::operator - (const Vector3D& v)
{
	return Vector3D(this->x - v.getX(), this->y - v.getY(), this->z - v.getZ());
}

float Vector3D::operator * (const Vector3D& v)
{
	return this->x * v.getX() + this->y * v.getY() + this->z * v.getZ();
}

float Vector3D::operator * (const float k)
{
	return Vector3D(this->x * k, this->y * k, this->z * k);
}

float Vector3D::length() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3D Vector3D::normalization()
{
	return Vector3D(this->x / this->length(), this->y / this->length(), this->z / this->length());
}

Vector3D::~Vector3D() = default;