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

    Matrix4D operator * (const Matrix4D& m);

    Vector4D operator * (const Vector4D& v);

    void print_matrix() const
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

private:
    std::vector<std::vector<float>> matrix;
};

#endif //MATRIX4D_H