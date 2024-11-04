#include "../headers/RenderEngine.h"

#include <iostream>

#include "../headers/GraphicConveyor.h"
#include "../../forms/headers/mainwindow.h"
#include "../../math/headers/DepthBuffer.h"
#include "../../math/headers/Point2D.h"

void RenderEngine::render(QPainter &painter,
                          Camera &camera,
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
        render_triangles(painter, mesh, width, height, model_view_projection_matrix,
                         static_cast<int>(mesh.triangles.size()), depth_buffer);
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
                                        std::vector<Point3D> &result_points)
{
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_polygon; ++vertex_in_triangle_ind) {
        Vector3D vertex = mesh.vertices[mesh.triangles[triangle_ind].get_vertex_indices()[vertex_in_triangle_ind]];
        Vector3D vertex_vecmath(vertex.getX(), vertex.getY(), vertex.getZ());
        Point3D result_point = Point3D::vertex_to_point(
            Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height,
            vertex.getZ());
        result_points.emplace_back(result_point);
    }
}

void RenderEngine::add_texture_vertex(const Model &mesh, const int &width, const int &height, int triangle_ind,
                                      int n_vertices_in_polygon,
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

void RenderEngine::rasterization(QPainter &painter,
                                 const std::vector<Point3D> &result_points, DepthBuffer &depth_buffer)
{
    auto edgeFunction = [](Point3D a, Point3D b, Point3D c)
    {
        return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
    };


    Point3D A = result_points[0];
    Point3D B = result_points[1];
    Point3D C = result_points[2];
    Point3D P;

    const int x_left = static_cast<int>(std::min({
        A.getX(), B.getX(), C.getX(), static_cast<float>(depth_buffer.getWidth())
    }));
    const int x_right = static_cast<int>(std::max({A.getX(), B.getX(), C.getX(), 0.0f}));
    const int y_down = static_cast<int>(std::min({
        A.getY(), B.getY(), C.getY(), static_cast<float>(depth_buffer.getHeight())
    }));
    const int y_up = static_cast<int>(std::max({A.getY(), B.getY(), C.getY(), 0.0f}));

    for (int y = y_down; y < y_up; y++) {
        for (int x = x_left; x < x_right; x++) {
            if (x < 0 || x > depth_buffer.getWidth() || y > depth_buffer.getHeight() || y < 0) {
                break;
            }
            P.set(x, y, 0);
            const float ABP = edgeFunction(A, B, P);
            const float BCP = edgeFunction(B, C, P);
            const float CAP = edgeFunction(C, A, P);

            if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
                const float ABC = edgeFunction(A, B, C);
                const float weightA = BCP / ABC;
                const float weightB = CAP / ABC;
                const float weightC = ABP / ABC;
                int z = A.getZ() * weightA + B.getZ() * weightB + C.getZ() * weightC;
                painter.setPen(QColor(-z * 10, -z * 10, -z * 10));
                if (depth_buffer.get(x, y) > z) {
                    depth_buffer.set(x, y, z);
                    painter.drawPoint(P.getX(), P.getY());
                }
            }
        }
    }
}

void RenderEngine::show_mesh(QPainter &painter, std::vector<Point3D> &result_points, DepthBuffer &depth_buffer)
{
    auto edgeFunction = [](Point3D a, Point3D b, Point3D c)
    {
        return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
    };

    for (int i = 1; i < result_points.size(); ++i) {
        RenderEngine::draw_line(painter, result_points[i - 1], result_points[i]);
    }
    if (result_points.size() > 0) {
        RenderEngine::draw_line(painter, result_points[result_points.size() - 1], result_points[0]);
    }

    // float x_left = std::min({A.getX(), B.getX(), C.getX()});
    // float x_right = std::max({A.getX(), B.getX(), C.getX()});
    // float y_down = std::min({A.getY(), B.getY(), C.getY()});
    // float y_up = std::max({A.getY(), B.getY(), C.getY()});

    // for (int y = y_down; y < y_up; y++) {
    //     for (int x = x_left; x < x_right; x++) {
    //         if (x < 0 || x * y > depth_buffer.size() || y < 0) {
    //             break;
    //         }
    //         P.set(x, y, 0);
    //         const float ABC = edgeFunction(A, B, C);
    //         const float ABP = edgeFunction(A, B, P);
    //         const float BCP = edgeFunction(B, C, P);
    //         const float CAP = edgeFunction(C, A, P);
    //         const float weightA = BCP / ABC;
    //         const float weightB = CAP / ABC;
    //         const float weightC = ABP / ABC;
    //         if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
    //             float z = A.getZ() * weightA + B.getZ() * weightB + C.getZ() * weightC;
    //             painter.setPen(QColor(-z * 10, -z * 10, -z * 10));
    //             if (depth_buffer.get(x, y) > z) {
    //                 depth_buffer.set(x, y, z);
    //                 painter.drawPoint(P.getX(), P.getY());
    //             }
    //         }
    //     }
    // }
}

