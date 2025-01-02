#ifndef ILLUMINATION_H
#define ILLUMINATION_H

#include "Camera.h"
#include "Light.h"
#include "../../math/headers/Point3D.h"

#include <vector>

class Illumination
{
public:
	std::vector<Point3D> normal_points;

	Illumination() = default;

	virtual ~Illumination() = default;

	static void illumination(const std::array<Point3D, 3>& normal_vectors,
		const Point3D& P,
		const std::vector<Light>& lights,
		float weight_a,
		float weight_b,
		float weight_c,
		int& r,
		int& g,
		int& b);

	static float calculate_parameter_of_illumination(const std::array<Point3D, 3>& normal_vectors,
		Vector3D& pos,
		const Point3D& P,
		const float weight_A,
		const float weight_B,
		const float weight_C);
};

#endif
