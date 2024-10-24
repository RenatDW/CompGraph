//
// Created by Ренат Асланов on 23.10.2024.
//

#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include "Camera.h"
#include "Model.h"

class RenderEngine
{
    public:
    static void render(
            // const GraphicsContext graphicsContext,
            const Camera camera,
            const Model mesh,
            const int width,
            const int height,
            const bool showTriangulation);
    private:
        // static void renderTriangle(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);
        // static void renderPolygons(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);

};

#endif //RENDERENGINE_H
