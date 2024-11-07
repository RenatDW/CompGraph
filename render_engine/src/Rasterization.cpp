//
// Created by Ренат Асланов on 07.11.2024.
//

#include "../headers/Rasterization.h"


float Rasterization::edgeFunction(Point3D a, Point3D b, Point3D c) {
    return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
}
