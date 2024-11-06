#include "gtest/gtest.h"
#include "../../math/src/Matrix3D.cpp"

TEST(Matrix3DTest, GetterMatrix3D)
{
    const Matrix3D matrix = Matrix3D::create_identity_matrix();
    EXPECT_FLOAT_EQ(matrix.get(0, 0), 1.0f);
}

TEST(Matrix3DTest, ElementSetterMatrix3D)
{
    Matrix3D matrix = Matrix3D::create_identity_matrix();
    matrix.set(0,0, -10.0f);
    EXPECT_FLOAT_EQ(matrix.get(0, 0), -10.0f);
}

TEST(Matrix3DTest, MatrixSetterMatrix3D)
{
    Matrix3D matrix1 = Matrix3D::create_identity_matrix();
    const Matrix3D matrix2;
    matrix1.set(matrix2.get_matrix());
    EXPECT_FLOAT_EQ(matrix1.get(0, 0), 0.0f);
}

TEST(Matrix3DTest, EqualsMatrixMatrix3D)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    const std::vector<std::vector<float>> matrix2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    const std::vector<std::vector<float>> matrix3 = {
        {0, 2, 3},
        {0, 0, 6},
        {7, 8, 0}
    };

    EXPECT_TRUE(matrix1 == matrix2);
    EXPECT_TRUE(matrix1 != matrix3);
}

TEST(Matrix3DTest, SumOperatorMatrix3D)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    const std::vector<std::vector<float>> matrix2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    Matrix3D m1;
    Matrix3D m2;
    m1.set(matrix1);
    m2.set(matrix2);

    const std::vector<std::vector<float>> answer = {
        {10, 10, 10},
        {10, 10, 10},
        {10, 10, 10}
    };


    EXPECT_TRUE((m1 + m2).get_matrix() == answer);
}

TEST(Matrix3DTest, SubOperatorMatrix3D)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    const std::vector<std::vector<float>> matrix2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    Matrix3D m1;
    Matrix3D m2;
    m1.set(matrix1);
    m2.set(matrix2);

    const std::vector<std::vector<float>> answer = {
        {-8, -6, -4},
        {-2, 0, 2},
        {4, 6, 8}
    };

    EXPECT_TRUE((m1 - m2).get_matrix() == answer);
}

TEST(Matrix3DTest, MatrixByMatrixProductMatrix3D)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    const std::vector<std::vector<float>> matrix2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    Matrix3D m1;
    Matrix3D m2;
    m1.set(matrix1);
    m2.set(matrix2);

    const std::vector<std::vector<float>> answer = {
        {30, 24, 18},
        {84, 69, 54},
        {138, 114, 90}
    };

    EXPECT_TRUE((m1 * m2).get_matrix() == answer);
}

TEST(Matrix3DTest, MatrixByVectorProductMatrix3D)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    Matrix3D m;
    const Vector3D v({9, 6, 3});
    m.set(matrix1);

    EXPECT_FLOAT_EQ((m * v).getX(), 30);
    EXPECT_FLOAT_EQ((m * v).getY(), 84);
    EXPECT_FLOAT_EQ((m * v).getZ(), 138);
}

TEST(Matrix3DTest, TranspositionMatrix3D)
{
    const std::vector<std::vector<float>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    const std::vector<std::vector<float>> matrix2 = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };

    const Matrix3D m1(matrix1);
    EXPECT_TRUE(m1.transposition().get_matrix() == matrix2);
}