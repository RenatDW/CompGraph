#include "../headers/Vector4D.h"
#include "../headers/Vector3D.h"

#include <cmath>

Vector4D::Vector4D() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

Vector4D::Vector4D(const float x, const float y, const float z, const float w) :
	x(x), y(y), z(z), w(w) {};

float Vector4D::getX() const
{
	return x;
}

float Vector4D::getY() const
{
	return y;
};

float Vector4D::getZ() const
{
	return z;
};

float Vector4D::getW() const
{
	return w;
};

void Vector4D::setX(const float x)
{
	this->x = x;
}

void Vector4D::setY(const float y)
{
	this->y = y;
}

void Vector4D::setZ(float z)
{
	this->z = z;
}

void Vector4D::setW(float w)
{
	this->w = w;
}

Vector4D Vector4D::operator + (const Vector4D& v) const
{
	return {this->x + v.getX(), this->y + v.getY(), this->z + v.getZ(), this->w + v.getW()};
}

Vector4D Vector4D::operator - (const Vector4D& v) const
{
	return {this->x - v.getX(), this->y - v.getY(), this->z - v.getZ(), this->w - v.getW()};
}

float Vector4D::operator * (const Vector4D& v) const
{
	return this->x * v.getX() + this->y * v.getY() + this->z * v.getZ() + this->w * v.getW();
}

Vector4D Vector4D::operator * (const float k) const
{
	return {this->x * k, this->y * k, this->z * k, this->w * k};
}

float Vector4D::length() const
{
	return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

Vector4D Vector4D::normalize() const
{
	float len = this->length();
	if (len == 0) return {0, 0, 0, 0};
	len = 1 / len;
	return {this->x*len, this->y *len, this->z *len, this->w *len};
}

Vector4D::~Vector4D() = default;
