#ifndef POINT3D_H
#define POINT3D_H

#include "Vector3D.h"

class Point3D
{
public:
    Point3D();

    Point3D(const Vector3D &);

    Point3D(float x, float y, float z);

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] float getZ() const;

    void setX(float x);

    void setY(float y);

    void setZ(float z);

    void set(float x, float y, float z);

    Point3D operator * (float a) const;

    float operator * (const Point3D & cam) const;

    Point3D operator + (const Point3D &v2) const;

    Point3D operator - (const Point3D & point_3d) const;

    static Point3D vector_to_point(Vector3D a);
    [[nodiscard]] Point3D normalize() const;

private:
    float x;
    float y;
    float z;
};

#endif
