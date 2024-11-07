//
// Created by Ренат Асланов on 07.11.2024.
//

#ifndef RASTERIZATION_H
#define RASTERIZATION_H
#include "Renderable.h"


class Rasterization {
public:
    std::vector<Point3D> result_points;
    Rasterization() = default;

    void render();

    static float edgeFunction(Point3D a, Point3D b, Point3D c);


    ~Rasterization() = default;
};



#endif //RASTERIZATION_H
