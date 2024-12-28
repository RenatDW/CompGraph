//
// Created by Ренат Асланов on 07.11.2024.
//

#include "../headers/Texture.h"

void Texture::texturing(const std::array<Point2D, 3> &texture_vectors, const QImage &image, float weight_a,
    float weight_b, float weight_c, int &r, int &g, int &b)
{
    if (texture_vectors.empty() || image.isNull()) {
        return;
    }
    QColor texColor = get_suitable_pixel(texture_vectors, image, weight_a, weight_b, weight_c);
    r = texColor.red(), g = texColor.green(), b = texColor.blue();
}

QColor Texture::get_suitable_pixel(const std::array<Point2D, 3> &texture_vectors, const QImage &image,
    const float weight_a, const float weight_b, const float weight_c)
{
    float u = weight_a * texture_vectors[0].getX() + weight_b * texture_vectors[1].getX() + weight_c * texture_vectors[2].
              getX();
    float v = weight_a * texture_vectors[0].getY() + weight_b * texture_vectors[1].getY() + weight_c * texture_vectors[2].
              getY();
    int texX = static_cast<int>(static_cast<float>(image.width() - 1) - u * static_cast<float>(image.width() - 1));
    int texY = static_cast<int>(static_cast<float>(image.height() - 1) - v * static_cast<float>(image.height() - 1));
    texX = std::clamp(texX, 0, image.width() - 1);
    texY = std::clamp(texY, 0, image.height() - 1);

    return image.pixel(texX, texY);
}
