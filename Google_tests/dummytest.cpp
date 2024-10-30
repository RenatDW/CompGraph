#include "gtest/gtest.h"

#include "../objwriter/dummyWriter.cpp"

TEST(SumTest, HandlesPositiveNumbers) {
    EXPECT_FLOAT_EQ(sum(1.0f, 2.0f), 3.0f); // Проверяем сумму положительных чисел
}

TEST(SumTest, HandlesNegativeNumbers) {
    EXPECT_FLOAT_EQ(sum(-1.0f, -2.0f), -3.0f); // Проверяем сумму отрицательных чисел
}

TEST(SumTest, HandlesMixedNumbers) {
    EXPECT_FLOAT_EQ(sum(1.0f, -2.0f), -1.0f); // Проверяем сумму смешанных чисел
}

TEST(SumTest, HandlesZero) {
    EXPECT_FLOAT_EQ(sum(0.0f, 0.0f), 0.0f); // Проверяем сумму нулей
}
