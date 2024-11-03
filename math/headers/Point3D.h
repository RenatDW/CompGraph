//
// Created by Ренат Асланов on 03.11.2024.
//

#ifndef POINT3D_H
#define POINT3D_H
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

    static Point3D vertex_to_point(Vector3D vertex, int width, int height, float z);

private:
    float x;
    float y;
    float z;
};


#endif //POINT3D_H
