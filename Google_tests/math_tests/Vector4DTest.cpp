#include "gtest/gtest.h"
#include "../../../src/math/src/Vector4D.cpp"

TEST(Vector4DTest, DefaultConstructorVector4D)
{
    const Vector4D v;
    EXPECT_FLOAT_EQ(v.getX(), 0.0f);
    EXPECT_FLOAT_EQ(v.getY(), 0.0f);
    EXPECT_FLOAT_EQ(v.getZ(), 0.0f);
    EXPECT_FLOAT_EQ(v.getW(), 0.0f);
}

TEST(Vector4DTest, ConstructorWithXYZVector4D)
{
    const Vector4D v(1.0f, 2.0f, 0.5f, 3.0f);
    EXPECT_FLOAT_EQ(v.getX(), 1.0f);
    EXPECT_FLOAT_EQ(v.getY(), 2.0f);
    EXPECT_FLOAT_EQ(v.getZ(), 0.5f);
    EXPECT_FLOAT_EQ(v.getW(), 3.0f);
}

TEST(Vector4DTest, GettersVector4D)
{
    const Vector4D v(1.2f, 2.5f, -4.0f, 0.5f);
    EXPECT_FLOAT_EQ(v.getX(), 1.2f);
    EXPECT_FLOAT_EQ(v.getY(), 2.5f);
    EXPECT_FLOAT_EQ(v.getZ(), -4.0f);
    EXPECT_FLOAT_EQ(v.getW(), 0.5f);
}

TEST(Vector4DTest, SettersVector4D)
{
    Vector4D v(2.8f, 2.1f, 0.0f, 1.0f);
    v.setX(5.5f);
    v.setY(7.4f);
    v.setZ(3.1f);
    v.setW(1.0f);
    EXPECT_FLOAT_EQ(v.getX(), 5.5f);
    EXPECT_FLOAT_EQ(v.getY(), 7.4f);
    EXPECT_FLOAT_EQ(v.getZ(), 3.1f);
    EXPECT_FLOAT_EQ(v.getW(), 1.0f);
}

TEST(Vector4DTest, SumOperatorVector4D)
{
    const Vector4D v1(1.4f, -3.8f, 0.2f, 2.0f);
    const Vector4D v2(0.2f, 92.2f, 3.1f, 1.0f);
    EXPECT_FLOAT_EQ((v1 + v2).getX(), 1.6f);
    EXPECT_FLOAT_EQ((v1 + v2).getY(), 88.4f);
    EXPECT_FLOAT_EQ((v1 + v2).getZ(), 3.3f);
    EXPECT_FLOAT_EQ((v1 + v2).getW(), 3.0f);
}

TEST(Vector4DTest, SubOperatorVector4D)
{
    const Vector4D v1(-1.4f, -3.8f, 5.0f, 2.5f);
    const Vector4D v2(-0.2f, 2.2f, 1.0f, 1.4f);
    EXPECT_FLOAT_EQ((v1 - v2).getX(), -1.2f);
    EXPECT_FLOAT_EQ((v1 - v2).getY(), -6.0f);
    EXPECT_FLOAT_EQ((v1 - v2).getZ(), 4.0f);
    EXPECT_FLOAT_EQ((v1 - v2).getW(), 1.1f);
}

TEST(Vector4DTest, VectorByConstProductVector4D)
{
    const Vector4D v1(-1.4f, 0.0f, 1.3f, 1.4f);
    EXPECT_FLOAT_EQ((v1 * 2.0f).getX(), -2.8f);
    EXPECT_FLOAT_EQ((v1 * 2.0f).getY(), 0.0f);
    EXPECT_FLOAT_EQ((v1 * 2.0f).getZ(), 2.6f);
    EXPECT_FLOAT_EQ((v1 * 2.0f).getW(), 2.8f);
}

TEST(Vector4DTest, ScalarProductVector4D)
{
    const Vector4D v1(1.0f, 2.0f, 0.9f, 0.0f);
    const Vector4D v2(-2.3f, 0.0f, 0.0f, 9.0f);
    EXPECT_FLOAT_EQ(v1 * v2, -2.3f);
}

TEST(Vector4DTest, LengthVector4D)
{
    const Vector4D v(2.0f, 2.0f, 2.0f, 2.0f);
    EXPECT_FLOAT_EQ(v.length(), 4.0f);
}

TEST(Vector4DTest, NormalizationVector4D)
{
    const Vector4D v(4.0f, -3.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.normalize().getX(), 0.8f);
    EXPECT_FLOAT_EQ(v.normalize().getY(), -0.6f);
    EXPECT_FLOAT_EQ(v.normalize().getZ(), 0.0f);
    EXPECT_FLOAT_EQ(v.normalize().getW(), 0.0f);
}


