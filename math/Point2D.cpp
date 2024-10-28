//
// Created by Ренат Асланов on 28.10.2024.
//
#include "../headers/Vector3D.h"
#include "../headers/Point2D.h"

Point2D Point2D::vertexToPoint(const Vector3D vertex, const int width, const int height) {
    return Point2D(vertex.getX() * width + width / 2.0F, -vertex.getY() * height + height / 2.0F);
}

Point2D::Point2D(float x, float y) {
    this->x = x;
    this->y = y;
}
