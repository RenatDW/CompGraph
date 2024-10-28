#include "../headers/Matrix3D.h"
#include "../headers/Vector3D.h"

#include <iostream>
#include <vector>

Matrix3D Matrix3D::operator * (const Matrix3D& m)
{
    int rowsA = this->matrix.size();
    int colsA = this->matrix[0].size();
    int rowsB = m.matrix.size();
    int colsB = m.matrix.size();

    std::vector<std::vector<int>> ans(rowsA, std::vector<int>(colsB, 0));

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                ans[i][j] += this->matrix[i][k] * m.matrix[k][j];
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

void Matrix3D::printMatrix() const {
    for (const auto& row : matrix) {
        std::cout << "[ ";
        for (const auto& element : row) {
            std::cout << element << " ";
        }
        std::cout << "]" << std::endl;
    }
}
