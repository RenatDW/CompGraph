#ifndef GRAPHICCONVEYOR_H
#define GRAPHICCONVEYOR_H

#include "../../math/headers/Vector3D.h"
#include "../../math/headers/Matrix4D.h"
#include "../../model/headers/Model.h"

#include <unordered_map>
#include <array>

class GraphicConveyor
{
public:
    static void rotate_scale_translate(Model& mesh, float sx, float sy, float sz,
        float phi, float psi, float theta, float tx, float ty, float tz);

	static void rotate(Model& mesh, float phi, float psi, float theta);

	static void scale(Model& mesh, float sx, float sy, float sz);

	static void translate(Model& mesh, float tx, float ty, float tz);

public:
    static Matrix4D look_at(const Vector3D& eye, const Vector3D& target);

    static Matrix4D look_at(const Vector3D& eye, const Vector3D& target, const Vector3D& up);

    static Matrix4D perspective(float fov, float aspect_ratio, float near_plane, float far_plane);

private:
	Matrix4D rotate_matrix;

	Matrix4D scale_matrix;

	Matrix4D translate_matrix;

	static Matrix4D get_rotate_matrix(float phi, float psi, float theta);

	static Matrix4D get_scale_matrix(float sx, float sy, float sz);

	static Matrix4D get_translate_matrix(float tx, float ty, float tz);
};

#endif
