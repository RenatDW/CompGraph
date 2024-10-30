#ifndef MATRIX4D_H
#define MATRIX4D_H

#include "Vector4D.h"
#include "Vector3D.h"

#include <vector>

class Matrix4D
{
public:
    Matrix4D();

    Matrix4D(const std::vector<std::vector<float>>& matrix);

    static Matrix4D create_identity_matrix();

    [[nodiscard]] std::vector<std::vector<float>> get_matrix() const;

    [[nodiscard]] float get(int row, int col) const;

    void set(const std::vector<std::vector<float>>& matrix);

    void set(int row, int col, float value);

    static Vector3D multiply_matrix4d_by_vector3d(const Matrix4D& matrix, const Vector3D& vertex);

    Matrix4D operator * (const Matrix4D& m) const;

    Vector4D operator * (const Vector4D& v) const;

    Matrix4D operator + (const Matrix4D& m) const;

    Matrix4D operator - (const Matrix4D& m) const;

    [[nodiscard]] Matrix4D transposition() const;

    void print_matrix() const;

    void mul(const Matrix4D& m);

private:
    std::vector<std::vector<float>> matrix;
};

#endif