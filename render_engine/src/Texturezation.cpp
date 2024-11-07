//
// Created by Ренат Асланов on 07.11.2024.
//

#include "../headers/Texturezation.h"

void Texturezation::render()
{
    // texturation();
}

void Texturezation::add_vertex(Model &mesh, Matrix4D &model_view_projection_matrix, int triangle_ind,
                               int n_vertices_in_triangle, int width, int height)
{
    std::vector<Point2D> texture_vectors;
    for (int vertex_in_triangle_ind = 0; vertex_in_triangle_ind < n_vertices_in_triangle; ++vertex_in_triangle_ind) {
        int texture_vertex_ind = mesh.triangles[triangle_ind].get_texture_indices()[vertex_in_triangle_ind];
        Point2D result_point = {
            mesh.textureVertices[texture_vertex_ind].getX(), mesh.textureVertices[texture_vertex_ind].getY()
        };
        texture_vectors.emplace_back(result_point);
    }
    this->texture_vectors = texture_vectors;
}

void Texturezation::texturation(const std::vector<Point2D> &texture_vectors, const QImage &image, const float weightA,
    const float weightB, const float weightC, int &r, int &g, int &b)
{
    if (texture_vectors.empty() || image.isNull()) {
        return;
    }
    QColor texColor = get_suitable_pixel(texture_vectors, image, weightA, weightB, weightC);
    r = texColor.red(), g = texColor.green(), b = texColor.blue();
}

QColor Texturezation::get_suitable_pixel(const std::vector<Point2D> &texture_vectors, const QImage &image,
    const float weightA, const float weightB, const float weightC)
{
    float u = weightA * texture_vectors[0].getX() + weightB * texture_vectors[1].getX() + weightC * texture_vectors[2].
              getX();
    float v = weightA * texture_vectors[0].getY() + weightB * texture_vectors[1].getY() + weightC * texture_vectors[2].
              getY();
    int texX = static_cast<int>(static_cast<float>(image.width() - 1) - u * static_cast<float>(image.width() - 1));
    int texY = static_cast<int>(static_cast<float>(image.height() - 1) - v * static_cast<float>(image.height() - 1));
    texX = std::clamp(texX, 0, image.width() - 1);
    texY = std::clamp(texY, 0, image.height() - 1);

    return image.pixel(texX, texY);
}
