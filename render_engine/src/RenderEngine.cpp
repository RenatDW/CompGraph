#include "../headers/RenderEngine.h"

#include <iostream>

#include "../headers/GraphicConveyor.h"
#include "../../forms/headers/mainwindow.h"
#include "../../math/headers/DepthBuffer.h"
#include "../../math/headers/Point2D.h"

void RenderEngine::render(QPainter &painter,
                          Camera &camera,
                          const std::string &filename,
                          const QColor &color,
                          const Model &mesh,
                          const int &width,
                          const int &height,
                          const bool &show_triangulation)
{
    DepthBuffer depth_buffer(width, height);
    const Matrix4D model_matrix = Matrix4D::create_identity_matrix();
    const Matrix4D view_matrix = camera.get_view_matrix();
    const Matrix4D projection_matrix = camera.get_projection_matrix();

    Matrix4D model_view_projection_matrix(model_matrix);
    model_view_projection_matrix.mul(view_matrix);
    model_view_projection_matrix.mul(projection_matrix);
    if (show_triangulation) {
        render_triangles(painter, mesh, width, height,
                         model_view_projection_matrix, color, static_cast<int>(mesh.triangles.size()), depth_buffer,
                         filename, camera);
    } else {
        render_polygons(painter, mesh, width, height, model_view_projection_matrix,
                        static_cast<int>(mesh.polygons.size()));
    }
}

void RenderEngine::add_polygons_vertex(const Model &mesh, const int &width, const int &height,
                                       const Matrix4D &model_view_projection_matrix, const int polygon_ind,
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

void RenderEngine::add_triangles_vertex(const Model &mesh, const int &width, const int &height,
                                        const Matrix4D &model_view_projection_matrix, int triangle_ind,
                                        int n_vertices_in_polygon,
                                        std::vector<Point3D> &result_points, std::vector<Point3D> &world_vertex)
{
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_polygon; ++vertex_in_triangle_ind) {
        Vector3D vertex = mesh.vertices[mesh.triangles[triangle_ind].get_vertex_indices()[vertex_in_triangle_ind]];
        Vector3D vertex_vecmath(vertex.getX(), vertex.getY(), vertex.getZ());
        world_vertex.emplace_back(vertex.getX(), vertex.getY(), vertex.getZ());
        Point3D result_point = Point3D::vertex_to_point(
            Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height,
            vertex.getZ());
        result_points.emplace_back(result_point);
    }
}

void RenderEngine::add_normal_vertex(const Model &mesh, int triangle_ind, int n_vertices_in_polygon,
                                     std::vector<Point3D> &normal_points)
{
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_polygon; ++vertex_in_triangle_ind) {
        int texture_vertex_ind = mesh.triangles[triangle_ind].get_normal_indices()[vertex_in_triangle_ind];
        Point3D result_point = {
            mesh.normals[texture_vertex_ind].getX(), mesh.normals[texture_vertex_ind].getY(),
            mesh.normals[texture_vertex_ind].getZ()
        };
        normal_points.emplace_back(result_point);
    }
}

void RenderEngine::add_texture_vertex(const Model &mesh, int triangle_ind, int n_vertices_in_polygon,
                                      std::vector<Point2D> &texture_vectors)
{
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_polygon; ++vertex_in_triangle_ind) {
        int texture_vertex_ind = mesh.triangles[triangle_ind].get_texture_indices()[vertex_in_triangle_ind];
        Point2D result_point = {
            mesh.textureVertices[texture_vertex_ind].getX(), mesh.textureVertices[texture_vertex_ind].getY()
        };
        texture_vectors.emplace_back(result_point);
    }
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
        add_polygons_vertex(mesh, width, height, model_view_projection_matrix, polygon_ind, n_vertices_in_polygon,
                            result_points);
        draw_points(painter, n_vertices_in_polygon, result_points);
    }
}

void RenderEngine::initialize_loop_varibles(const DepthBuffer &depth_buffer, Point3D &A, Point3D &B, Point3D &C,
                                            int &x_left, int &x_right, int &y_down, int &y_up)
{
    x_left = static_cast<int>(std::min({
        A.getX(), B.getX(), C.getX(), static_cast<float>(depth_buffer.getWidth() - 1)
    })) + 1;
    x_right = static_cast<int>(std::max({A.getX(), B.getX(), C.getX(), 0.0f}));
    y_down = static_cast<int>(std::min({
        A.getY(), B.getY(), C.getY(), static_cast<float>(depth_buffer.getHeight() - 1)
    })) + 1;
    y_up = static_cast<int>(std::max({A.getY(), B.getY(), C.getY(), 0.0f}));
}

float RenderEngine::calculate_parametr_of_illumination(const std::vector<Point3D> &normal_vectors, Camera &camera, Point3D P,
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

QColor RenderEngine::do_work(const std::vector<Point2D> &texture_vectors, const QImage &image, const float &weightA,
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

void RenderEngine::universal_render(QPainter &painter, const std::vector<Point3D> &result_points,
                                    const std::vector<Point3D> &normal_vectors,
                                    const std::vector<Point2D> &texture_vectors, DepthBuffer &depth_buffer,
                                    const std::string &filename, const QColor &fill_color,
                                    Camera &camera)
{
    QImage image((filename.data()));
    Point3D A = result_points[0], B = result_points[1], C = result_points[2], P;

    int x_left, x_right, y_down, y_up;
    initialize_loop_varibles(depth_buffer, A, B, C, x_left, x_right, y_down, y_up);

    for (int y = y_down - 1; y < y_up + 1; y++) {
        for (int x = x_left - 1; x < x_right + 1; x++) {
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
                    int r = fill_color.red(), g = fill_color.green(), b = fill_color.blue();
                    if (!texture_vectors.empty()) {
                        QColor texColor = do_work(texture_vectors, image, weightA, weightB, weightC);
                        r = texColor.red(), g = texColor.green(), b = texColor.blue();
                    }

                    if (!normal_vectors.empty()) {
                        float k = 0.4;
                        float l = calculate_parametr_of_illumination(normal_vectors, camera, P, weightA, weightB,
                                                                     weightC);
                        r *= (1 - k + k * l), g *= (1 - k + k * l), b *= (1 - k + k * l);
                    }
                    painter.setPen(QColor(r, g, b));
                    depth_buffer.set(x, y, z);
                    painter.drawPoint(P.getX(), P.getY());
                }
            }
        }
    }
}

void RenderEngine::render_triangles(QPainter &painter, const Model &mesh,
                                    const int &width, const int &height,
                                    const Matrix4D &model_view_projection_matrix, const QColor &fill_color, int n_triangles,
                                    DepthBuffer &depth_buffer, const std::string &filename, Camera &camera)
{
    for (int triangle_ind = 0; triangle_ind < n_triangles; ++triangle_ind) {
        const int n_vertices_in_triangle = static_cast<int>(mesh.triangles[triangle_ind].get_vertex_indices().size());
        std::vector<Point3D> result_points;
        std::vector<Point3D> normal_vectors;
        std::vector<Point2D> texture_vectors;
        std::vector<Point3D> world_vector;
        add_triangles_vertex(mesh, width, height, model_view_projection_matrix, triangle_ind, n_vertices_in_triangle,
                             result_points, world_vector);
        // add_texture_vertex(mesh, triangle_ind, n_vertices_in_triangle, texture_vectors);
        add_normal_vertex(mesh, triangle_ind, n_vertices_in_triangle, normal_vectors);

        universal_render(painter, result_points, normal_vectors, texture_vectors, depth_buffer, filename, fill_color,
                         camera);
    }
    painter.end();
}
