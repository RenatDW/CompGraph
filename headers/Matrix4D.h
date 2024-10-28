#ifndef MATRIX4D_H
#define MATRIX4D_H

#include "Vector4D.h"

#include <vector>
#include <iostream>

class Matrix4D
{
public:
    Matrix4D(std::vector<std::vector<float>> matrix) :
        matrix(matrix) {}

    Matrix4D create_zero_matrix();

    Matrix4D create_identity_matrix();

    std::vector<std::vector<float>> get_matrix() const;

    void set_matrix(std::vector<std::vector<float>> matrix);

    Matrix4D operator * (const Matrix4D& m);

    Vector4D operator * (const Vector4D& v);

    Matrix4D operator + (const Matrix4D& m);

    Matrix4D operator - (const Matrix4D& m);

    Matrix4D transposition();

    void print_matrix() const;

private:
    std::vector<std::vector<float>> matrix;
};

#endif //MATRIX4D_H