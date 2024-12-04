#include "gtest/gtest.h"
#include "../../src/math/src/Point3D.cpp"
#include "../../src/math/headers/Vector3D.h"
#include "../../src/math/headers/MathCast.h"

TEST(Point3DTest, GettersPoint3D)
{
    const Point3D point(1.0f, 2.0f, -3.0f);
    EXPECT_FLOAT_EQ(point.getX(), 1.0f);
    EXPECT_FLOAT_EQ(point.getY(), 2.0f);
    EXPECT_FLOAT_EQ(point.getZ(), -3.0f);
}

TEST(Point3DTest, SettersPoint3D)
{
    Point3D point;
    point.setX(1.0f);
    point.setY(2.0f);
    point.setZ(3.0f);
    EXPECT_FLOAT_EQ(point.getX(), 1.0f);
    EXPECT_FLOAT_EQ(point.getY(), 2.0f);
    EXPECT_FLOAT_EQ(point.getZ(), 3.0f);
    point.set(-1.0f, -3.0f, -21.0f);
    EXPECT_FLOAT_EQ(point.getX(), -1.0f);
    EXPECT_FLOAT_EQ(point.getY(), -3.0f);
    EXPECT_FLOAT_EQ(point.getZ(), -21.0f);
}

TEST(Point3DTest, Point3DbyConstProduct)
{
    const Point3D point(1.0f, 2.0f, -3.0f);
    EXPECT_FLOAT_EQ((point * 2.0f).getX(), 2.0f);
    EXPECT_FLOAT_EQ((point * 2.0f).getY(), 4.0f);
    EXPECT_FLOAT_EQ((point * 2.0f).getZ(), -6.0f);
}

TEST(Point3DTest, SumOperatorPoint3D)
{
    const Point3D point1(1.0f, 2.0f, -3.0f);
    const Point3D point2(0.0f, 5.0f, -13.0f);
    EXPECT_FLOAT_EQ((point1 + point2).getX(), 1.0f);
    EXPECT_FLOAT_EQ((point1 + point2).getY(), 7.0f);
    EXPECT_FLOAT_EQ((point1 + point2).getZ(), -16.0f);
}

TEST(Point3DTest, SubOperatorPoint3D)
{
    const Point3D point1(1.0f, 2.0f, -3.0f);
    const Point3D point2(0.0f, 5.0f, -13.0f);
    EXPECT_FLOAT_EQ((point1 - point2).getX(), 1.0f);
    EXPECT_FLOAT_EQ((point1 - point2).getY(), -3.0f);
    EXPECT_FLOAT_EQ((point1 - point2).getZ(), 10.0f);
}

TEST(Point3DTest, normalizePoint3D)
{
    const Point3D point(3.0f, 4.0f, 0.0f);
    EXPECT_FLOAT_EQ(point.normalize().getX(), 0.6f);
    EXPECT_FLOAT_EQ(point.normalize().getY(), 0.8f);
    EXPECT_FLOAT_EQ(point.normalize().getZ(), 0.0f);
}

TEST(Point3DTest, Point3DbyPoint3DProduct)
{
    const Point3D point1(1.0f, 2.0f, -3.0f);
    const Point3D point2(0.0f, 5.0f, -13.0f);
    EXPECT_FLOAT_EQ((point1 * point2), 49.0f);
}