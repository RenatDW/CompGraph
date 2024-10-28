#include "../headers/Matrix4D.h"
#include "../headers/Vector4D"

#include <vector>

Matrix4D Matrix4D::create_zero_matrix()
{
    Matrix4D matrix;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

Matrix4D Matrix4D::create_identity_matrix()
{
    Matrix4D matrix;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (i == j)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }

    return matrix;
}

std::vector<std::vector<float>> Matrix4D::get_matrix() const
{
    return matrix;
}

void Matrix4D::set_matrix(std::vector<std::vector<float>> matrix)
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

Matrix4D Matrix4D::operator * (const Matrix4D& m)
{
    int rowsA = this->matrix.size();
    int colsA = this->matrix[0].size();
    int colsB = m.matrix.size();

    std::vector<std::vector<float>> ans = this->matrix;

    for (int i = 0; i < rowsA; i++) 
    {
        for (int j = 0; j < colsB; j++) 
        {
            for (int k = 0; k < colsA; k++) 
            {
                ans[i][j] *= m.matrix[k][j];
            }
        }
    }

    return Matrix4D(ans);
}

Vector4D Matrix4D::operator * (const Vector4D& v)
{
    return Vector4D(this->matrix[0][0] * v.getX() + this->matrix[0][1] * v.getY() + this->matrix[0][2] * v.getZ() + this->matrix[0][3] * v.getW(),
        this->matrix[1][0] * v.getX() + this->matrix[1][1] * v.getY() + this->matrix[1][2] * v.getZ() + this->matrix[1][3] * v.getW(),
        this->matrix[2][0] * v.getX() + this->matrix[2][1] * v.getY() + this->matrix[2][2] * v.getZ() + this->matrix[2][3] * v.getW(),
        this->matrix[3][0] * v.getX() + this->matrix[3][1] * v.getY() + this->matrix[3][2] * v.getZ() + this->matrix[3][3] * v.getW()
    );
}

Matrix4D Matrix4D::operator + (const Matrix4D& m)
{
    std::vector<std::vector<float>> ans = this->matrix;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            ans[i][j] += m.matrix[i][j];
        }
    }
    return Matrix4D(ans);
}

Matrix4D Matrix4D::operator - (const Matrix4D& m)
{
    std::vector<std::vector<float>> ans = this->matrix;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            ans[i][j] -= m.matrix[i][j];
        }
    }
    return Matrix4D(ans);
}

Matrix4D Matrix4D::transposition()
{
    std::vector<std::vector<float>> ans = this->matrix;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            ans[i][j] = this->matrix[j][i];
        }
    }
    return Matrix4D(ans);
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
