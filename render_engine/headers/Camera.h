#ifndef CAMERS_H
#define CAMERS_H

#include "../../math/headers/Vector3D.h"
#include "../../math/headers/Matrix4D.h"

class Camera
{
    friend bool operator==(const Camera &lhs, const Camera &rhs)
    {
        return lhs.position == rhs.position
               && lhs.target == rhs.target
               && lhs.fov == rhs.fov
               && lhs.aspectRatio == rhs.aspectRatio
               && lhs.nearPlane == rhs.nearPlane
               && lhs.farPlane == rhs.farPlane;
    }

    friend bool operator!=(const Camera &lhs, const Camera &rhs)
    {
        return !(lhs == rhs);
    }

public:
    void set_position(const Vector3D &position);

    void set_target(const Vector3D &target);

    void set_aspect_ratio(const float &aspectRatio);

    Vector3D get_position();

    Vector3D get_target();

    void move_position(const Vector3D &translation);

    void move_target(const Vector3D &translation);

    Matrix4D get_view_matrix();

    [[nodiscard]] Matrix4D get_projection_matrix() const;

    Camera(const Vector3D &position,
           const Vector3D &target,
           float fov,
           float aspectRatio,
           float nearPlane,
           float farPlane);
    float nearPlane;
    float farPlane;
private:
    Vector3D position;
    Vector3D target;
    float fov;
    float aspectRatio;


};

#endif