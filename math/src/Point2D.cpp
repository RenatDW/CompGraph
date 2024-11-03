#include "../headers/Vector3D.h"
#include "../headers/Point2D.h"

Point2D::Point2D() : x(0.0f), y(0.0f) {}

Point2D::Point2D(float x, float y) {
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


Point2D Point2D::vertexToPoint(const Vector3D vertex, const int width, const int height) {
    return Point2D(vertex.getX() * width + width / 2.0F, -vertex.getY() * height + height / 2.0F);
}

