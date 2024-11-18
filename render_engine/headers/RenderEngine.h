#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <iosfwd>
#include <QPainter>

#include "Camera.h"
#include "Renderable.h"
#include "../../model/headers/Model.h"
#include "../../math/headers/Point2D.h"
#include "../../math/headers/Point3D.h"


#include "../../math/headers/DepthBuffer.h"


class RenderEngine
{
public:
    void render();


    RenderEngine(QPainter &painter, Camera &camera, std::string &string, QColor &color, Model &model,
                 int width,
                 int height, bool show_mesh_param, bool show_texture_param,bool show_illumination_param);


    ~RenderEngine() = default;

private:
    DepthBuffer depth_buffer;
    QPainter &painter;
    Model &mesh;
    Camera &camera;
    std::string &filename;
    int width;
    int height;
    bool show_texture_param;
    bool show_mesh_param;
    bool show_illumination_param;
    QColor &fill_model_color;

    static void draw_line(QPainter &painter, Point3D &A, Point3D &B);


    void add_polygons_vertex(
        const Matrix4D &model_view_projection_matrix, int polygon_ind,
        int n_vertices_in_polygon,
        std::vector<Point2D> &result_points) const;

    std::vector<Point3D> get_triangles_vertex(
        const Matrix4D &model_view_projection_matrix, int triangle_ind,
        int n_vertices_in_polygon) const;

    std::vector<Point3D> get_triangle_normal_vertex(
        int triangle_ind,
        int n_vertices_in_polygon) const;

    std::vector<Point2D> get_triangle_texture_vertex(
        int triangle_ind,
        int n_vertices_in_polygon) const;

    static void draw_points(QPainter &painter, int point_count, const std::vector<Point2D> &result_points);

    void render_polygons(QPainter &painter, const Model &mesh, const int &width, const int &height,
                         const Matrix4D &model_view_projection_matrix, int n_polygons) const;

    void initialize_loop_varibles(Point3D &A, Point3D &B, Point3D &C, int &x_left,
                                  int &x_right,
                                  int &y_down, int &y_up) const;

    static void calculate_baricentric_coeficients(Point3D A, Point3D B, Point3D C, float &ABC, float ABP, float BCP, float CAP,
                                                  float &weight_a, float &weight_b, float &weight_c, float &z);

    static bool show_mesh(float weight_a, float weight_b, float weight_c, int &r, int &g, int &b);

    static float calculate_parametr_of_illumination(const std::vector<Point3D> &normal_vectors, Camera &camera, const Point3D &P,
                                                    float weightA, float weightB, float weightC);

    static QColor get_suitable_pixel(const std::vector<Point2D> &texture_vectors, const QImage &image,
                                     const float &weightA, const float &weightB, const float &weightC);

    void illumination(const std::vector<Point3D> &normal_vectors, const Point3D &P, float weightA,
                      float weightB, float weightC, int &r, int &g, int &b) const;

    void universal_render(const std::vector<Point3D> &result_points, const std::vector<Point3D> &normal_vectors,
                          const std::vector<Point2D> &
                          texture_vectors);

    void get_triangles_vectors(std::vector<Point3D> &result_points, std::vector<Point3D> &normal_vectors, std::vector<Point2D> &texture_vectors, const
                               Matrix4D &model_view_projection_matrix, int triangle_ind, int n_vertices_in_triangle);

    void render_triangles(
        const Matrix4D &model_view_projection_matrix, int n_triangles);

    static float edge_function(Point3D a, Point3D b, Point3D c);

    // static void renderTriangle(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);
    // static void renderPolygons(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);
};

#endif //RENDERENGINE_H
