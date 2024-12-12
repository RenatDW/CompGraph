#include "gtest/gtest.h"
#include "../../../src/math/src/Point2D.cpp"
#include "../../../src/math/headers/Vector3D.h"
#include "../../../src/math/headers/MathCast.h"

TEST(Point2DTest, DefaultConstructor)
{
    const Point2D point;
    EXPECT_FLOAT_EQ(point.getX(), 0.0f);
    EXPECT_FLOAT_EQ(point.getY(), 0.0f);
}

TEST(Point2DTest, ConstructorWithXY)
{
    const Point2D point(1.0f, -2.9f);
    EXPECT_FLOAT_EQ(point.getX(), 1.0f);
    EXPECT_FLOAT_EQ(point.getY(), -2.9f);
}

TEST(Point2DTest, Getters)
{
    const Point2D point(0.0f, -2.9f);
    EXPECT_FLOAT_EQ(point.getX(), 0.0f);
    EXPECT_FLOAT_EQ(point.getY(), -2.9f);
}
