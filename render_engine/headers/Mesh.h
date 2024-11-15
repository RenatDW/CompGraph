//
// Created by Ренат Асланов on 15.11.2024.
//

#ifndef MESH_H
#define MESH_H
#include <qpainter.h>

#include "../../math/headers/Point3D.h"



class Mesh {
public:
    static bool show_mesh(float weightA, float weightB, float weightC, int &r, int &g, int &b);
    static void show_mesh_by_points(QPainter &painter, Point3D A, Point3D B);

};



#endif //MESH_H
