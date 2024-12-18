#ifndef ILLUMINATION_H
#define ILLUMINATION_H

#include "Camera.h"
#include "Renderable.h"
#include "../../math/headers/Point3D.h"

#include <vector>

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

    static void illumination(const std::array<Point3D, 3> &normal_vectors, const Point3D &P,
                             Camera &camera, float weight_a, float weight_b, float weight_c, int &r,
                             int &g, int &b);

    static float calculate_parametr_of_illumination(const std::array<Point3D, 3> &normal_vectors, Camera &camera,
                                             const Point3D &P,
                                             float weight_A, float weight_B, float weight_C);
};

#endif //ILLUMINATION_H
