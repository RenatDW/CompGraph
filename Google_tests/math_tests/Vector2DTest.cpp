#include "gtest/gtest.h"
#include "../../math/src/Vector2D.cpp"

TEST(Vector2DTest, DefaultConstructorVector2D)
{
    const Vector2D v;
    EXPECT_FLOAT_EQ(v.getX(), 0.0f);
    EXPECT_FLOAT_EQ(v.getY(), 0.0f);
}

TEST(Vector2DTest, ConstructorWithXYVector2D)
{
    const Vector2D v(1.0f, 2.0f);
    EXPECT_FLOAT_EQ(v.getX(), 1.0f);
    EXPECT_FLOAT_EQ(v.getY(), 2.0f);
}

TEST(Vector2DTest, GettersVector2D)
{
    const Vector2D v(1.2f, 2.5f);
    EXPECT_FLOAT_EQ(v.getX(), 1.2f);
    EXPECT_FLOAT_EQ(v.getY(), 2.5f);
}

TEST(Vector2DTest, SettersVector2D)
{
    Vector2D v(2.8f, 2.1f);
    v.setX(5.5f);
    v.setY(7.4f);
    EXPECT_FLOAT_EQ(v.getX(), 5.5f);
    EXPECT_FLOAT_EQ(v.getY(), 7.4f);
}

TEST(Vector2DTest, SumOperatorVector2D)
{
    const Vector2D v1(1.4f, -3.8f);
    const Vector2D v2(0.2f, 92.2f);
    EXPECT_FLOAT_EQ((v1 + v2).getX(), 1.6f);
    EXPECT_FLOAT_EQ((v1 + v2).getY(), 88.4f);
}

TEST(Vector2DTest, SubOperatorVector2D)
{
    const Vector2D v1(-1.4f, -3.8f);
    const Vector2D v2(-0.2f, 2.2f);
    EXPECT_FLOAT_EQ((v1 - v2).getX(), -1.2f);
    EXPECT_FLOAT_EQ((v1 - v2).getY(), -6.0f);
}

TEST(Vector2DTest, VectorByConstProductVector2D)
{
    const Vector2D v1(-1.4f, 0.0f);
    EXPECT_FLOAT_EQ((v1 * 2.0f).getX(), -2.8f);
    EXPECT_FLOAT_EQ((v1 * 2.0f).getY(), 0.0f);
}

TEST(Vector2DTest, ScalarProductVector2D)
{
    const Vector2D v1(1.0f, 2.0f);
    const Vector2D v2(-2.3f, 0.0f);
    EXPECT_FLOAT_EQ(v1 * v2, -2.3f);
}

TEST(Vector2DTest, LengthVector2D)
{
    const Vector2D v(3.0f, -4.0f);
    EXPECT_FLOAT_EQ(v.length(), 5.0f);
}

TEST(Vector2DTest, NormalizationVector2D)
{
    const Vector2D v(4.0f, -3.0f);
    EXPECT_FLOAT_EQ(v.normalization().getX(), 0.8f);
    EXPECT_FLOAT_EQ(v.normalization().getY(), -0.6f);
}