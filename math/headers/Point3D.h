//
// Created by Ренат Асланов on 03.11.2024.
//

#ifndef POINT3D_H
#define POINT3D_H
#include <qstringconverter_base.h>
#include <string>

#include "Vector3D.h"


class Point3D
{
public:
    Point3D() = default;

    Point3D(float x, float y, float z);

    float getX();

    float getY();

    float getZ();

    void setX(float x);

    void setY(float y);

    void setZ(float z);

    void set(float x, float y, float z);
    Point3D operator * (float a) const;

    Point3D operator+(Point3D &v2) const;

    Point3D normalize();

    Point3D operator-(const Point3D & point_3d) const;

    float dot(Point3D &v);

    Point3D operator*(const Point3D & cam) const;


    static Point3D vertex_to_point(Vector3D vertex, int width, int height, float z);

    static Vector3D point_to_vector(Point3D point);

private:
    float x;
    float y;
    float z;
};


#endif //POINT3D_H