void RenderEngine::render_texture(QPainter &painter, std::vector<Point3D> &result_points, DepthBuffer &depth_buffer,
                                  std::vector<Point2D> &textures)
{
    auto edgeFunction = [](Point3D a, Point3D b, Point3D c)
    {
        return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
    };
    QImage image("/Users/renat/CLionProjects/3DModels/CaracalCube/caracal_texture.png");

    Point3D A = result_points[0];
    Point3D B = result_points[1];
    Point3D C = result_points[2];
    Point3D P;

    const int x_left = static_cast<int>(std::min({
        A.getX(), B.getX(), C.getX(), static_cast<float>(depth_buffer.getWidth())
    }));
    const int x_right = static_cast<int>(std::max({A.getX(), B.getX(), C.getX(), 0.0f}));
    const int y_down = static_cast<int>(std::min({
        A.getY(), B.getY(), C.getY(), static_cast<float>(depth_buffer.getHeight())
    }));
    const int y_up = static_cast<int>(std::max({A.getY(), B.getY(), C.getY(), 0.0f}));

    for (int y = y_down; y < y_up; y++) {
        for (int x = x_left; x < x_right; x++) {
            if (x < 0 || x > depth_buffer.getWidth() || y > depth_buffer.getHeight() || y < 0) {
                break;
            }
            P.set(x, y, 0);
            const float ABP = edgeFunction(A, B, P);
            const float BCP = edgeFunction(B, C, P);
            const float CAP = edgeFunction(C, A, P);

            if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
                const float ABC = edgeFunction(A, B, C);
                const float weightA = BCP / ABC;
                const float weightB = CAP / ABC;
                const float weightC = ABP / ABC;

                float u = weightA * (textures[0].getX() ) + (weightB * textures[1].getX()) + weightC * (textures[2].getX());
                float v = weightA * (textures[0].getY()) + (weightB * textures[1].getY()) + weightC * (textures[2].getY());
                float z = A.getZ() * weightA + B.getZ() * weightB + C.getZ() * weightC;

                if (depth_buffer.get(x, y) > z) {
                    int texX = static_cast<int>((image.width() - 1) - u * (image.width() - 1));
                    int texY = static_cast<int>((image.height() - 1) - v * (image.height() - 1));
                    // std::cout << "texX: " << texX << " texY: " << texY << std::endl;
                    texX = std::clamp(texX, 0, image.width() - 1);
                    texY = std::clamp(texY, 0, image.height() - 1);

                    QColor texColor = image.pixel(texX, texY);
                    painter.setPen(texColor);
                    // painter.setPen(QColor(255* weightA ,255 * weightB, 255 * weightC));
                    painter.drawPoint(x, y);
                    depth_buffer.set(x, y, z);
                }
            }
        }
    }
}

void RenderEngine::draw_line(QPainter &painter, Point3D &A, Point3D &B)
{
    // painter.setPen(QColor(0, 0, 0));
    float x1 = B.getX();
    float y1 = B.getY();
    float x0 = A.getX();
    float y0 = A.getY();

    float dx = abs(x1 - x0);
    float sx = x0 < x1 ? 1 : -1;
    float dy = -abs(y1 - y0);
    float sy = y0 < y1 ? 1 : -1;
    float error = dx + dy;

    while (true) {
        painter.drawPoint(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        float e2 = 2 * error;
        if (e2 >= dy) {
            error += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            error += dx;
            y0 += sy;
        }
    }
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

void RenderEngine::render_triangles(QPainter &painter, const Model &mesh, const int &width, const int &height,
                                    const Matrix4D &model_view_projection_matrix, int n_triangles,
                                    DepthBuffer &depth_buffer)
{
    for (int triangle_ind = 0; triangle_ind < n_triangles; ++triangle_ind) {
        const int n_vertices_in_triangle = static_cast<int>(mesh.triangles[triangle_ind].get_vertex_indices().size());
        std::vector<Point3D> result_points;
        std::vector<Point2D> texture_vectors;
        add_triangles_vertex(mesh, width, height, model_view_projection_matrix, triangle_ind, n_vertices_in_triangle,
                             result_points);
        add_texture_vertex(mesh, width, height, triangle_ind, n_vertices_in_triangle, texture_vectors);
        render_texture(painter, result_points, depth_buffer, texture_vectors);
        // rasterization(painter, result_points, depth_buffer);
        // show_mesh(painter, result_points, depth_buffer);
    }
    painter.end();
}
