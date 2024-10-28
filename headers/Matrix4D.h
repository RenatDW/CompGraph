#ifndef MATRIX4D_H
#define MATRIX4D_H

#include "Vector4D.h"

#include <vector>

class Matrix4D
{
public:
    Matrix4D(std::vector<std::vector<float>> matrix) :
        matrix(matrix) {}
    Matrix4D();

    Matrix4D operator * (const Matrix4D& m);

    Vector4D operator * (const Vector4D& v);

    void mul(const Matrix4D &m1);

    std::vector<std::vector<float>> matrix1() const {
        return matrix;
    }

    std::vector<std::vector<float>> matrix;
};

#endif //MATRIX4D_H