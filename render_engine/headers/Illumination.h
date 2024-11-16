//
// Created by Ренат Асланов on 07.11.2024.
//

#ifndef ILLUMINATION_H
#define ILLUMINATION_H
#include <vector>

#include "Camera.h"
#include "Renderable.h"
#include "../../math/headers/Point3D.h"


class Illumination
{
public:
    //TODO исправить камел кейсы
    std::vector<Point3D> normal_points;

    void render();

    Illumination() = default;

    virtual ~Illumination() = default;

    void add_vertex(Model &mesh, const Matrix4D &model_view_projection_matrix, int triangle_ind,
        int n_vertices_in_triangle, int width, int height);

    static void illumination(const std::vector<Point3D> &normal_vectors, const Point3D &P,
                             Camera &camera, float weightA, float weightB, float weightC, int &r,
                             int &g, int &b);

    static float calculate_parametr_of_illumination(const std::vector<Point3D> &normal_vectors, Camera &camera,
                                             const Point3D &P,
                                             const float weightA, const float weightB, const float weightC);
};

#endif //ILLUMINATION_H
