//
// Created by Ренат Асланов on 07.11.2024.
//

#include "../headers/Rasterization.h"

#include <array>
#include <cmath>
#include <iostream>

// float Rasterization::edgeFunction(Point3D a, Point3D b, Point3D c) {
// return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
// }
float Rasterization::get_triangle_area_round(Point3D &a, Point3D &b, Point3D &c)
{
    {
        //Это работает для отображения сетки модели
        return (floor(b.getX()) - floor(a.getX())) * (floor(c.getY()) - floor(a.getY())) - (
                   floor(b.getY()) - floor(a.getY())) * (floor(c.getX()) - floor(a.getX()));
    }
}

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
    float ABP, BCP, CAP;
    // // if (flag) {
    //     ABP = get_triangle_area_round(A, B, P);
    //     BCP = get_triangle_area_round(B, C, P);
    //     CAP = get_triangle_area_round(C, A, P);
    // std::cout<< ABP <<", " << BCP << ", " << CAP<< "||";
    // } else {
    ABP = get_triangle_area_float(A, B, P);
    BCP = get_triangle_area_float(B, C, P);
    CAP = get_triangle_area_float(C, A, P);
    //     // std::cout<< ABP <<", " << BCP << ", " << CAP<< std::endl;
    // }

    return {ABP, BCP, CAP};
}

std::array<float, 4> Rasterization::calculate_baricentric_coeficients(Point3D A, Point3D B, Point3D C, float &ABC,
                                                                     float ABP, float BCP,
                                                                     float CAP)
{
    float weight_a, weight_b, weight_c, z;

    weight_a = BCP / ABC;
    weight_b = CAP / ABC;
    weight_c = ABP / ABC;

    z = (A.getZ() * weight_a + B.getZ() * weight_b + C.getZ() * weight_c);
    return {weight_a, weight_b, weight_c, z};
}
