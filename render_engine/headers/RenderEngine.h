#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <iosfwd>
#include <iosfwd>

#include "Camera.h"
#include "../../model/headers/Model.h"
#include "../../math/headers/Point2D.h"
#include "../../math/headers/Point3D.h"

#include <QPainter>

#include "../../math/headers/DepthBuffer.h"


class RenderEngine
{
public:
    static void add_polygons_vertex(const Model &mesh, const int &width, const int &height,
                                    const Matrix4D &model_view_projection_matrix, int polygon_ind,
                                    int n_vertices_in_polygon,
                                    std::vector<Point2D> &result_points);

    static void add_triangles_vertex(const Model &mesh, const int &width, const int &height,
                                     const Matrix4D &model_view_projection_matrix, int triangle_ind,
                                     int n_vertices_in_polygon,
                                     std::vector<Point3D> &result_points, std::vector<Point3D> &world_vertex);
    static void add_normal_vertex(const Model &mesh,
                                  int triangle_ind,
                                  int n_vertices_in_polygon,
                                  std::vector<Point3D> &normal_points);
    static void add_texture_vertex(const Model &mesh,
                                   int triangle_ind,
                                   int n_vertices_in_polygon,
                                   std::vector<Point2D> &texture_vectors);

    static void draw_points(QPainter &painter, int point_count, const std::vector<Point2D> &result_points);

    static void render_polygons(QPainter &painter, const Model &mesh, const int &width, const int &height,
                                const Matrix4D &model_view_projection_matrix, int n_polygons);

    static void render_triangles(QPainter &painter, const Model &mesh, const int &width, const int &height,
                                 const Matrix4D &model_view_projection_matrix, int n_triangles, DepthBuffer &depth_buffer, Camera &camera);

    static void rasterization(QPainter &painter, const std::vector<Point3D> &result_points,
                              DepthBuffer &depth_buffer);
    static void show_mesh(QPainter &painter, std::vector<Point3D> &result_points, DepthBuffer &depth_buffer);

    static void render_texture(QPainter &painter, std::vector<Point3D> &result_points, DepthBuffer &depth_buffer, std::vector<Point2D> &textures);

    static float edgeFunction(Point3D a, Point3D b, Point3D c);

    static void render_illumination(QPainter &painter, std::vector<Point3D> &result_points, DepthBuffer &depth_buffer, std::vector<Point2D> textures, std::
                                    vector<Point3D> &illumination, Camera &camera, std::vector<Point3D> &world_vector);
    static void draw_line(QPainter &painter, Point3D &A, Point3D &B);
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
