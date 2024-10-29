#include "../headers/RenderEngine.h"
#include "../headers/GraphicConveyor.h"
#include "../headers/mainwindow.h"
#include "../headers/Point2D.h"

// #include <QPainter>
// void RenderEngine::render(QPainter& painter){
// const Camera camera,
// const Model mesh,
// const int width,
// const int height,
// const bool showTriangulation) {
// Matrix4f modelMatrix = rotateScaleTranslate();
// Matrix4f viewMatrix = camera.getViewMatrix();
// Matrix4f projectionMatrix = camera.getProjectionMatrix();
//
// Matrix4f modelViewProjectionMatrix = new Matrix4f(modelMatrix);
// modelViewProjectionMatrix.mul(viewMatrix);
// modelViewProjectionMatrix.mul(projectionMatrix);
// if(showTriangulation.equals(ShowTriangles.TRIANGLES)) {
//     renderTriangle(graphicsContext, mesh, width, height, modelViewProjectionMatrix);
// } else
//     renderPolygons(graphicsContext, mesh, width, height, modelViewProjectionMatrix);

// }

// void RenderEngine::render(QPainter painter) {
//     painter.drawLine(10,10,200,200);
// }

void RenderEngine::render(QPainter &painter,
                          Camera &camera,
                          const Model &mesh,
                          const int &width,
                          const int &height,
                          const bool &showTriangulation)
{
    Matrix4D modelMatrix = Matrix4D::create_identity_matrix();
    Matrix4D viewMatrix = camera.getViewMatrix();
    Matrix4D projectionMatrix = camera.getProjectionMatrix();

    Matrix4D modelViewProjectionMatrix(modelMatrix);
    modelViewProjectionMatrix.mul(viewMatrix);
    modelViewProjectionMatrix.mul(projectionMatrix);

    int nPolygons = (int) mesh.polygons.size();
    //Проходимся по каждому полигону
    for (int polygonInd = 0; polygonInd < nPolygons; ++polygonInd) {
        //Получаем все вершины конкретного полигона
        const int nVerticesInPolygon = (int) mesh.polygons[polygonInd].get_vertex_indices().size();
        //Создаем лист содрежащий все точки полигона
        std::vector<Point2D> resultPoints;
        //Проходимся по всем вершинам полигона
        for (int vertexInPolygonInd = 0; vertexInPolygonInd < nVerticesInPolygon; ++vertexInPolygonInd) {
            //Получаем ссылку на вектор вершины с координатами, проходясь по конкретному полигону и получая номер конкретного вектора
            Vector3D vertex = mesh.vertices[mesh.polygons[polygonInd].get_vertex_indices()[vertexInPolygonInd]];
            //Переводим самописный вектор в библиотечный вектор
            Vector3D vertexVecmath(vertex.getX(), vertex.getY(), vertex.getZ());
            //Получаем точку на экране путем перемножения матриц
            Point2D resultPoint = Point2D::vertexToPoint(
                Matrix4D::multiply_matrix4d_by_vector3d(modelViewProjectionMatrix, vertexVecmath), width, height);
            //Добавляем точку в итоговый массив для вывода
            resultPoints.emplace_back(resultPoint);
        }

        for (int vertexInPolygonInd = 1; vertexInPolygonInd < nVerticesInPolygon; ++vertexInPolygonInd) {
            painter.drawLine(
                (int) resultPoints[vertexInPolygonInd - 1].getX(),
                (int) resultPoints[vertexInPolygonInd - 1].getY(),
                (int) resultPoints[vertexInPolygonInd].getX(),
                (int) resultPoints[vertexInPolygonInd].getY());
        }

        if (nVerticesInPolygon > 0)
            painter.drawLine(
                (int) resultPoints[nVerticesInPolygon - 1].getX(),
                (int) resultPoints[nVerticesInPolygon - 1].getY(),
                (int) resultPoints[0].getX(),
                (int) resultPoints[0].getY());
    }
}
