#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "Vector3D.h"
#include "Matrix3D.h"

#include <vector>

class Matrix3D
{
public:
    Matrix3D(std::vector<std::vector<int>> matrix) :
        matrix(matrix) {}

    std::vector<std::vector<float>> get_matrix() const;

    void set_matrix(std::vector<std::vector<float>> matrix);

    Matrix3D operator * (const Matrix3D& m);

    Vector3D operator * (const Vector3D& v);

    Matrix3D operator + (const Matrix3D& m);

	Matrix3D operator - (const Matrix3D& m);

    Matrix3D transposition();

    void print_matrix() const;

private:
    std::vector<std::vector<float>> matrix;
};




#endif