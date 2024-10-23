#include "Vector4D.h"

Vector4D::Vector4D() = default;

Vector4D::Vector4D(double x, double y, double z, double w) :
	x(x), y(y), z(z), w(w) {};

double Vector4D::getX() const
{
	return x;
}

void Vector4D::setX(double x)
{
	this->x = x;
}

double Vector4D::getY() const
{
	return y;
};

void Vector4D::setY(double y)
{
	this->y = y;
}

double Vector4D::getZ() const
{
	return z;
};

void Vector4D::setZ(double z)
{
	this->z = z;
}

double Vector4D::getW() const
{
	return w;
};

void Vector4D::setW(double w)
{
	this->w = w;
}

Vector4D::~Vector4D() = default;
