#include "../headers/GraphicConveyor.h"
#include "../../math/headers/Vector3D.h"
#include "../../math/headers/Matrix4D.h"
#include "../../math/headers/Matrix3D.h"
#include "../../math/headers/Vector4D.h"
#include "../../math/headers/MathCast.h"

#include <cmath>

Matrix4D GraphicConveyor::rotate_matrix_cached = Matrix4D::create_identity_matrix();
Matrix4D GraphicConveyor::scale_matrix_cached = Matrix4D::create_identity_matrix();
Matrix4D GraphicConveyor::translate_matrix_cached = Matrix4D::create_identity_matrix();

//TODO доделать
Matrix4D GraphicConveyor::get_rotate_matrix(float phi, float psi, float theta)
{
	//TODO нужно сделать универсальную r

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


	return rotate_matrix_cached;
}

Matrix4D GraphicConveyor::get_scale_matrix(float sx, float sy, float sz)
{
	if (scale_matrix_cached.get(0, 0) == sx &&
		scale_matrix_cached.get(1, 1) == sy &&
		scale_matrix_cached.get(2, 2) == sz)
	{
		return scale_matrix_cached;
	}

	scale_matrix_cached.set(0, 0, sx);
	scale_matrix_cached.set(1, 1, sy);
	scale_matrix_cached.set(2, 2, sz);
	return scale_matrix_cached;
}

Matrix4D GraphicConveyor::get_translate_matrix(float tx, float ty, float tz)
{
	if (translate_matrix_cached.get(0, 3) == tx &&
		translate_matrix_cached.get(1, 3) == ty &&
		translate_matrix_cached.get(2, 3) == tz)
	{
		return translate_matrix_cached;
	}

	translate_matrix_cached.set(0, 3, tx);
	translate_matrix_cached.set(1, 3, ty);
	translate_matrix_cached.set(2, 3, tz);
	return translate_matrix_cached;
}

void GraphicConveyor::rotate_scale_translate(Model &mesh, const float sx, const float sy, const float sz,
                                             const float phi, const float psi, const float theta, const float tx, const float ty, const float tz)
{
    const Matrix4D s = get_scale_matrix(sx, sy, sz);
    const Matrix4D r = get_rotate_matrix(phi, psi, theta);
    const Matrix4D t = get_translate_matrix(tx, ty, tz);

    for (auto& vertex : mesh.vertices)
    {
        Vector4D vertex4D = MathCast::to_Vector4D(vertex);
        vertex4D = t * r * s * vertex4D;
        vertex = MathCast::to_Vector3D(vertex4D);
    }
}

void GraphicConveyor::rotate(Model& mesh, float phi, float psi, float theta)
{
	const Matrix4D r = get_rotate_matrix(phi, psi, theta);

	for (auto& vertex : mesh.vertices)
	{
		Vector4D vertex4D = MathCast::to_Vector4D(vertex);
		vertex4D = r * vertex4D;
		vertex = MathCast::to_Vector3D(vertex4D);
	}
}

void GraphicConveyor::scale(Model& mesh, float sx, float sy, float sz)
{
	const Matrix4D s = get_scale_matrix(sx, sy, sz);

	for (auto& vertex : mesh.vertices)
	{
		Vector4D vertex4D = MathCast::to_Vector4D(vertex);
		vertex4D = s * vertex4D;
		vertex = MathCast::to_Vector3D(vertex4D);
	}
}

void GraphicConveyor::translate(Model& mesh, float tx, float ty, float tz)
{
	Matrix4D t = get_translate_matrix(tx, ty, tz);

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






