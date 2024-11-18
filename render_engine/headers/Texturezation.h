//
// Created by Ренат Асланов on 07.11.2024.
//

#ifndef TEXTUREZATION_H
#define TEXTUREZATION_H

#include <QImage>
#include <vector>

#include "Renderable.h"

class Texturezation

{
public:
    std::vector<Point2D> texture_vectors;

    Texturezation() = default;

    virtual ~Texturezation() = default;

    void render();

    void add_vertex(Model &mesh, Matrix4D &model_view_projection_matrix, int triangle_ind, int n_vertices_in_triangle, int width, int
                    height);

    static void texturation(const std::array<Point2D, 3> &texture_vectors, const QImage &image,
                            float weight_a,
                            float weight_b, float weight_c, int &r, int &g, int &b);
    static QColor get_suitable_pixel(const std::array<Point2D, 3> &texture_vectors, const QImage &image,
                                     float weight_a,
                                     float weight_b, float weight_c);
};


#endif //TEXTUREZATION_H
