#include "../headers/Matrix3D.h"

#include <iostream>
#include <vector>

Matrix3D::Matrix3D()
{
    matrix = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
}

Matrix3D::Matrix3D(const std::vector<std::vector<float>>& matrix) : matrix(matrix) {}

Matrix3D Matrix3D::create_identity_matrix()
{
    const std::vector<std::vector<float>> identity_matrix = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    return {identity_matrix};
}

std::vector<std::vector<float>> Matrix3D::get_matrix() const
{
    return matrix;
}

float Matrix3D::get(const int row, const int col) const
{
    const int N = 3;

    if (row >= 0 && row < N && col >= 0 && col < N)
    {
        return matrix[row][col];
    }

    return -1;
}

void Matrix3D::set(const std::vector<std::vector<float>>& matrix)
{
    /*if (matrix.size() != 3 &&
        matrix[0].size() != 3 &&
        matrix[1].size() != 3 &&
        matrix[2].size() != 3)
    {
        return;
    }*/

    this->matrix = matrix;
}

void Matrix3D::set(const int row, const int col, const float value)
{
    const int N = 3;

    if (row >= 0 && row < N && col >= 0 && col < N)
    {
        matrix[row][col] = value;
    }
}

Matrix3D Matrix3D::operator * (const Matrix3D& m) const
{
    const int rows_A = static_cast<int>(this->matrix.size());
    const int cols_A = static_cast<int>(this->matrix[0].size());
    const int cols_B = static_cast<int>(m.matrix.size());

    std::vector ans(rows_A, std::vector(cols_B, 0.0f));

    for (int i = 0; i < rows_A; ++i)
    {
        for (int j = 0; j < cols_B; ++j)
        {
            for (int k = 0; k < cols_A; ++k)
            {
                ans[i][j] += this->matrix[i][k] * m.matrix[k][j];
            }
        }
    }

    return {ans};
}

Vector3D Matrix3D::operator * (const Vector3D& v) const
{
    return{
        this->matrix[0][0] * v.getX() + this->matrix[0][1] * v.getY() + this->matrix[0][2] * v.getZ(),
        this->matrix[1][0] * v.getX() + this->matrix[1][1] * v.getY() + this->matrix[1][2] * v.getZ(),
        this->matrix[2][0] * v.getX() + this->matrix[2][1] * v.getY() + this->matrix[2][2] * v.getZ()
    };
}

Matrix3D Matrix3D::operator + (const Matrix3D& m) const
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

Matrix3D Matrix3D::operator - (const Matrix3D& m) const
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
    return {ans};
}

Matrix3D Matrix3D::transposition() const
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