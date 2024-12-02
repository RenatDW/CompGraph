//
// Created by Ренат Асланов on 07.11.2024. Я СЛЕЖУ ЗА ТОБОЙ
//
#include "../headers/Illumination.h"
#include "../../math//headers/MathCast.h"
#include <array>

void Illumination::render()
{
    // this->illumination();
}

void Illumination::add_vertex(Model &mesh, const Matrix4D &model_view_projection_matrix, int triangle_ind,
                              int n_vertices_in_triangle, int width, int height)
{
    std::vector<Point3D> normal_points;
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_triangle; ++vertex_in_triangle_ind) {
        int texture_vertex_ind = mesh.triangles[triangle_ind].get_normal_indices()[vertex_in_triangle_ind];
        Point3D result_point = {
            mesh.normals[texture_vertex_ind].getX(), mesh.normals[texture_vertex_ind].getY(),
            mesh.normals[texture_vertex_ind].getZ()
        };
        normal_points.emplace_back(result_point);
    }
    this->normal_points = normal_points;
}

void Illumination::illumination(const std::array<Point3D, 3> &normal_vectors, const Point3D &P, Camera &camera, const float weight_a,
                                const float weight_b, const float weight_c, int &r, int &g, int &b)
{
    if (normal_vectors.empty()) {
        return;
    }
    float k = 0.4;
    float l = calculate_parametr_of_illumination(normal_vectors, camera, P, weight_a, weight_b, weight_c);
    r *= (1 - k + k * l), g *= (1 - k + k * l), b *= (1 - k + k * l);
}

float Illumination::calculate_parametr_of_illumination(const std::array<Point3D, 3> &normal_vectors, Camera &camera,
    const Point3D &P, const float weightA, const float weightB, const float weightC)
{
    Vector3D cam{ camera.get_position().getX(), camera.get_position().getY(), camera.get_position().getZ()};
    Vector3D normal_A = MathCast::to_Vector3D(normal_vectors[0]).normalize();
    Vector3D normal_B = MathCast::to_Vector3D(normal_vectors[1]).normalize();
    Vector3D normal_C = MathCast::to_Vector3D(normal_vectors[2]).normalize();
    Vector3D vn = (normal_A * weightA + normal_B * weightB + normal_C * weightC).normalize();
    Vector3D ray = (cam - Vector3D{P.getX(), P.getY(), P.getZ()}).normalize();
    float l = -(ray * vn);
    if (l < 0.0f) {
        l = 0.0f;
    }
    return l;
}
