#include "gtest/gtest.h"
#include "../../math/src/Point3D.cpp"

TEST(Point3DTest, GettersPoint3D)
{
    const Point3D point(1.0f, 2.0f, -3.0f);
    EXPECT_FLOAT_EQ(point.getX(), 1.0f);
    EXPECT_FLOAT_EQ(point.getY(), 2.0f);
    EXPECT_FLOAT_EQ(point.getZ(), -3.0f);
}



