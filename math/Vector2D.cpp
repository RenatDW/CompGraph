#pragma once
#include "Vector2D.h"

Vector2D::Vector2D() = default;

Vector2D::Vector2D(double x, double y) : x(x), y(y) {};

double Vector2D::getX() const 
{ 
	return x; 
}

void Vector2D::setX(double x) 
{ 
	this->x = x; 
}

double Vector2D::getY() const 
{ 
	return y; 
};

void Vector2D::setY(double y) 
{ 
	this->y = y; 
}

Vector2D::~Vector2D() = default;