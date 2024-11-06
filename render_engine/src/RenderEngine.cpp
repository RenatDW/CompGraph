#include "../headers/RenderEngine.h"

#include <iostream>

#include "../headers/GraphicConveyor.h"
#include "../../forms/headers/mainwindow.h"
#include "../../math/headers/DepthBuffer.h"
#include "../../math/headers/Point2D.h"


void RenderEngine::render(const bool &show_triangulation)
{
    const Matrix4D model_matrix = Matrix4D::create_identity_matrix();
    const Matrix4D view_matrix = camera.get_view_matrix();
    const Matrix4D projection_matrix = camera.get_projection_matrix();

    Matrix4D model_view_projection_matrix(model_matrix);
    model_view_projection_matrix = model_view_projection_matrix.mul(view_matrix).mul(projection_matrix);

    if (show_triangulation) {
        render_triangles(model_view_projection_matrix, static_cast<int>(mesh.triangles.size()));
    } else {
        render_polygons(painter, mesh, width, height, model_view_projection_matrix,
                        static_cast<int>(mesh.polygons.size()));
    }
}

RenderEngine::RenderEngine(QPainter &painter, const Camera &camera, std::string &string, QColor color,
                           const Model &model, int width, int height): depth_buffer(width, height), painter(painter),
                                                                       camera(camera), mesh(model),
                                                                       width(width), height(height),
                                                                       fill_model_color(color), filename(string) {}

void RenderEngine::add_polygons_vertex(const Matrix4D &model_view_projection_matrix, const int polygon_ind,
                                       const int n_vertices_in_polygon,
                                       std::vector<Point2D> &result_points)
{
    for (int vertex_in_polygon_ind = 0; vertex_in_polygon_ind < n_vertices_in_polygon; ++vertex_in_polygon_ind) {
        Vector3D vertex = mesh.vertices[mesh.polygons[polygon_ind].get_vertex_indices()[vertex_in_polygon_ind]];
        Vector3D vertex_vecmath(vertex.getX(), vertex.getY(), vertex.getZ());
        Point2D result_point = Point2D::vertex_to_point(
            Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height);
        result_points.emplace_back(result_point);
    }
}

std::vector<Point3D> RenderEngine::get_triangles_vertex(const Matrix4D &model_view_projection_matrix, int triangle_ind,
                                                        int n_vertices_in_polygon)
{
    std::vector<Point3D> result_points;
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_polygon; ++vertex_in_triangle_ind) {
        Vector3D vertex = mesh.vertices[mesh.triangles[triangle_ind].get_vertex_indices()[vertex_in_triangle_ind]];
        Vector3D vertex_vecmath(vertex.getX(), vertex.getY(), vertex.getZ());
        Point3D result_point = Point3D::vertex_to_point(
            Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height,
            vertex.getZ());
        result_points.emplace_back(result_point);
    }
    return result_points;
}

std::vector<Point3D> RenderEngine::get_triangle_normal_vertex(int triangle_ind, int n_vertices_in_polygon)
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

std::vector<Point2D> RenderEngine::get_triangle_texture_vertex(int triangle_ind, int n_vertices_in_polygon)
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

float RenderEngine::edgeFunction(Point3D a, Point3D b, Point3D c)
{
    return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
}

void RenderEngine::render_polygons(QPainter &painter, const Model &mesh, const int &width, const int &height,
                                   const Matrix4D &model_view_projection_matrix, const int n_polygons)
{
    for (int polygon_ind = 0; polygon_ind < n_polygons; ++polygon_ind) {
        const int n_vertices_in_polygon = static_cast<int>(mesh.polygons[polygon_ind].get_vertex_indices().size());
        std::vector<Point2D> result_points;
        add_polygons_vertex(model_view_projection_matrix, polygon_ind, n_vertices_in_polygon, result_points);
        draw_points(painter, n_vertices_in_polygon, result_points);
    }
}

void RenderEngine::initialize_loop_varibles(Point3D &A, Point3D &B, Point3D &C,
                                            int &x_left, int &x_right, int &y_down, int &y_up)
{
    x_left = static_cast<int>(std::min({
        A.getX(), B.getX(), C.getX(), static_cast<float>(depth_buffer.getWidth())
    }));
    x_right = static_cast<int>(std::max({A.getX(), B.getX(), C.getX(), 0.0f})) + 1;
    y_down = static_cast<int>(std::min({
        A.getY(), B.getY(), C.getY(), static_cast<float>(depth_buffer.getHeight())
    }));
    y_up = static_cast<int>(std::max({A.getY(), B.getY(), C.getY(), 0.0f})) + 1;
}

