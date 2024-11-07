#include "../headers/Vector3D.h"
#include "../headers/Vector4D.h"

#include <cmath>

Vector3D::Vector3D() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3D::Vector3D(const float x, const float y, const float z) :
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

void Vector3D::setX(const float x)
{
	this->x = x;
}

void Vector3D::setY(const float y)
{ 
	this->y = y; 
}

void Vector3D::setZ(const float z)
{
	this->z = z;
}

Vector3D Vector3D::operator + (const Vector3D& v) const
{
	return {this->x + v.getX(), this->y + v.getY(), this->z + v.getZ()};
}

Vector3D Vector3D::operator - (const Vector3D& v) const
{
	return {this->x - v.getX(), this->y - v.getY(), this->z - v.getZ()};
}

Vector3D Vector3D::cross(const Vector3D &v1, const Vector3D &v2)
{
	float x = v1.y * v2.z - v1.z * v2.y;
	float y = v2.x * v1.z - v2.z * v1.x;
	float z = v1.x * v2.y - v1.y * v2.x;

	return {x,y,z};
}


float Vector3D::operator * (const Vector3D& v) const
{
	return this->x * v.getX() + this->y * v.getY() + this->z * v.getZ();
}

Vector3D Vector3D::operator * (const float k) const
{
	return {this->x * k, this->y * k, this->z * k};
}

float Vector3D::length() const
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3D Vector3D::normalize() const
{
	if(this->length() == 0) return {0,0,0};
	return {this->x / this->length(), this->y / this->length(), this->z / this->length()};
}

Vector3D Vector3D::transition(const Vector4D& v)
{
	return {v.getX()/v.getW(), v.getY()/v.getW(), v.getZ()/v.getW()};
}

Vector3D::~Vector3D() = default;