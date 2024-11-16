#ifndef MODEL_H
#define MODEL_H


#include "../../math/headers/Vector2D.h"
#include "../../math/headers/Vector3D.h"
#include "Polygon.h"
#include "Triangle.h"

#include <vector>

struct Model
{
    std::vector<Vector3D> vertices;
    std::vector<Vector2D> textureVertices;
    std::vector<Vector3D> normals;
    std::vector<Polygon> polygons;
    std::vector<Triangle> triangles;
};

#endif
