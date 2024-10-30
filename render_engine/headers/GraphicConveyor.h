#ifndef GRAPHICCONVEYOR_H
#define GRAPHICCONVEYOR_H

#include "../../math/headers/Vector3D.h"
#include "../../math/headers/Matrix4D.h"

class GraphicConveyor
{
public:
    static Matrix4D rotate_scale_translate();

    static Matrix4D look_at(const Vector3D &eye, const Vector3D &target);

    static Matrix4D look_at(const Vector3D &eye, const Vector3D &target, const Vector3D &up);

    static Matrix4D perspective(const float &fov,
                                const float &aspect_ratio,
                                const float &near_plane,
                                const float &far_plane);
};

#endif
