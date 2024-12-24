#include "../headers/Matrix4D.h"

#include <vector>
#include <iostream>
#include <limits>

Matrix4D::Matrix4D()
{
    this->matrix = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
}

Matrix4D::Matrix4D(const std::vector<std::vector<float> > &matrix) : matrix(matrix) {}

Matrix4D Matrix4D::create_identity_matrix()
{
    std::vector<std::vector<float> > identity_matrix = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    return {identity_matrix};
}

std::vector<std::vector<float> > Matrix4D::get_matrix() const
{
    return matrix;
}

float Matrix4D::get(const int row, const int col) const
{
    const int N = 4;

    if (row >= 0 && row < N && col >= 0 && col < N) {
        return matrix[row][col];
    }

    return -1;
}

void Matrix4D::set(const std::vector<std::vector<float> > &matrix)
{
    if (matrix.size() != 4 &&
        matrix[0].size() != 4 &&
        matrix[1].size() != 4 &&
        matrix[2].size() != 4 &&
        matrix[3].size() != 4) {
        return;
    }

    this->matrix = matrix;
}

void Matrix4D::set(const int row, const int col, const float value)
{
    const int N = 4;

    if (row >= 0 && row < N && col >= 0 && col < N) {
        matrix[row][col] = value;
    }
}

Vector3D Matrix4D::multiply_matrix4d_by_vector3d(const Matrix4D &matrix, const Vector3D &vertex)
{
	const float x = vertex.getX() * matrix.get(0, 0) + vertex.getY() * matrix.get(0, 1) + vertex.getZ() * matrix.get(0, 2) + matrix.get(0, 3);
	const float y = vertex.getX() * matrix.get(1, 0) + vertex.getY() * matrix.get(1, 1) + vertex.getZ() * matrix.get(1, 2) + matrix.get(1, 3);
	const float z = vertex.getX() * matrix.get(2, 0) + vertex.getY() * matrix.get(2, 1) + vertex.getZ() * matrix.get(2, 2) + matrix.get(2, 3);
	const float w = vertex.getX() * matrix.get(3, 0) + vertex.getY() * matrix.get(3, 1) + vertex.getZ() * matrix.get(3, 2) + matrix.get(3, 3);
	return {x / w, y / w, z / w};

}


Matrix4D Matrix4D::operator *(const Matrix4D &m) const
{
    const int rows_A = static_cast<int>(this->matrix.size());
    const int cols_A = static_cast<int>(this->matrix[0].size());
    const int cols_B = static_cast<int>(m.matrix.size());

    std::vector ans(rows_A, std::vector(cols_B, 0.0f));

    for (int i = 0; i < rows_A; i++)
    {
        for (int j = 0; j < cols_B; j++)
        {
            for (int k = 0; k < cols_A; k++)
            {
                ans[i][j] += this->matrix[i][k] * m.matrix[k][j];

            }
        }
    }

    return {ans};
}

Vector4D Matrix4D::operator *(const Vector4D &v) const
{
    return {
        this->matrix[0][0] * v.getX() + this->matrix[0][1] * v.getY() + this->matrix[0][2] * v.getZ() + this->matrix[0][
            3] * v.getW(),
        this->matrix[1][0] * v.getX() + this->matrix[1][1] * v.getY() + this->matrix[1][2] * v.getZ() + this->matrix[1][
            3] * v.getW(),
        this->matrix[2][0] * v.getX() + this->matrix[2][1] * v.getY() + this->matrix[2][2] * v.getZ() + this->matrix[2][
            3] * v.getW(),
        this->matrix[3][0] * v.getX() + this->matrix[3][1] * v.getY() + this->matrix[3][2] * v.getZ() + this->matrix[3][
            3] * v.getW()
    };
}

Matrix4D Matrix4D::operator +(const Matrix4D &m) const
{
    std::vector<std::vector<float> > ans = this->matrix;
    const int N = static_cast<int>(ans.size());

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ans[i][j] += m.matrix[i][j];
        }
    }
    return {ans};
}

Matrix4D Matrix4D::operator -(const Matrix4D &m) const
{
    std::vector<std::vector<float> > ans = this->matrix;
    const int N = static_cast<int>(ans.size());

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ans[i][j] -= m.matrix[i][j];
        }
    }
    return {ans};
}

Matrix4D Matrix4D::transposition() const
{
    std::vector<std::vector<float> > ans = this->matrix;
    const int N = static_cast<int>(ans.size());

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ans[i][j] = this->matrix[j][i];
        }
    }
    return {ans};
}


std::ostream& operator<<(std::ostream& os, const Matrix4D& d)
{
	for(auto line : d.matrix){
		os << " " << line[0]<< " " << line[1]<< " " << line[2]<< " " << line[3]<< std::endl;
	}
	return os;
}
