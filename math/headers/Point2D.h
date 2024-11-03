#ifndef POINT2D_H
#define POINT2D_H

#include "Vector3D.h"
#include "Vector2D.h"

class Point2D
{
public:
    Point2D();

    Point2D(float x, float y);

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;


    void setX(float x);

    void setY(float y);

    void set(float x, float y);

    static Point2D vertex_to_point(Vector3D vertex, int width, int height);
    static Point2D vertex_to_point(Vector2D vertex, int width, int height);

private:
    float x;
    float y;
};

#endif
