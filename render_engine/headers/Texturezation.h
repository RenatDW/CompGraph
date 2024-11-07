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

    static void texturation(const std::vector<Point2D> &texture_vectors, const QImage &image,
                     const float weightA,
                     const float weightB, const float weightC, int &r, int &g, int &b);
    static QColor get_suitable_pixel(const std::vector<Point2D> &texture_vectors, const QImage &image,
                                     float weightA,
                                     float weightB, float weightC);
};


#endif //TEXTUREZATION_H
