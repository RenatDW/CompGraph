#include "gtest/gtest.h"
#include "../../../src/math/src/Point2D.cpp"

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

TEST(Point2DTest, Setters)
{
	Point2D point(0.1f, -2.0f);
	point.setX(1.0f);
	point.setY(9.0f);
	EXPECT_FLOAT_EQ(point.getX(), 1.0f);
	EXPECT_FLOAT_EQ(point.getY(), 9.0f);
	point.set(0.9f, 0.9f);
	EXPECT_FLOAT_EQ(point.getX(), 0.9f);
	EXPECT_FLOAT_EQ(point.getY(), 0.9f);
}

TEST(Point2DTest, EqualityOperator) {
	Point2D p1(3.0, 4.0);
	Point2D p2(3.0, 4.0);
	Point2D p3(5.0, 4.0);

	EXPECT_TRUE(p1 == p2);
	EXPECT_FALSE(p1 == p3);
}

TEST(Point2DTest, InequalityOperator) {
	Point2D p1(3.0, 4.0);
	Point2D p2(3.0, 4.0);
	Point2D p3(3.0, 5.0);

	EXPECT_FALSE(p1 != p2);
	EXPECT_TRUE(p1 != p3);
}

TEST(Point2DTest, LessThanOperator) {
	Point2D p1(2.0, 3.0);
	Point2D p2(3.0, 3.0);
	Point2D p3(2.0, 4.0);
	Point2D p4(2.0, 3.0);

	EXPECT_TRUE(p1 < p2);
	EXPECT_TRUE(p1 < p3);
	EXPECT_FALSE(p1 < p4);
	EXPECT_FALSE(p2 < p1);
}
