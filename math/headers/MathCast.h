#ifndef MATH_CAST_H
#define MATH_CAST_H

#include "Point2D.h"
#include "Point3D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix3D.h"
#include "Matrix4D.h"

class MathCast
{
public:
    static Point2D to_Point2D(const Vector3D& v, int width, int height);

    static Point3D to_Point3D(const Vector3D& v, int width, int height);

    static Vector3D to_Vector3D(const Point3D& point);

    static Vector3D to_Vector3D(const Vector4D& v);

    static Vector4D to_Vector4D(const Vector3D& v);
};

#endif