float RenderEngine::calculate_parametr_of_illumination(const std::vector<Point3D> &normal_vectors, Camera &camera,
                                                       Point3D P,
                                                       const float weightA, const float weightB, const float weightC)
{
    Vector3D normal_A = Point3D::point_to_vector(normal_vectors[0]).normalize(), normal_B =
            Point3D::point_to_vector(normal_vectors[1]).normalize(), normal_C = Point3D::point_to_vector(
                normal_vectors[2]).
            normalize();
    Vector3D vn = (normal_A * weightA + normal_B * weightB + normal_C * weightC).normalize();
    Vector3D cam{camera.getPosition().getX(), camera.getPosition().getY(), camera.getPosition().getZ()};
    Vector3D ray = (cam - Vector3D{P.getX(), P.getY(), P.getZ()}).normalize();
    ray = ray.normalize();
    float l = -(ray * vn);
    if (l < 0.0f) {
        l = 0.0f;
    }
    return l;
}

QColor RenderEngine::get_suitable_pixel(const std::vector<Point2D> &texture_vectors, const QImage &image,
                                        const float &weightA,
                                        const float &weightB, const float &weightC)
{
    float u = weightA * texture_vectors[0].getX() + weightB * texture_vectors[1].getX() + weightC * texture_vectors[2].
              getX();
    float v = weightA * texture_vectors[0].getY() + weightB * texture_vectors[1].getY() + weightC * texture_vectors[2].
              getY();
    int texX = static_cast<int>(static_cast<float>(image.width() - 1) - u * static_cast<float>(image.width() - 1));
    int texY = static_cast<int>(static_cast<float>(image.height() - 1) - v * static_cast<float>(image.height() - 1));
    texX = std::clamp(texX, 0, image.width() - 1);
    texY = std::clamp(texY, 0, image.height() - 1);

    return image.pixel(texX, texY);
}

void RenderEngine::texturation(const std::vector<Point2D> &texture_vectors, const QImage &image, const float weightA,
                               const float weightB, const float weightC, int &r, int &g, int &b)
{
    if (texture_vectors.empty() || image.isNull()) {
        return;
    }
    QColor texColor = get_suitable_pixel(texture_vectors, image, weightA, weightB, weightC);
    r = texColor.red(), g = texColor.green(), b = texColor.blue();
}

void RenderEngine::illumination(const std::vector<Point3D> &normal_vectors, const Point3D &P,
                                const float weightA, const float weightB, const float weightC, int &r, int &g, int &b)
{
    if (normal_vectors.empty()) {
        return;
    }
    float k = 0.4;
    float l = calculate_parametr_of_illumination(normal_vectors, camera, P, weightA, weightB, weightC);
    r *= (1 - k + k * l), g *= (1 - k + k * l), b *= (1 - k + k * l);
}

void RenderEngine::universal_render(const std::vector<Point3D> &result_points,
                                    const std::vector<Point3D> &normal_vectors,
                                    const std::vector<Point2D> &texture_vectors)
{
    QImage image(filename.data());
    Point3D A = result_points[0], B = result_points[1], C = result_points[2], P;

    int x_left, x_right, y_down, y_up;
    initialize_loop_varibles(A, B, C, x_left, x_right, y_down, y_up);

    for (int y = y_down; y < y_up; y++) {
        for (int x = x_left; x < x_right; x++) {
            if (x < 0 || x > depth_buffer.getWidth() || y > depth_buffer.getHeight() || y < 0) {
                break;
            }
            P.set(static_cast<float>(x), static_cast<float>(y), 0);
            const float ABP = edgeFunction(A, B, P), BCP = edgeFunction(B, C, P), CAP = edgeFunction(C, A, P);
            if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
                const float ABC = edgeFunction(A, B, C);
                const float weightA = BCP / ABC, weightB = CAP / ABC, weightC = ABP / ABC;

                int z = static_cast<int>(A.getZ() * weightA + B.getZ() * weightB + C.getZ() * weightC);

                if (depth_buffer.get(x, y) > static_cast<float>(z)) {
                    int r = fill_model_color.red(), g = fill_model_color.green(), b = fill_model_color.blue();
                    texturation(texture_vectors, image, weightA, weightB, weightC, r, g, b);
                    //TODO освещение почему-то не динамичное...
                    illumination(normal_vectors, P, weightA, weightB, weightC, r, g, b);

                    painter.setPen(QColor(r, g, b));
                    depth_buffer.set(x, y, z);
                    painter.drawPoint(P.getX(), P.getY());
                }
            }
        }
    }
}

void RenderEngine::render_triangles(const Matrix4D &model_view_projection_matrix, int n_triangles)
{
    for (int triangle_ind = 0; triangle_ind < n_triangles; ++triangle_ind) {
        const int n_vertices_in_triangle = static_cast<int>(mesh.triangles[triangle_ind].get_vertex_indices().size());
        std::vector<Point3D> result_points = get_triangles_vertex(model_view_projection_matrix, triangle_ind,
                                                                  n_vertices_in_triangle);
        std::vector<Point3D> normal_vectors = get_triangle_normal_vertex(triangle_ind, n_vertices_in_triangle);
        std::vector<Point2D> texture_vectors = get_triangle_texture_vertex(triangle_ind, n_vertices_in_triangle);

        universal_render(result_points, normal_vectors, texture_vectors);
    }
    painter.end();
}
