#include "../headers/Illumination.h"
#include "../../math//headers/MathCast.h"
#include <array>


void Illumination::illumination(const std::array<Point3D, 3> &normal_vectors, const Point3D &P, std::vector<Light> lights, float weight_a,
                                float weight_b, float weight_c, int &r, int &g, int &b)
{
    if (normal_vectors.empty()) {
        return;
    }
	float k = 0.4;

	for(auto elem: lights)
	{
		float l = calculate_parametr_of_illumination(normal_vectors, elem.pos, P, weight_a, weight_b, weight_c);
		r *= (1 - k + k * l) * std::max(float(elem.color.red()) / 255.0f, 0.0000001f);
		g *= (1 - k + k * l) * std::max(float(elem.color.green()) / 255.0f, 0.0000001f);
		b *= (1 - k + k * l) * std::max(float(elem.color.blue()) / 255.0f, 0.0000001f);
	}
}

float Illumination::calculate_parametr_of_illumination(const std::array<Point3D, 3> &normal_vectors, Vector3D& pos,
    const Point3D &P, const float weight_A, const float weight_B, const float weight_C)
{
    Vector3D normal_A = MathCast::to_Vector3D(normal_vectors[0]).normalize();
    Vector3D normal_B = MathCast::to_Vector3D(normal_vectors[1]).normalize();
    Vector3D normal_C = MathCast::to_Vector3D(normal_vectors[2]).normalize();
    Vector3D vn = (normal_A * weight_A + normal_B * weight_B + normal_C * weight_C).normalize();
    Vector3D ray = (pos - Vector3D{P.getX(), P.getY(), P.getZ()}).normalize();
    float l = -(ray * vn);
    if (l < 0.0f) {
        l = 0.0f;
    }
    return l;
}
