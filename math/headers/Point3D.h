#ifndef POINT3D_H
#define POINT3D_H

#include "Vector3D.h"

class Point3D
{
public:
    Point3D() = default;

    Point3D(float x, float y, float z);

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    [[nodiscard]] float getZ() const;

    void setX(float x);

    void setY(float y);

    void setZ(float z);

    void set(float x, float y, float z);

    Point3D operator * (float a) const;

    Point3D operator + (const Point3D &v2) const;

    Point3D operator - (const Point3D & point_3d) const;

    float dot(const Point3D &v) const;

    Point3D operator*(const Point3D & cam) const;

    [[nodiscard]] Point3D normalize() const;

    static Point3D vertex_to_point(const Vector3D& vertex, int width, int height, float near, float far);

    static Vector3D point_to_vector(Point3D point);

private:
    float x;
    float y;
    float z;
};

#endif
