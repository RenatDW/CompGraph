#include "../headers/GraphicConveyor.h"
#include "../../math/headers/Vector3D.h"
#include "../../math/headers/Matrix4D.h"
#include "../../math/headers/Matrix3D.h"
#include "../../math/headers/Vector4D.h"
#include "../../math/headers/MathCast.h"

#include <cmath>

void GraphicConveyor::rotate_scale_translate(Model &mesh, const float sx, const float sy, const float sz,
                                             const float phi, const float psi, const float theta, const float tx, const float ty, const float tz)
{
    const float w = 1.0f;

    const std::vector<std::vector<float>> scale_matrix = {
			{sx, 0, 0, 0},
			{0, sy, 0, 0},
			{0, 0, sz, 0},
			{0, 0, 0, w}
    };

    const std::vector<std::vector<float>> rz_matrix = {
			{std::cos(phi), std::sin(phi), 0, 0},
			{-std::sin(phi), std::cos(phi), 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, w}
    };

    const std::vector<std::vector<float>> ry_matrix = {
			{std::cos(psi), 0, std::sin(psi), 0},
			{0, 1, 0, 0},
			{-std::sin(psi), 0, std::cos(psi), 0},
			{0, 0, 0, w}
    };

    const std::vector<std::vector<float>> rx_matrix = {
			{1, 0, 0, 0},
			{0, std::cos(theta), std::sin(theta), 0},
			{0, -std::sin(theta), std::cos(theta), 0},
			{0, 0, 0, w}
    };

    const std::vector<std::vector<float>> translation_matrix = {
			{1, 0, 0, tx},
			{0, 1, 0, ty},
			{0, 0, 1, tz},
			{0, 0, 0, w}
    };

    const Matrix4D s(scale_matrix);
    const Matrix4D rz(rz_matrix);
    const Matrix4D ry(ry_matrix);
    const Matrix4D rx(rx_matrix);
    const Matrix4D t(translation_matrix);

    const Matrix4D r = rz * ry * rx; //TODO надо придумать нормальную r

    for (auto& vertex : mesh.vertices)
    {
        Vector4D vertex4D = MathCast::to_Vector4D(vertex);
        vertex4D = t * r * s * vertex4D;
        vertex = MathCast::to_Vector3D(vertex4D);
    }
}

void GraphicConveyor::rotate(Model& mesh, float phi, float psi, float theta)
{
	const std::vector<std::vector<float>> rz_matrix = {
			{std::cos(phi), std::sin(phi), 0, 0},
			{-std::sin(phi), std::cos(phi), 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
	};

	const std::vector<std::vector<float>> ry_matrix = {
			{std::cos(psi), 0, std::sin(psi), 0},
			{0, 1, 0, 0},
			{-std::sin(psi), 0, std::cos(psi), 0},
			{0, 0, 0, 1}
	};

	const std::vector<std::vector<float>> rx_matrix = {
			{1, 0, 0, 0},
			{0, std::cos(theta), std::sin(theta), 0},
			{0, -std::sin(theta), std::cos(theta), 0},
			{0, 0, 0, 1}
	};

	const Matrix4D rz(rz_matrix);
	const Matrix4D ry(ry_matrix);
	const Matrix4D rx(rx_matrix);

	const Matrix4D r = rz * ry * rx;

	for (auto& vertex : mesh.vertices)
	{
		Vector4D vertex4D = MathCast::to_Vector4D(vertex);
		vertex4D = r * vertex4D;
		vertex = MathCast::to_Vector3D(vertex4D);
	}
}

void GraphicConveyor::scale(Model& mesh, float sx, float sy, float sz)
{
	const std::vector<std::vector<float>> scale_matrix = {
			{sx, 0, 0, 0},
			{0, sy, 0, 0},
			{0, 0, sz, 0},
			{0, 0, 0, 1}
	};

	const Matrix4D s(scale_matrix);

	for (auto& vertex : mesh.vertices)
	{
		Vector4D vertex4D = MathCast::to_Vector4D(vertex);
		vertex4D = s * vertex4D;
		vertex = MathCast::to_Vector3D(vertex4D);
	}
}

void GraphicConveyor::translate(Model& mesh, float tx, float ty, float tz)
{
	const std::vector<std::vector<float>> translation_matrix = {
			{1, 0, 0, tx},
			{0, 1, 0, ty},
			{0, 0, 1, tz},
			{0, 0, 0, 1}
	};

	const Matrix4D t(translation_matrix);

	for (auto& vertex : mesh.vertices)
	{
		Vector4D vertex4D = MathCast::to_Vector4D(vertex);
		vertex4D = t * vertex4D;
		vertex = MathCast::to_Vector3D(vertex4D);
	}
}

Matrix4D GraphicConveyor::look_at(const Vector3D &eye,const Vector3D &target)
{
    return look_at(eye, target, Vector3D(0, 1.0f, 0)); // здесь у каждой переменной был F
}

Matrix4D GraphicConveyor::look_at(const Vector3D &eye, const Vector3D &target, const Vector3D &up)
{
    Vector3D resultX = Vector3D();
    Vector3D resultY = Vector3D();
    Vector3D resultZ = Vector3D();

    resultZ = (target - eye).normalize();

    //TODO это типо фикс только если смотреть перемещать по оY модель разворачивает во все стороны
    Vector3D adjustedUp = up;
    if (std::abs(resultZ * up) > 0.99f) {
        // Если вектор up слишком близок по направлению к resultZ, используем другой вектор для up
        adjustedUp = (resultZ.getX() ==  0.0f) ? Vector3D(0, 0, 1): Vector3D(1, 0, 0);
    }
    resultX = Vector3D::cross(adjustedUp, resultZ).normalize();
    resultY = Vector3D::cross(resultZ, resultX).normalize();


    std::vector<std::vector<float> > matrix = {
        {resultX.getX(), resultY.getX(), resultZ.getX(), 0},
        {resultX.getY(), resultY.getY(), resultZ.getY(), 0},
        {resultX.getZ(), resultY.getZ(), resultZ.getZ(), 0},
        {-(resultX * eye), -(resultY * eye), -(resultZ * eye), 1}
    };
    return Matrix4D(matrix);
}

Matrix4D GraphicConveyor::perspective(const float &fov, const float &aspect_ratio, const float &near_plane,
                                      const float &far_plane)
{
    Matrix4D result;
    const auto tangent_minus_on_degree = (1.0f / (std::tan(fov * 0.5f)));
    result.set(0, 0, tangent_minus_on_degree / aspect_ratio);
    result.set(1, 1, tangent_minus_on_degree);
    result.set(2, 2, (far_plane + near_plane) / (far_plane - near_plane));
    result.set(2, 3, 1.0f);
    result.set(3, 2, 2 * (near_plane * far_plane) / (near_plane - far_plane));
    return result;
}




