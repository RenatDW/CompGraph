#include "../headers/Vector2D.h"

#include <cmath>

Vector2D::Vector2D() = default;

Vector2D::Vector2D(float x, float y) : x(x), y(y) {};

float Vector2D::getX() const
{ 
	return x; 
}

float Vector2D::getY() const
{ 
	return y; 
};

void Vector2D::setX(float x)
{
	this->x = x;
}

void Vector2D::setY(float y)
{ 
	this->y = y; 
}

Vector2D Vector2D::operator + (const Vector2D& v)
{
	return Vector2D(this->x + v.getX(), this->y + v.getY());
}

Vector2D Vector2D::operator - (const Vector2D& v)
{
	return Vector2D(this->x - v.getX(), this->y - v.getY());
}

float Vector2D::operator * (const Vector2D& v)
{
	return this->x * v.getX() + this->y * v.getY();
}

float Vector2D::operator * (const float k)
{
	return Vector2D(this->x * k, this->y * k);
}

float Vector2D::length() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}

Vector2D Vector2D::normalization()
{
	return Vector2D(this->x / this->length(), this->y / this->length());
}

Vector2D::~Vector2D() = default;