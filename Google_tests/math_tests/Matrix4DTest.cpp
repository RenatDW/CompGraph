#include "gtest/gtest.h"
#include "../../math/src/Matrix4D.cpp"
#include "../../math/headers/Vector4D.h"
#include "../../math/src/Vector4D.cpp"

TEST(Matrix4DTest, Getter)
{
    const Matrix4D matrix = Matrix4D::create_identity_matrix();
    EXPECT_FLOAT_EQ(matrix.get(3, 3), 1.0f);
}

TEST(Matrix4DTest, ElementSetter)
{
    Matrix4D matrix = Matrix4D::create_identity_matrix();
    matrix.set(2,3, -10.0f);
    EXPECT_FLOAT_EQ(matrix.get(2, 3), -10.0f);
}

TEST(Matrix4DTest, MatrixSetter)
{
    Matrix4D matrix1 = Matrix4D::create_identity_matrix();
    const Matrix4D matrix2;
    matrix1.set(matrix2.get_matrix());
    EXPECT_FLOAT_EQ(matrix1.get(0, 0), 0.0f);
}

TEST(Matrix4DTest, EqualsMatrix)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3, 1},
        {4, 5, 6, 2},
        {7, 8, 9, 3},
        {1, 2, 3, 4}
    };
    const std::vector<std::vector<float>> matrix2 = {
        {1, 2, 3, 1},
        {4, 5, 6, 2},
        {7, 8, 9, 3},
        {1, 2, 3, 4}
    };
    const std::vector<std::vector<float>> matrix3 = {
        {1, 2, 3, 1},
        {4, 5, 6, 2},
        {7, 8, 9, 3},
        {0, 0, 0, 0}
    };

    EXPECT_TRUE(matrix1 == matrix2);
    EXPECT_TRUE(matrix1 != matrix3);
}

TEST(Matrix4DTest, SumOperator)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3, 1},
        {4, 5, 6, 2},
        {7, 8, 9, 3},
        {1, 2, 3, 4}
    };

    const std::vector<std::vector<float>> matrix2 = {
        {9, 9, 9, 9},
        {9, 9, 9, 9},
        {9, 9, 9, 9},
        {9, 9, 9, 9}
    };

    Matrix4D m1;
    Matrix4D m2;
    m1.set(matrix1);
    m2.set(matrix2);

    const std::vector<std::vector<float>> answer = {
        {10, 11, 12, 10},
        {13, 14, 15, 11},
        {16, 17, 18, 12},
        {10, 11, 12, 13}
    };

    EXPECT_TRUE((m1 + m2).get_matrix() == answer);
}

TEST(Matrix4DTest, SubOperator)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3, 1},
        {4, 5, 6, 2},
        {7, 8, 9, 3},
        {1, 2, 3, 4}
    };

    const std::vector<std::vector<float>> matrix2 = {
        {1, 2, 3, 1},
        {5, 6, 7, 3},
        {7, 8, 9, 3},
        {2, 3, 4, 5}
    };

    Matrix4D m1;
    Matrix4D m2;
    m1.set(matrix1);
    m2.set(matrix2);

    const std::vector<std::vector<float>> answer = {
        {0, 0, 0, 0},
        {-1, -1, -1, -1},
        {0, 0, 0, 0},
        {-1, -1, -1, -1}
    };

    EXPECT_TRUE((m1 - m2).get_matrix() == answer);
}

TEST(Matrix4DTest, Matrix4DByMatrixProduct)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3, 1},
        {4, 5, 6, 2},
        {7, 8, 9, 3},
        {1, 2, 3, 4}
    };

    const std::vector<std::vector<float>> matrix2 = {
        {1, 2, 3, 1},
        {40, 50, 60, 20},
        {7, 8, 9, 3},
        {10, 20, 30, 40}
    };

    Matrix4D m1;
    Matrix4D m2;
    m1.set(matrix1);
    m2.set(matrix2);

    const std::vector<std::vector<float>> answer = {
        {112, 146, 180, 90},
        {266, 346, 426, 202},
        {420, 546, 672, 314},
        {142, 206, 270, 210}
    };

    EXPECT_TRUE((m1 * m2).get_matrix() == answer);
}

TEST(Matrix4DTest, Matrix4DByVectorProduct)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3, 1},
        {4, 5, 6, 2},
        {7, 8, 9, 3},
        {1, 2, 3, 4}
    };

    Matrix4D m;
    const Vector4D v({9, 6, 3, 1});
    m.set(matrix1);

    EXPECT_FLOAT_EQ((m * v).getX(), 31);
    EXPECT_FLOAT_EQ((m * v).getY(), 86);
    EXPECT_FLOAT_EQ((m * v).getZ(), 141);
    EXPECT_FLOAT_EQ((m * v).getW(), 34);
}

TEST(Matrix4DTest, TranspositionMatrix4D)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3, 1},
        {4, 5, 6, 2},
        {7, 8, 9, 3},
        {1, 2, 3, 4}
    };

    const std::vector<std::vector<float>> matrix2 = {
        {1, 4, 7, 1},
        {2, 5, 8, 2},
        {3, 6, 9, 3},
        {1, 2, 3, 4}
    };
    const Matrix4D m1(matrix1);

    EXPECT_TRUE(m1.transposition().get_matrix() == matrix2);
}
