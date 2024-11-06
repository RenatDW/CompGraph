#include "gtest/gtest.h"
#include "../../math/src/Point2D.cpp"
#include "../../math/headers/Vector3D.h"

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

TEST(Point2D, VertexToPoint)
{
    const Vector3D vertex(1.0f, 2.0f, -1.0f);
    const Point2D point = Point2D::vertex_to_point(vertex, 4, 5);
    EXPECT_FLOAT_EQ(point.getX(), 6.0f);
    EXPECT_FLOAT_EQ(point.getY(), -7.5f);
}