#include "../headers/Matrix3D.h"
#include "../headers/Vector3D.h"

#include <iostream>
#include <vector>

std::vector<std::vector<float>> Matrix3D::get_matrix() const
{
    return matrix;
}

void Matrix3D::set_matrix(std::vector<std::vector<float>> matrix)
{
    if (matrix.size() != 3 &&
        matrix[0].size() != 3 &&
        matrix[1].size() != 3 &&
        matrix[2].size() != 3)
    {
        return;
    }

    this->matrix = matrix;
}

Matrix3D Matrix3D::operator * (const Matrix3D& m)
{
    int rowsA = this->matrix.size();
    int colsA = this->matrix[0].size();
    int colsB = m.matrix.size();

    std::vector<std::vector<float>> ans = this->matrix;

    for (int i = 0; i < rowsA; ++i) 
    {
        for (int j = 0; j < colsB; ++j) 
        {
            for (int k = 0; k < colsA; ++k) 
            {
                ans[i][j] *= m.matrix[k][j];
            }
        }
    }

    return Matrix3D(ans);
}

Vector3D Matrix3D::operator * (const Vector3D& v)
{
    return Vector3D(this->matrix[0][0] * v.getX() + this->matrix[0][1] * v.getY() + this->matrix[0][2] * v.getZ(),
        this->matrix[1][0] * v.getX() + this->matrix[1][1] * v.getY() + this->matrix[1][2] * v.getZ(),
        this->matrix[2][0] * v.getX() + this->matrix[2][1] * v.getY() + this->matrix[2][2] * v.getZ()
    );
}

Matrix3D Matrix3D::operator + (const Matrix3D& m)
{
    std::vector<std::vector<float>> ans = this->matrix;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			ans[i][j] += m.matrix[i][j];
		}
	}
	return Matrix3D(ans);
}

Matrix3D Matrix3D::operator - (const Matrix3D& m)
{
    std::vector<std::vector<float>> ans = this->matrix;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            ans[i][j] -= m.matrix[i][j];
        }
    }
    return Matrix3D(ans);
}

Matrix3D Matrix3D::transposition()
{
    std::vector<std::vector<float>> ans = this->matrix;

	    for (int i = 0; i < 3; ++i)
	    {
		    for (int j = 0; j < 3; ++j)
		    {
			    ans[i][j] = this->matrix[j][i];
		    }
	    }
	return Matrix3D(ans);
}


void Matrix3D::print_matrix() const 
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
