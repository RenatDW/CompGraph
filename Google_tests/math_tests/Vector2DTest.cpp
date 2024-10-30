#include "gtest/gtest.h"
#include "../../math/src/Vector2D.cpp"

TEST(Vector2DTest, DefaultConstructor) {
    Vector2D v;
    EXPECT_FLOAT_EQ(v.getX(), 0.0f);
    EXPECT_FLOAT_EQ(v.getY(), 0.0f);
}
