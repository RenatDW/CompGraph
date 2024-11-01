#include "../headers/Vector3D.h"
#include "../headers/Point2D.h"

Point2D::Point2D() : x(0.0f), y(0.0f) {}

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

Point2D Point2D::vertexToPoint(const Vector3D& vertex, const int width, const int height) {
    return{vertex.getX() * static_cast<float>(width) + static_cast<float>(width) / 2.0f,
        -vertex.getY() * static_cast<float>(height) + static_cast<float>(height) / 2.0f};
}

