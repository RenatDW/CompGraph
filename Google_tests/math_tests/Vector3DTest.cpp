#include "gtest/gtest.h"
#include "../../math/src/Vector3D.cpp"

TEST(Vector3DTest, DefaultConstructor)
{
    const Vector3D v;
    EXPECT_FLOAT_EQ(v.getX(), 0.0f);
    EXPECT_FLOAT_EQ(v.getY(), 0.0f);
    EXPECT_FLOAT_EQ(v.getZ(), 0.0f);
}

TEST(Vector3DTest, ConstructorWithXYZ)
{
    const Vector3D v(1.0f, 2.0f, 0.5f);
    EXPECT_FLOAT_EQ(v.getX(), 1.0f);
    EXPECT_FLOAT_EQ(v.getY(), 2.0f);
    EXPECT_FLOAT_EQ(v.getZ(), 0.5f);
}

TEST(Vector3DTest, Getters)
{
    const Vector3D v(1.2f, 2.5f, -4.0f);
    EXPECT_FLOAT_EQ(v.getX(), 1.2f);
    EXPECT_FLOAT_EQ(v.getY(), 2.5f);
    EXPECT_FLOAT_EQ(v.getZ(), -4.0f);
}

TEST(Vector3DTest, Setters)
{
    Vector3D v(2.8f, 2.1f, 0.0f);
    v.setX(5.5f);
    v.setY(7.4f);
    v.setZ(3.1f);
    EXPECT_FLOAT_EQ(v.getX(), 5.5f);
    EXPECT_FLOAT_EQ(v.getY(), 7.4f);
    EXPECT_FLOAT_EQ(v.getZ(), 3.1f);
}

TEST(Vector3DTest, SumOperator)
{
    const Vector3D v1(1.4f, -3.8f, 0.2f);
    const Vector3D v2(0.2f, 92.2f, 3.1f);
    EXPECT_FLOAT_EQ((v1 + v2).getX(), 1.6f);
    EXPECT_FLOAT_EQ((v1 + v2).getY(), 88.4f);
    EXPECT_FLOAT_EQ((v1 + v2).getZ(), 3.3f);
}

TEST(Vector3DTest, SubOperator)
{
    const Vector3D v1(-1.4f, -3.8f, 5.0f);
    const Vector3D v2(-0.2f, 2.2f, 1.0f);
    EXPECT_FLOAT_EQ((v1 - v2).getX(), -1.2f);
    EXPECT_FLOAT_EQ((v1 - v2).getY(), -6.0f);
    EXPECT_FLOAT_EQ((v1 - v2).getZ(), 4.0f);
}

TEST(Vector3DTest, VectorByConstProduct)
{
    const Vector3D v1(-1.4f, 0.0f, 1.3f);
    EXPECT_FLOAT_EQ((v1 * 2.0f).getX(), -2.8f);
    EXPECT_FLOAT_EQ((v1 * 2.0f).getY(), 0.0f);
    EXPECT_FLOAT_EQ((v1 * 2.0f).getZ(), 2.6f);
}

TEST(Vector3DTest, ScalarProduct)
{
    const Vector3D v1(1.0f, 2.0f, 0.9f);
    const Vector3D v2(-2.3f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(v1 * v2, -2.3f);
}

TEST(Vector3DTest, Length)
{
    const Vector3D v(200.0f, -200.0f, 100.0f);
    EXPECT_FLOAT_EQ(v.length(), 300.f);
}

TEST(Vector3DTest, Normalization)
{
    const Vector3D v(4.0f, -3.0f, 0.0f);
    EXPECT_FLOAT_EQ(v.normalize().getX(), 0.8f);
    EXPECT_FLOAT_EQ(v.normalize().getY(), -0.6f);
    EXPECT_FLOAT_EQ(v.normalize().getZ(), 0.0f);
}
