#ifndef TEXTURING_H
#define TEXTURING_H

#include <QImage>
#include <vector>
#include "../../math/headers/Point2D.h"
#include "Texture.h"

class Texturing
{
public:
    std::vector<Point2D> texture_vectors{};

    Texturing() = default;

    virtual ~Texturing() = default;

	static void texturing(const std::array<Point2D, 3> &texture_vectors, Texture& texture,
                            float weight_a,
                            float weight_b, float weight_c, int &r, int &g, int &b);
    static QColor get_suitable_pixel(const std::array<Point2D, 3> &texture_vectors, Texture& texture,
                                     float weight_a,
                                     float weight_b, float weight_c);
};

#endif
