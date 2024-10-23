#ifndef MODEL_H
#define MODEL_H

#include "Vector3D.h"
#include "Vector2D.h"
#include "Polygon.h"

#include <vector>

class Model
{
public:
	std::vector<Vector3D> vertices;
	std::vector<Vector2D> textureVertices;
	std::vector<Vector3D> normals;
	std::vector<Polygon> polygons;
};

#endif