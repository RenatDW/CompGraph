//
// Created by Ренат Асланов on 28.10.2024.
//

#ifndef POINT2D_H
#define POINT2D_H



class Point2D {
    public:
    static Point2D vertexToPoint(const Vector3D vertex, const int width, const int height);

    Point2D() = default;

    Point2D(float x, float y);

    float x1() const {
        return x;
    }

    float y1() const {
        return y;
    }

private:
    float x;
    float y;
};



#endif //POINT2D_H
