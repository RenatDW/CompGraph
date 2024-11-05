#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <iosfwd>
#include <iosfwd>
#include <iosfwd>

#include "Camera.h"
#include "../../model/headers/Model.h"
#include "../../math/headers/Point2D.h"
#include "../../math/headers/Point3D.h"

#include <QPainter>

#include "TypeOfRender.h"
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

    static void initialize_loop_varibles(DepthBuffer &depth_buffer, Point3D &A, Point3D &B, Point3D &C, int &x_left,
                                         int &x_right,
                                         int &y_down, int &y_up);

    static float calculate_parametr_of_illumination(std::vector<Point3D> &normal_vectors, Camera &camera, Point3D P,
                                                    float weightA, float weightB, float weightC);

    static QColor do_work(std::vector<Point2D> &texture_vectors, QImage &image,
                          const float &weightA, const float &weightB, const float &weightC);

    static void universal_render(QPainter &painter, std::vector<Point3D> &result_points, std::vector<Point3D> &normal_vectors, std::vector<Point2D>
                                 &texture_vectors, DepthBuffer &depth_buffer, std::string &filename, QColor &fill_color, Camera &camera);

    static void render_triangles(QPainter &painter, const Model &mesh, const int &width,
                                 const int &height, const Matrix4D &model_view_projection_matrix, int n_triangles, DepthBuffer &depth_buffer, std::
                                 string &filename, Camera &camera);

    static void rasterization(QPainter &painter, const std::vector<Point3D> &result_points,
                              DepthBuffer &depth_buffer);
    static void show_mesh(QPainter &painter, std::vector<Point3D> &result_points, DepthBuffer &depth_buffer);

    static void render_texture(QPainter &painter, std::vector<Point3D> &result_points, DepthBuffer &depth_buffer, std::vector<Point2D> &textures);

    static float edgeFunction(Point3D a, Point3D b, Point3D c);

    static void render_illumination(QPainter &painter, std::vector<Point3D> &result_points, DepthBuffer &depth_buffer, std::vector<Point3D> &illumination, Camera
                                    &camera);
    static void draw_line(QPainter &painter, Point3D &A, Point3D &B);
    static void render(
        QPainter &painter,
        Camera &camera,
        std::string &filename,
        const Model &mesh,
        const int &width, const int &height, const bool &show_triangulation);

private:
    // static void renderTriangle(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);
    // static void renderPolygons(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);
};

#endif //RENDERENGINE_H
