//
// Created by Ренат Асланов on 23.10.2024.
//
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
                          Camera camera,
                          const Model mesh,
                          const int width,
                          const int height,
                          const bool showTriangulation) {
    Matrix4D modelMatrix = GraphicConveyor::rotate_scale_translate();
    Matrix4D viewMatrix = camera.getViewMatrix();
    Matrix4D projectionMatrix = camera.getProjectionMatrix();

    Matrix4D modelViewProjectionMatrix(modelMatrix);
    modelViewProjectionMatrix.mul(viewMatrix);
    modelViewProjectionMatrix.mul(projectionMatrix);
    
    int nPolygons = mesh.polygons.size();
    //Проходимся по каждому полигону
    for (int polygonInd = 0; polygonInd < nPolygons; ++polygonInd) {
        //Получаем все вершины конкретного полигона
        const int nVerticesInPolygon = mesh.polygons[polygonInd].get_vertex_indices().size();
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
                GraphicConveyor::multiplyMatrix4ByVector3(modelViewProjectionMatrix, vertexVecmath), width, height);
            //Добавляем точку в итоговый массив для вывода
            resultPoints.emplace_back(resultPoint);
        }

        for (int vertexInPolygonInd = 1; vertexInPolygonInd < nVerticesInPolygon; ++vertexInPolygonInd) {
            painter.drawLine(
                resultPoints[vertexInPolygonInd - 1].x1(),
                resultPoints[vertexInPolygonInd - 1].y1(),
                resultPoints[vertexInPolygonInd].x1(),
                resultPoints[vertexInPolygonInd].y1());
        }

        if (nVerticesInPolygon > 0)
            painter.drawLine(
                resultPoints[nVerticesInPolygon - 1].x1(),
                resultPoints[nVerticesInPolygon - 1].y1(),
                resultPoints[0].x1(),
                resultPoints[0].y1());
    }
}
