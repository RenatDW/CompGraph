#include "../headers/Matrix4D.h"
#include "../headers/Vector4D.h"

#include <vector>
#include <iostream>

Matrix4D::Matrix4D()
{
    this->matrix = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
}

Matrix4D Matrix4D::create_identity_matrix()
{
    const std::vector<std::vector<float>> identity_matrix = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    return {identity_matrix};
}

std::vector<std::vector<float>> Matrix4D::get_matrix() const
{
    return matrix;
}

float Matrix4D::get(const int row, const int col) const
{
    const int N = 4;

    if (row >=0 && row < N && col >= 0 && col < N)
    {
        return matrix[row][col];
    }

    return -1;
}

void Matrix4D::set(const std::vector<std::vector<float>>& matrix)
{
    if (matrix.size() != 4 &&
        matrix[0].size() != 4 &&
        matrix[1].size() != 4 &&
        matrix[2].size() != 4 &&
        matrix[3].size() != 4)
    {
        return;
    }

    this->matrix = matrix;
}

void Matrix4D::set(const int row, const int col, const float value)
{
    const int N = 4;

    if (row >= 0 && row < N && col >= 0 && col < N)
    {
        matrix[row][col] = value;
    }
}

Matrix4D Matrix4D::operator * (const Matrix4D& m) const
{
    const int ROWS_A = static_cast<int>(this->matrix.size());
    const int COLS_A = static_cast<int>(this->matrix[0].size());
    const int COLS_B = static_cast<int>(m.matrix.size());

    std::vector<std::vector<float>> ans = this->matrix;

    for (int i = 0; i < ROWS_A; i++)
    {
        for (int j = 0; j < COLS_B; j++)
        {
            for (int k = 0; k < COLS_A; k++)
            {
                ans[i][j] *= m.matrix[k][j];
            }
        }
    }

    return {ans};
}

Vector4D Matrix4D::operator * (const Vector4D& v) const
{
    return {
        this->matrix[0][0] * v.getX() + this->matrix[0][1] * v.getY() + this->matrix[0][2] * v.getZ() + this->matrix[0][3] * v.getW(),
        this->matrix[1][0] * v.getX() + this->matrix[1][1] * v.getY() + this->matrix[1][2] * v.getZ() + this->matrix[1][3] * v.getW(),
        this->matrix[2][0] * v.getX() + this->matrix[2][1] * v.getY() + this->matrix[2][2] * v.getZ() + this->matrix[2][3] * v.getW(),
        this->matrix[3][0] * v.getX() + this->matrix[3][1] * v.getY() + this->matrix[3][2] * v.getZ() + this->matrix[3][3] * v.getW()
    };
}

Matrix4D Matrix4D::operator + (const Matrix4D& m) const
{
    std::vector<std::vector<float>> ans = this->matrix;
    const int N = static_cast<int>(ans.size());

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            ans[i][j] += m.matrix[i][j];
        }
    }
    return {ans};
}

Matrix4D Matrix4D::operator - (const Matrix4D& m) const
{
    std::vector<std::vector<float>> ans = this->matrix;
    const int N = static_cast<int>(ans.size());

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            ans[i][j] -= m.matrix[i][j];
        }
    }
    return{ans};
}

Matrix4D Matrix4D::transposition() const
{
    std::vector<std::vector<float>> ans = this->matrix;
    const int N = static_cast<int>(ans.size());

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            ans[i][j] = this->matrix[j][i];
        }
    }
    return {ans};
}

void Matrix4D::print_matrix() const
{
    for (const auto& row : matrix)
    {
        std::cout << "[ ";
        for (const auto& element : row)
        {
            std::cout << element << " ";
        }
        std::cout << "]" << std::endl;
    }
}
void Matrix4D::mul(const Matrix4D &m) {
    const int N = static_cast<int>(this->matrix.size());

    std::vector<std::vector<float>> result(N, std::vector<float>(N, 0.0f));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                result[i][j] += this->matrix[i][k] * m.matrix[k][j];
            }
        }
    }

    this->matrix = result;
}
