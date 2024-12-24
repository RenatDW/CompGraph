#include "../headers/Illumination.h"
#include "../../math//headers/MathCast.h"
#include <array>

void Illumination::illumination(const std::array<Point3D, 3> &normal_vectors, const Point3D &P, Camera &camera, const float weight_a,
                                const float weight_b, const float weight_c, int &r, int &g, int &b)
{
    if (normal_vectors.empty()) {
        return;
    }
    float k = 0.4;
    float l = calculate_parametr_of_illumination(normal_vectors, camera, P, weight_a, weight_b, weight_c);
    r *= (1 - k + k * l), g *= (1 - k + k * l), b *= (1 - k + k * l);
}

float Illumination::calculate_parametr_of_illumination(const std::array<Point3D, 3> &normal_vectors, Camera &camera,
    const Point3D &P, const float weight_A, const float weight_B, const float weight_C)
{
    Vector3D cam{ camera.get_position().getX(), camera.get_position().getY(), camera.get_position().getZ()};
    Vector3D normal_A = MathCast::to_Vector3D(normal_vectors[0]).normalize();
    Vector3D normal_B = MathCast::to_Vector3D(normal_vectors[1]).normalize();
    Vector3D normal_C = MathCast::to_Vector3D(normal_vectors[2]).normalize();
    Vector3D vn = (normal_A * weight_A + normal_B * weight_B + normal_C * weight_C).normalize();
    Vector3D ray = (cam - Vector3D{P.getX(), P.getY(), P.getZ()}).normalize();
    float l = -(ray * vn);
    if (l < 0.0f) {
        l = 0.0f;
    }
    return l;
}
