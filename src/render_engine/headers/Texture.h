#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <vector>
#include "../../math/headers/Point2D.h"

class Texture

{
public:
    std::vector<Point2D> texture_vectors;

    Texture() = default;

    virtual ~Texture() = default;

	static void texturing(const std::array<Point2D, 3> &texture_vectors, const QImage &image,
                            float weight_a,
                            float weight_b, float weight_c, int &r, int &g, int &b);
    static QColor get_suitable_pixel(const std::array<Point2D, 3> &texture_vectors, const QImage &image,
                                     float weight_a,
                                     float weight_b, float weight_c);
};

#endif //TEXTURE_H
