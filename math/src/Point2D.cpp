#include "../headers/Point2D.h"

Point2D::Point2D() : x(0.0f), y(0.0f) {}
Point2D::Point2D(const Vector2D &a): x(a.getX()), y(a.getY()){}

Point2D::Point2D(const float x, const float y) {
    this->x = x;
    this->y = y;
}

float Point2D::getX() const
{
    return x;
}

float Point2D::getY() const
{
    return y;
}


void Point2D::setX(float x)
{
    this->x = x;
}

void Point2D::setY(float y)
{
    this->y = y;
}

void Point2D::set(float x, float y)
{
    this->x = x;
    this->y = y;
}









