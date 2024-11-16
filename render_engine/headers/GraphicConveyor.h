#ifndef GRAPHICCONVEYOR_H
#define GRAPHICCONVEYOR_H

#include "../../math/headers/Vector3D.h"
#include "../../math/headers/Matrix4D.h"
#include "../../model/headers/Model.h"

class GraphicConveyor
{
public:
    static void rotate_scale_translate(Model& mesh, float sx, float sy, float sz,
        float phi, float psi, float theta, float tx, float ty, float tz);

    static Matrix4D look_at(const Vector3D &eye, const Vector3D &target);

    static Matrix4D look_at(const Vector3D &eye, const Vector3D &target, const Vector3D &up);

    static Matrix4D perspective(const float &fov,
                                const float &aspect_ratio,
                                const float &near_plane,
                                const float &far_plane);
};

#endif
