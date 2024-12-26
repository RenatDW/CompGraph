#ifndef CAMERA_H
#define CAMERA_H

#include "../../math/headers/Vector3D.h"
#include "../../math/headers/Matrix4D.h"

class Camera
{
public:
	Camera(const Vector3D &position,
			const Vector3D &target,
			float fov,
			float aspectRatio,
			float nearPlane,
			float farPlane);


	Camera();

    void set_position(const Vector3D& t_position);

    void set_target(const Vector3D& t_target);

    void set_aspect_ratio(const float& t_aspectRatio);

    void move_position(const Vector3D &translation);

    void move_target(const Vector3D &translation);

    Matrix4D get_view_matrix();

	Vector3D& get_position();

	Vector3D& get_target();

    [[nodiscard]] Matrix4D get_projection_matrix();

public:
	float nearPlane;
	float farPlane;

private:
    Vector3D position;
    Vector3D target;
    float fov;
    float aspectRatio;
};

#endif