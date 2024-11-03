#include "../headers/RenderEngine.h"
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
    // painter.fillRect(0, 0, width, height, Qt::white);
    DepthBuffer depth_buffer(width, height);
    const Matrix4D model_matrix = Matrix4D::create_identity_matrix();
    const Matrix4D view_matrix = camera.get_view_matrix();
    const Matrix4D projection_matrix = camera.get_projection_matrix();

    Matrix4D model_view_projection_matrix(model_matrix);
    model_view_projection_matrix.mul(view_matrix);
    model_view_projection_matrix.mul(projection_matrix);
    if (show_triangulation) {
        render_triangles(painter, mesh, width, height, model_view_projection_matrix, static_cast<int>(mesh.triangles.size()), depth_buffer);
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
        Point2D result_point = Point2D::vertexToPoint(
            Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height);
        result_points.emplace_back(result_point);
    }
}

void RenderEngine::add_triangles_vertex(const Model &mesh, const int &width, const int &height,
                                        const Matrix4D &model_view_projection_matrix, int triangle_ind,
                                        int n_vertices_in_polygon,
                                        std::vector<Point3D> &result_points, std::vector<Vector3D> &src_vectors, DepthBuffer &depth_buffer)
{
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_polygon; ++vertex_in_triangle_ind) {
        Vector3D vertex = mesh.vertices[mesh.triangles[triangle_ind].get_vertex_indices()[vertex_in_triangle_ind]];
        Vector3D vertex_vecmath(vertex.getX(), vertex.getY(), vertex.getZ());
        src_vectors.emplace_back(vertex_vecmath);
        Point3D result_point = Point3D::vertex_to_point(Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height, vertex.getZ());
        // Point2D result_point = Point2D::vertexToPoint(
        //     Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height);
        result_points.emplace_back(result_point);
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

void RenderEngine::rasterization(QPainter &painter, int point_count,
                                 const std::vector<Point3D> &result_points, const std::vector<Vector3D> &src_vectors, DepthBuffer &depth_buffer)
{
    auto edgeFunction = [](Point3D a, Point3D b, Point3D c)
    {
        return (b.getX() - a.getX()) * (c.getY() - a.getY()) - (b.getY() - a.getY()) * (c.getX() - a.getX());
    };
    float x_left = std::numeric_limits<float>::max();
    float x_right = std::numeric_limits<float>::min();
    float y_down = std::numeric_limits<float>::max();
    float y_up = std::numeric_limits<float>::min();
    //TODO Сделано неприавльно я  прохожу по всем точ
    for (auto element: result_points) {
        x_left = element.getX() < x_left ? element.getX() : x_left;
        x_right = element.getX() > x_right ? element.getX() : x_right;
        y_down = element.getY() < y_down ? element.getY() : y_down;
        y_up = element.getY() > y_up ? element.getY() : y_up;
    }
    Point3D A = result_points[0];
    Point3D B = result_points[1];
    Point3D C = result_points[2];
    Point3D P;
    for (int y = y_down; y < y_up; y++) {
        for (int x = x_left; x < x_right; x++) {
            P.set(x, y, 0);
            const float ABP = edgeFunction(A, B, P);
            const float BCP = edgeFunction(B, C, P);
            const float CAP = edgeFunction(C, A, P);
            if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
                // Если пиксель внутри треугольника, рассчитываем z-координату
                float z = (A.getZ() + B.getZ() + C.getZ()) / 3; // Пример - усредненная z-координата, замените на ваш алгоритм
                // Проверка глубины
                if (depth_buffer.get(x, y) > z) {
                    depth_buffer.set(x, y, z); // Обновляем глубину
                    painter.drawPoint(P.getX(), P.getY()); // Рисуем пиксель
                }
            }
        }
    }
    // std::sort(result_points.begin(), result_points.end());
    // float x_left = result_points[2].getX();
    // float x_right = result_points[0].getX();
    // float y_0 = result_points[2].getY(), y_1 = result_points[1].getY(), y_2 = result_points[0].getY();
    // for(y_0; y_0 < y_1; y_0++) {
    //     for(x_left; x_left < x_right; x_left++) {
    //         // if()
    //     }
    // }
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
                                    const Matrix4D &model_view_projection_matrix, int n_triangles, DepthBuffer &depth_buffer)
{
    painter.setPen(QColor(10, 10, 10));

    for (int triangle_ind = 0; triangle_ind < n_triangles; ++triangle_ind) {
        const int n_vertices_in_triangle = static_cast<int>(mesh.triangles[triangle_ind].get_vertex_indices().size());
        // std::vector<Point2D> result_points;
        std::vector<Point3D> result_points;
        std::vector<Vector3D> src_vectors;

        add_triangles_vertex(mesh, width, height, model_view_projection_matrix, triangle_ind, n_vertices_in_triangle,
                             result_points, src_vectors, depth_buffer);
        // Point3D A = result_points[0];
        // Point3D B = result_points[1];
        // Point3D C = result_points[2];
        // Vector3D AB = {B.getX() - A.getX(), B.getY() - A.getY(), B.getZ() - A.getZ()};
        // Vector3D AC = {C.getX() - A.getX(), C.getY() - A.getY(), C.getZ() - A.getZ()};
        // Vector3D n = Vector3D::cross(AB, AC);
        // float z = A.getZ() - n.getX()*(x - A.getX())/n.getZ() - n.getY()*(y - A.getY())/n.getZ();

        // draw_points(painter, n_vertices_in_triangle, result_points);

        rasterization(painter, n_vertices_in_triangle, result_points, src_vectors, depth_buffer);
    }
}


//         // First of all, initialize the depth of each pixel.
// d(i, j) = infinite // Max length
//
// // Initialize the color value for each pixel to the background color
// c(i, j) = background color
//
// // For each polygon, do the following steps :
// for (each pixel in polygon's projection)
// {
//     // Find depth i.e, z of polygon
//     //   at (x, y) corresponding to pixel (i, j)
//     if (z < d(i, j))
//     {
//         d(i, j) = z;
//         c(i, j) = color;
//     }
// }
