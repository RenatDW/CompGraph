#include "gtest/gtest.h"
#include "../../math/src/MathCast.cpp"

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

TEST(MathCastTests, Point3DtoVector3D)
{
    const Point3D point(1.0f, 2.0f, -3.0f);
    const Vector3D vector = MathCast::to_Vector3D(point);
    EXPECT_FLOAT_EQ(vector.getX(), 1.0f);
    EXPECT_FLOAT_EQ(vector.getY(), 2.0f);
    EXPECT_FLOAT_EQ(vector.getZ(), -3.0f);
}
