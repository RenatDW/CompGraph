#include "../headers/Vector4D.h"

Vector4D::Vector4D() = default;

Vector4D::Vector4D(float x, float y, float z, float w) :
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

void Vector4D::setX(float x)
{
	this->x = x;
}

void Vector4D::setY(float y)
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

Vector4D::~Vector4D() = default;
