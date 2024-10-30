#include "../headers/Vector2D.h"

#include <cmath>

Vector2D::Vector2D() : x(0.0f), y(0.0f) {}

Vector2D::Vector2D(const float x, const float y) : x(x), y(y) {};

float Vector2D::getX() const
{
	return x;
}

float Vector2D::getY() const
{ 
	return y; 
};

void Vector2D::setX(const float x)
{
	this->x = x;
}

void Vector2D::setY(const float y)
{ 
	this->y = y; 
}

Vector2D Vector2D::operator + (const Vector2D& v) const
{
	return {this->x + v.getX(), this->y + v.getY()};
}

Vector2D Vector2D::operator - (const Vector2D& v) const
{
	return {this->x - v.getX(), this->y - v.getY()};
}

float Vector2D::operator * (const Vector2D& v) const
{
	return this->x * v.getX() + this->y * v.getY();
}

Vector2D Vector2D::operator * (const float k) const
{
	return {this->x * k, this->y * k};
}

float Vector2D::length() const
{
	return std::sqrt(this->x * this->x + this->y * this->y);
}

Vector2D Vector2D::normalization() const
{
	return {this->x / this->length(), this->y / this->length()};
}

Vector2D::~Vector2D() = default;