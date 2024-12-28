#include "../headers/Rasterization.h"

#include <array>
#include <cmath>
#include <iostream>

float Rasterization::get_triangle_area_float(Point3D &a, Point3D &b, Point3D &c)
{
    float a1 = (b.getX() - a.getX());
    float a2 = (c.getY() - a.getY());
    float b1 = (b.getY() - a.getY());
    float b2 = (c.getX() - a.getX());
    return a1*a2 - b1*b2;
}


std::array<float, 3> Rasterization::calculate_edge_functions(Point3D &A, Point3D &B, Point3D &C, Point3D &P, bool flag)
{
	float ABP = get_triangle_area_float(A, B, P);
	float BCP = get_triangle_area_float(B, C, P);
	float CAP = get_triangle_area_float(C, A, P);
    return {ABP, BCP, CAP};
}

std::array<float, 4> Rasterization::calculate_baricentric_coeficients(Point3D A,
	Point3D B,
	Point3D C,
	Point3D P)
{
	float ABC = get_triangle_area_float(A, B, C);
	float ABP = get_triangle_area_float(A, B, P);
	float BCP = get_triangle_area_float(B, C, P);
	float CAP = get_triangle_area_float(C, A, P);

	float weight_a = BCP / ABC;
	float weight_b = CAP / ABC;
	float weight_c = ABP / ABC;

	float z = (A.getZ() * weight_a + B.getZ() * weight_b + C.getZ() * weight_c);
    return {weight_a, weight_b, weight_c, z};
}
