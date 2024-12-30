#ifndef TRIANGLECOORD_H
#define TRIANGLECOORD_H
#include "../../math/headers/Point2D.h"

struct TriangleCoordinates
{
	int triangle_id{};
	int vertex_id{};
	Point2D vertex{};
};
#endif
