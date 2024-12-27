#ifndef MATRIX3D_H
#define MATRIX3D_H

#include "Vector3D.h"

#include <vector>

class Matrix3D
{
public:
    Matrix3D();

    Matrix3D(const std::vector<std::vector<float>>& matrix);

    static Matrix3D create_identity_matrix();

    [[nodiscard]] const std::vector<std::vector<float>>& get_matrix() const;

    [[nodiscard]] float get(int row, int col) const;

    void set(const std::vector<std::vector<float>>& matrix);

    void set(int row, int col, float value);

    Matrix3D operator * (const Matrix3D& m) const;

    Vector3D operator * (const Vector3D& v) const;

    Matrix3D operator + (const Matrix3D& m) const;

	Matrix3D operator - (const Matrix3D& m) const;

    [[nodiscard]] Matrix3D transposition() const;

    friend bool operator == (const Matrix3D& lhs, const Matrix3D& rhs)
    {
        return lhs.matrix == rhs.matrix;
    }

    friend bool operator != (const Matrix3D &lhs, const Matrix3D &rhs)
    {
        return !(lhs == rhs);
    }

private:
    std::vector<std::vector<float>> matrix;
};

#endif