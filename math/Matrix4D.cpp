//
// Created by Ренат Асланов on 24.10.2024.
//

#include "../headers/Matrix4D.h"

Matrix4D::Matrix4D() = default;

Matrix4D::Matrix4D(float ar[4][4])
{
    matrix(ar);
}

void Matrix4D::set(int x, int y, float value)
{
    matrix[x][y] = value;
}

float Matrix4D::get(int x, int y) const
{
    return matrix[x][y];
}