#ifndef MATRIX4D_H
#define MATRIX4D_H

#include "Vector4D.h"

#include <vector>

class Matrix4D
{
public:
    Matrix4D(std::vector<std::vector<float>> matrix) :
        matrix(matrix) {}
    Matrix4D():
        matrix(std::vector<std::vector<float>>()){}

    Matrix4D operator * (const Matrix4D& m);

    Vector4D operator * (const Vector4D& v);


    std::vector<std::vector<float>> matrix1() const {
        return matrix;
    }

private:
    std::vector<std::vector<float>> matrix;
};

#endif //MATRIX4D_H