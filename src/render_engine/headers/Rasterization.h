#ifndef RASTERIZATION_H
#define RASTERIZATION_H
#include "../../math/headers/Point3D.h"
#include <array>

class Rasterization
{
public:
    Rasterization() = default;

    static float get_triangle_area_float(Point3D &a, Point3D &b, Point3D &c);

	static std::array<float, 3> calculate_edge_functions(Point3D &A, Point3D &B, Point3D &C, Point3D &P, bool flag);

    static std::array<float, 4> calculate_baricentric_coeficients(Point3D A,
		Point3D B,
		Point3D C,
		Point3D P);

    ~Rasterization() = default;
};

#endif
