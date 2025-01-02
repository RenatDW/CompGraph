#include "../headers/Illumination.h"
#include "../../math//headers/MathCast.h"
#include <array>

void Illumination::illumination(const std::array<Point3D, 3>& normal_vectors,
	const Point3D& P,
	const std::vector<Light>& lights,
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
	float intensity = 1.0f / static_cast<float>(lights.size());
	r *= static_cast<int>(1 - k);
	g *= static_cast<int>(1 - k);
	b *= static_cast<int>(1 - k);
	for (auto elem : lights)
	{
		float l = calculate_parameter_of_illumination(normal_vectors, elem.pos, P, weight_a, weight_b, weight_c);
		r += static_cast<int>(intensity * k * l * static_cast<float>(elem.color.red()));
		g += static_cast<int>(intensity * k * l * static_cast<float>(elem.color.green()));
		b += static_cast<int>(intensity * k * l * static_cast<float>(elem.color.blue()));
	}
}
float Illumination::calculate_parameter_of_illumination(const std::array<Point3D, 3>& normal_vectors,
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
