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


Point2D Point2D::vertex_to_point(const Vector3D vertex, const int width, const int height) {
    return Point2D(vertex.getX() * width + width / 2.0F, -vertex.getY() * height + height / 2.0F);

Point2D Point2D::vertexToPoint(const Vector3D& vertex, const int width, const int height) {
    return{vertex.getX() * static_cast<float>(width) + static_cast<float>(width) / 2.0f,
        -vertex.getY() * static_cast<float>(height) + static_cast<float>(height) / 2.0f};

}







