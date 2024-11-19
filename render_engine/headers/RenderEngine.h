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
    void initialize_loop_varibles(Point3D &A, Point3D &B, Point3D &C, int &x_left,
                                  int &x_right,
                                  int &y_down, int &y_up) const;

    static std::array<float, 4> calculate_baricentric_coeficients(Point3D A, Point3D B, Point3D C, float &ABC,
                                                                  float ABP, float BCP, float CAP);

    static bool show_mesh(float weight_a, float weight_b, float weight_c, int &r, int &g, int &b);

    std::array<float, 3> calculate_edge_functions(Point3D &A, Point3D &B, Point3D &C, Point3D &P);

    void universal_render(const std::array<Point3D, 3> &result_points, const std::array<Point3D, 3> &normal_vectors,
                          const std::array<Point2D, 3> &texture_vectors);

    void get_triangles_vectors(std::array<Point3D, 3> &result_points, std::array<Point3D, 3> &normal_vectors, std::array<Point2D, 3> &texture_vectors, const
                               Matrix4D &model_view_projection_matrix, int triangle_ind) const;

    void render_triangles(
        const Matrix4D &model_view_projection_matrix, int n_triangles);

    static float edge_function(Point3D a, Point3D b, Point3D c);

    // static void renderTriangle(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);
    // static void renderPolygons(GraphicsContext graphicsContext, Model mesh, int width, int height, Matrix4f modelViewProjectionMatrix);
};

#endif //RENDERENGINE_H
