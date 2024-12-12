#include "gtest/gtest.h"
#include "../../../src/math/src/MathCast.cpp"

TEST(MathCastTest, Vector3DtoPoint2D)
{
    const Vector3D vertex(1.0f, 2.0f, -1.0f);
    const Point2D point = MathCast::to_Point2D(vertex, 4, 5);
    EXPECT_FLOAT_EQ(point.getX(), 6.0f);
    EXPECT_FLOAT_EQ(point.getY(), -7.5f);
}

TEST(MathCastTest, Vector3DtoPoint3D)
{
    const Vector3D vertex(1.0f, 2.0f, 3.0f);
    const Point3D point = MathCast::to_Point3D(vertex, 5, 10);
    EXPECT_FLOAT_EQ(point.getX(), 7.5f);
    EXPECT_FLOAT_EQ(point.getY(), -15.0f);
    EXPECT_FLOAT_EQ(point.getZ(), 3.0f);
}

TEST(MathCastTest, Point3DtoVector3D)
{
    const Point3D point(1.0f, 2.0f, -3.0f);
    const Vector3D vector = MathCast::to_Vector3D(point);
    EXPECT_FLOAT_EQ(vector.getX(), 1.0f);
    EXPECT_FLOAT_EQ(vector.getY(), 2.0f);
    EXPECT_FLOAT_EQ(vector.getZ(), -3.0f);
}

TEST(MathCastTest, Vector4DtoVector3D)
{
    const Vector4D v(1.0f, 2.0f, 3.0f, 4.0f);
    EXPECT_FLOAT_EQ(MathCast::to_Vector3D(v).getX(), 0.25f);
    EXPECT_FLOAT_EQ(MathCast::to_Vector3D(v).getY(), 0.5f);
    EXPECT_FLOAT_EQ(MathCast::to_Vector3D(v).getZ(), 0.75f);
}

TEST(MathCastTest, Vector3DtoVector4D)
{
    const Vector3D v(1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(MathCast::to_Vector4D(v).getX(), 1.0f);
    EXPECT_FLOAT_EQ(MathCast::to_Vector4D(v).getY(), 2.0f);
    EXPECT_FLOAT_EQ(MathCast::to_Vector4D(v).getZ(), 3.0f);
    EXPECT_FLOAT_EQ(MathCast::to_Vector4D(v).getW(), 1.0f);
}