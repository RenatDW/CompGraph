#include "../headers/Vector2D.h"

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

Vector2D::~Vector2D() = default;