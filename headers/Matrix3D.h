#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "Vector3D.h"
#include "Matrix3D.h"

#include <vector>

class Matrix3D
{
public:
    Matrix3D(std::vector<std::vector<float>> matrix) :
        matrix(matrix) {}
    Matrix3D():
        matrix(std::vector<std::vector<float>>()){}

    Matrix3D create_zero_matrix();
    
    Matrix3D create_identity_matrix();

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