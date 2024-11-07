#include "gtest/gtest.h"
#include "../../math/src/Point3D.cpp"

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


