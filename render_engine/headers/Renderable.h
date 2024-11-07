//
// Created by Ренат Асланов on 07.11.2024.
//

#ifndef RENDERABLE_H
#define RENDERABLE_H
#include "../../model/headers/Model.h"
#include "../../math/headers/Matrix4D.h"
#include "../../math/headers/Point3D.h"
#include "../../math/headers/Point2D.h"


class Renderable
{
public:
    Renderable() = default;

    virtual ~Renderable() = default;

    virtual void render();
    virtual void add_vertex(Model &mesh, const Matrix4D &model_view_projection_matrix, int triangle_ind, int n_vertices_in_triangle, int width, int
                            height);
};


#endif //RENDERABLE_H
