#include "../headers/RenderEngine.h"

#include <iostream>

#include "../headers/GraphicConveyor.h"
#include "../../forms/headers/mainwindow.h"
#include "../../math/headers/DepthBuffer.h"
#include "../../math/headers/Point2D.h"
#include "../headers/Illumination.h"
#include "../headers/Renderable.h"
#include "../headers/Mesh.h"
#include "../headers/Texturezation.h"
#include "../../math/headers/MathCast.h"

void RenderEngine::render(const std::vector<TypeOfRender> &show_triangulation)
{
    const Matrix4D model_matrix = Matrix4D::create_identity_matrix();
    const Matrix4D view_matrix = camera.get_view_matrix();
    const Matrix4D projection_matrix = camera.get_projection_matrix();

    Matrix4D model_view_projection_matrix(model_matrix);
    model_view_projection_matrix = model_view_projection_matrix * view_matrix * projection_matrix;

    // if (show_triangulation) {
    render_triangles(model_view_projection_matrix, static_cast<int>(mesh.triangles.size()));
    // } else {
    //     render_polygons(painter, mesh, width, height, model_view_projection_matrix,
    //                     static_cast<int>(mesh.polygons.size()));
    // }
}

RenderEngine::RenderEngine(QPainter &painter, Camera &camera, std::string &string, QColor &color,
                           Model &model, int width, int height,  bool show_mesh_param, bool show_texture_param, bool show_illumination_param): depth_buffer(width, height), painter(painter),
                                                                 mesh(model), camera(camera), filename(string),
                                                                 width(width), height(height),
                                                                 show_texture_param(show_texture_param),
                                                                 show_mesh_param(show_mesh_param),
                                                                 show_illumination_param(show_illumination_param),
                                                                 fill_model_color(color) {}

void RenderEngine::add_polygons_vertex(const Matrix4D &model_view_projection_matrix, const int polygon_ind,
                                       const int n_vertices_in_polygon,
                                       std::vector<Point2D> &result_points) const
{
    for (int vertex_in_polygon_ind = 0; vertex_in_polygon_ind < n_vertices_in_polygon; ++vertex_in_polygon_ind) {
        Vector3D vertex = mesh.vertices[mesh.polygons[polygon_ind].get_vertex_indices()[vertex_in_polygon_ind]];
        Vector3D vertex_vecmath(vertex.getX(), vertex.getY(), vertex.getZ());
        Point2D result_point = MathCast::to_Point2D(
            Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height);
        result_points.emplace_back(result_point);
    }
}

std::vector<Point3D> RenderEngine::get_triangles_vertex(const Matrix4D &model_view_projection_matrix, int triangle_ind,
                                                        int n_vertices_in_polygon) const
{
    std::vector<Point3D> result_points;
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_polygon; ++vertex_in_triangle_ind) {
        Vector3D vertex = mesh.vertices[mesh.triangles[triangle_ind].get_vertex_indices()[vertex_in_triangle_ind]];
        Vector3D vertex_vecmath(vertex.getX(), vertex.getY(), vertex.getZ());
        Point3D result_point = MathCast::to_Point3D(
            Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height);
        result_points.emplace_back(result_point);
    }
    return result_points;
}

std::vector<Point3D> RenderEngine::get_triangle_normal_vertex(int triangle_ind, int n_vertices_in_polygon) const
{
    std::vector<Point3D> normal_points;
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_polygon; ++vertex_in_triangle_ind) {
        int texture_vertex_ind = mesh.triangles[triangle_ind].get_normal_indices()[vertex_in_triangle_ind];
        Point3D result_point = {
            mesh.normals[texture_vertex_ind].getX(), mesh.normals[texture_vertex_ind].getY(),
            mesh.normals[texture_vertex_ind].getZ()
        };
        normal_points.emplace_back(result_point);
    }
    return normal_points;
}

std::vector<Point2D> RenderEngine::get_triangle_texture_vertex(int triangle_ind, int n_vertices_in_polygon) const
{
    std::vector<Point2D> texture_vectors;
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_polygon; ++vertex_in_triangle_ind) {
        int texture_vertex_ind = mesh.triangles[triangle_ind].get_texture_indices()[vertex_in_triangle_ind];
        Point2D result_point = {
            mesh.textureVertices[texture_vertex_ind].getX(), mesh.textureVertices[texture_vertex_ind].getY()
        };
        texture_vectors.emplace_back(result_point);
    }
    return texture_vectors;
}

void RenderEngine::draw_points(QPainter &painter, const int point_count,
                               const std::vector<Point2D> &result_points)
{
    for (int point_ind = 1; point_ind < point_count; ++
         point_ind) {
        painter.drawLine(
            static_cast<int>(result_points[point_ind - 1].getX()),
            static_cast<int>(result_points[point_ind - 1].getY()),
            static_cast<int>(result_points[point_ind].getX()),
            static_cast<int>(result_points[point_ind].getY()));
    }

    if (point_count > 0)
        painter.drawLine(
            static_cast<int>(result_points[point_count - 1].getX()),
            static_cast<int>(result_points[point_count - 1].getY()),
            static_cast<int>(result_points[0].getX()),
            static_cast<int>(result_points[0].getY()));
}

float RenderEngine::edge_function(Point3D a, Point3D b, Point3D c)
{
    return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
}

