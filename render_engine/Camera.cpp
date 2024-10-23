//
// Created by Ренат Асланов on 23.10.2024.
//

#include "Camera.h"
class Camera {
    public:
    Camera(
        const Vector3f position,
            const Vector3f target,
            const float fov,
            const float aspectRatio,
            const float nearPlane,
            const float farPlane) {
                this->position = position;
                this->target = target;
                this->fov = fov;
                this->aspectRatio = aspectRatio;
                this->nearPlane = nearPlane;
                this->farPlane = farPlane;
    }
    private:
    Vector3f position;
    Vector3f target;
    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
};
