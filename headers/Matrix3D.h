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

    Matrix3D operator * (const Matrix3D& m);


    Vector3D operator * (const Vector3D& v);

    void printMatrix() const;
    
private:
    std::vector<std::vector<float>> matrix;
};




#endif