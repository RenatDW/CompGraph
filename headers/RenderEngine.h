#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <iosfwd>

#include "Camera.h"
#include "Model.h"
#include <QPainter>

#include "Point2D.h"

class RenderEngine
{
public:
    static void add_polygons_vertex(const Model &mesh, const int &width, const int &height,
                                    const Matrix4D &model_view_projection_matrix, int polygon_ind, int n_vertices_in_polygon,
                                    std::vector<Point2D> &result_points);

    static void render_polygons(QPainter &painter, const Model &mesh, const int &width, const int &height,
                                const Matrix4D &model_view_projection_matrix, int nPolygons);

    static void render(
        QPainter &painter,
        Camera &camera,
        const Model &mesh,
        const int &width,
        const int &height,
        const bool &show_triangulation);

private:
    // static void renderTriangle(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);
    // static void renderPolygons(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);
};

#endif //RENDERENGINE_H
