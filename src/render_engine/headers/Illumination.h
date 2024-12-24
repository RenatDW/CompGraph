#ifndef ILLUMINATION_H
#define ILLUMINATION_H

#include "Camera.h"
#include "Renderable.h"
#include "../../math/headers/Point3D.h"

#include <vector>

class Illumination
{
public:
    //TODO исправить камел кейсы
    std::vector<Point3D> normal_points;

    Illumination() = default;

    virtual ~Illumination() = default;

    static void illumination(const std::array<Point3D, 3> &normal_vectors, const Point3D &P,
                             Camera &camera, float weight_a, float weight_b, float weight_c, int &r,
                             int &g, int &b);

    static float calculate_parametr_of_illumination(const std::array<Point3D, 3> &normal_vectors, Camera &camera,
                                             const Point3D &P,
                                             float weight_A, float weight_B, float weight_C);
};

#endif //ILLUMINATION_H
