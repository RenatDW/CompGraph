//
// Created by Ренат Асланов on 24.10.2024.
//

#ifndef MATRIX4D_H
#define MATRIX4D_H

class Matrix4D
{
public:
    Matrix4D();

    Matrix4D(float ar[4][4]);

    void set(int x, int y, float value);

    float get(int x, int y) const;

private:
    float matrix[4][4];
};

#endif //MATRIX4D_H