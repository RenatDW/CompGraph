//
// Created by Ренат Асланов on 28.10.2024.
//

#ifndef POINT2D_H
#define POINT2D_H



class Point2D
{
public:
    Point2D();

    Point2D(float x, float y);

    static Point2D vertexToPoint(Vector3D vertex, int width, int height);

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