void RenderEngine::render_polygons(QPainter &painter, const Model &mesh, const int &width, const int &height,
                                   const Matrix4D &model_view_projection_matrix, const int n_polygons) const
{
    for (int polygon_ind = 0; polygon_ind < n_polygons; ++polygon_ind) {
        const int n_vertices_in_polygon = static_cast<int>(mesh.polygons[polygon_ind].get_vertex_indices().size());
        std::vector<Point2D> result_points;
        add_polygons_vertex(model_view_projection_matrix, polygon_ind, n_vertices_in_polygon, result_points);
        draw_points(painter, n_vertices_in_polygon, result_points);
    }
}

void RenderEngine::initialize_loop_varibles(Point3D &A, Point3D &B, Point3D &C,
                                            int &x_left, int &x_right, int &y_down, int &y_up) const
{
    x_left = static_cast<int>(std::min({
        A.getX(), B.getX(), C.getX(), static_cast<float>(depth_buffer.getWidth())
    }));
    x_right = static_cast<int>(std::max({A.getX(), B.getX(), C.getX(), 0.0f}));
    y_down = static_cast<int>(std::min({
        A.getY(), B.getY(), C.getY(), static_cast<float>(depth_buffer.getHeight())
    }));
    y_up = static_cast<int>(std::max({A.getY(), B.getY(), C.getY(), 0.0f}));
}

void RenderEngine::calculate_baricentric_coeficients(Point3D A, Point3D B, Point3D C, float ABP, float BCP, float CAP,
                                                     float &weight_a, float &weight_b, float &weight_c, float &z)
{
    const float ABC = edge_function(A, B, C);
    weight_a = BCP / ABC;
    weight_b = CAP / ABC;
    weight_c = ABP / ABC;

    z = (A.getZ() * weight_a + B.getZ() * weight_b + C.getZ() * weight_c);
}


bool RenderEngine::show_mesh(float weight_a, float weight_b, float weight_c, int r, int g, int b)
{
    if (Mesh::show_mesh(weight_a, weight_b, weight_c, r, g, b)) return true;
    painter.setPen(QColor(1, 1, 1));
    return false;
}

void RenderEngine::universal_render(const std::vector<Point3D> &result_points,
                                    const std::vector<Point3D> &normal_vectors,
                                    const std::vector<Point2D> &texture_vectors)
{
    QImage image = (!filename.empty()) ? QImage(filename.data()) : QImage();
    Point3D A = result_points[0], B = result_points[1], C = result_points[2], P;
    int x_left, x_right, y_down, y_up;
    initialize_loop_varibles(A, B, C, x_left, x_right, y_down, y_up);

    for (int y = y_down; y < y_up + 1; y++) {
        for (int x = x_left; x < x_right + 1; x++) {
            if (x < 0 || x > depth_buffer.getWidth() || y > depth_buffer.getHeight() || y < 0) continue;
            P.set(static_cast<float>(x), static_cast<float>(y), 0);
            float ABP = edge_function(A, B, P), BCP = edge_function(B, C, P), CAP = edge_function(C, A, P);
            if (ABP < 0 || BCP < 0 || CAP < 0) continue;

            float weight_a, weight_b, weight_c, z;
            calculate_baricentric_coeficients(A, B, C, ABP, BCP, CAP, weight_a, weight_b, weight_c, z);

            if (depth_buffer.get(x, y) <= z) continue;

            //TODO освещение почему-то не динамичное...
            int r = fill_model_color.red(), g = fill_model_color.green(), b = fill_model_color.blue();


            //TODO не все я просчитал, увелечение по x на 1 не соответсвует увелечению y по kx + b, в локальных хоординатах
            // Mesh::show_mesh_by_points(painter, result_points[0], result_points[1]);
            // Mesh::show_mesh_by_points(painter, result_points[1], result_points[2]);
            // Mesh::show_mesh_by_points(painter, result_points[2], result_points[0]);
            if(show_mesh_param) {
                if (show_mesh(weight_a, weight_b, weight_c, r, g, b)) continue;
            }
            if(show_illumination_param) {
                Illumination::illumination(normal_vectors, P, camera, weight_a, weight_b, weight_c, r, g, b);
            }
            if(show_texture_param) {
                Texturezation::texturation(texture_vectors, image, weight_a, weight_b, weight_c, r, g, b);
            }

            painter.setPen(QColor(r, g, b));
            depth_buffer.set(x, y, z);
            painter.drawPoint(P.getX(), P.getY());
        }
    }
}

void RenderEngine::render_triangles(const Matrix4D &model_view_projection_matrix, int n_triangles)
{
    for (int triangle_ind = 0; triangle_ind < n_triangles; ++triangle_ind) {
        const int n_vertices_in_triangle = static_cast<int>(mesh.triangles[triangle_ind].get_vertex_indices().
            size());
        std::vector<Point3D> result_points = get_triangles_vertex(model_view_projection_matrix, triangle_ind,
                                                                  n_vertices_in_triangle);
        std::vector<Point3D> normal_vectors = get_triangle_normal_vertex(triangle_ind, n_vertices_in_triangle);
        std::vector<Point2D> texture_vectors = get_triangle_texture_vertex(triangle_ind, n_vertices_in_triangle);

        universal_render(result_points, normal_vectors, texture_vectors);
    }
    painter.end();
}
