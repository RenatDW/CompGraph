#ifndef MESH_H
#define MESH_H

#include <qpainter.h>

#include "../../math/headers/Point3D.h"

class Mesh {
public:
    static void show_mesh(float weight_a, float weight_b, float weight_c, int& r, int& g, int& b, QColor background);

};

#endif //MESH_H
