#include "../headers/RenderEngine.h"
#include "../headers/GraphicConveyor.h"
#include "../headers/mainwindow.h"
#include "../headers/Point2D.h"

void RenderEngine::render(QPainter &painter,
                          Camera &camera,
                          const Model &mesh,
                          const int &width,
                          const int &height,
                          const bool &show_triangulation)
{
    const Matrix4D model_matrix = Matrix4D::create_identity_matrix();
    const Matrix4D view_matrix = camera.get_view_matrix();
    const Matrix4D projection_matrix = camera.get_projection_matrix();

    Matrix4D model_view_projection_matrix(model_matrix);
    model_view_projection_matrix.mul(view_matrix);
    model_view_projection_matrix.mul(projection_matrix);

    const int nPolygons = static_cast<int>(mesh.polygons.size());
    render_polygons(painter, mesh, width, height, model_view_projection_matrix, nPolygons);
}

void RenderEngine::add_polygons_vertex(const Model &mesh, const int &width, const int &height,
                                       const Matrix4D &model_view_projection_matrix, int polygon_ind,
                                       const int n_vertices_in_polygon,
                                       std::vector<Point2D> &result_points)
{
    for (int vertex_in_polygon_ind = 0; vertex_in_polygon_ind < n_vertices_in_polygon; ++vertex_in_polygon_ind) {
        //Получаем ссылку на вектор вершины с координатами, проходясь по конкретному полигону и получая номер конкретного вектора
        Vector3D vertex = mesh.vertices[mesh.polygons[polygon_ind].get_vertex_indices()[vertex_in_polygon_ind]];
        //Переводим самописный вектор в библиотечный вектор
        Vector3D vertex_vecmath(vertex.getX(), vertex.getY(), vertex.getZ());
        //Получаем точку на экране путем перемножения матриц
        Point2D resultPoint = Point2D::vertexToPoint(
            Matrix4D::multiply_matrix4d_by_vector3d(model_view_projection_matrix, vertex_vecmath), width, height);
        //Добавляем точку в итоговый массив для вывода
        result_points.emplace_back(resultPoint);
    }
}


void RenderEngine::render_polygons(QPainter &painter, const Model &mesh, const int &width, const int &height,
                                   const Matrix4D &model_view_projection_matrix, const int nPolygons)
{
    for (int polygonInd = 0; polygonInd < nPolygons; ++polygonInd) {
        //Получаем все вершины конкретного полигона
        const int nVerticesInPolygon = static_cast<int>(mesh.polygons[polygonInd].get_vertex_indices().size());
        //Создаем лист содержащий все точки полигона
        std::vector<Point2D> resultPoints;
        //Проходимся по всем вершинам полигона
        add_polygons_vertex(mesh, width, height, model_view_projection_matrix, polygonInd, nVerticesInPolygon,
                            resultPoints);

        for (int vertexInPolygonInd = 1; vertexInPolygonInd < nVerticesInPolygon; ++vertexInPolygonInd) {
            painter.drawLine(
                static_cast<int>(resultPoints[vertexInPolygonInd - 1].getX()),
                static_cast<int>(resultPoints[vertexInPolygonInd - 1].getY()),
                static_cast<int>(resultPoints[vertexInPolygonInd].getX()),
                static_cast<int>(resultPoints[vertexInPolygonInd].getY()));
        }

        if (nVerticesInPolygon > 0)
            painter.drawLine(
                static_cast<int>(resultPoints[nVerticesInPolygon - 1].getX()),
                static_cast<int>(resultPoints[nVerticesInPolygon - 1].getY()),
                static_cast<int>(resultPoints[0].getX()),
                static_cast<int>(resultPoints[0].getY()));
    }
}
