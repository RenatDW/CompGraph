#include "../headers/Illumination.h"
#include "../../math//headers/MathCast.h"
#include <array>


void Illumination::illumination(const std::array<Point3D, 3>& normal_vectors,
	const Point3D& P,
	std::vector<Light> lights,
	float weight_a,
	float weight_b,
	float weight_c,
	int& r,
	int& g,
	int& b)
{
	if (normal_vectors.empty())
	{
		return;
	}
	float k = 0.4;
	float intensity = 1.0f / lights.size();
	r *= (1 - k);
	g *= (1 - k);
	b *= (1 - k);
	for (auto elem : lights)
	{
		float l = calculate_parametr_of_illumination(normal_vectors, elem.pos, P, weight_a, weight_b, weight_c);
		r += intensity * k * l * elem.color.red();
		g += intensity * k * l * elem.color.green();
		b += intensity * k * l * elem.color.blue();
	}
}
//TODO сюда передается неправильная точко P(координата на экране, а не мировая(((((((((()
float Illumination::calculate_parametr_of_illumination(const std::array<Point3D, 3>& normal_vectors,
	Vector3D& pos,
	const Point3D& P,
	const float weight_A,
	const float weight_B,
	const float weight_C)
{
	Vector3D normal_A = MathCast::to_Vector3D(normal_vectors[0]);
	Vector3D normal_B = MathCast::to_Vector3D(normal_vectors[1]);
	Vector3D normal_C = MathCast::to_Vector3D(normal_vectors[2]);

	Vector3D vn = (normal_A * weight_A + normal_B * weight_B + normal_C * weight_C).normalize();
	Vector3D ray = (Vector3D{ P.getX(), P.getY(), P.getZ()} - pos).normalize();
	float l = -(ray * vn);
	return std::max(l, 0.0f);
}
