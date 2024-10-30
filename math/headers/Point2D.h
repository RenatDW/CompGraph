#ifndef POINT2D_H
#define POINT2D_H

#include "Vector3D.h"

class Point2D
{
public:
    Point2D();

    Point2D(float x, float y);

    float getX() const;

    float getY() const;

    static Point2D vertexToPoint(Vector3D vertex, int width, int height);

private:
    float x;
    float y;
};

#endif
