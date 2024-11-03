//
// Created by Ренат Асланов on 03.11.2024.
//

#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H


#include <vector>
#include <limits>

class DepthBuffer {
public:
    DepthBuffer(int width, int height)
        : width(width), height(height), buffer(width * height, std::numeric_limits<float>::infinity()) {}

    float get(int x, int y) const;

    void set(int x, int y, float depth);

private:
    int width;
    int height;
    std::vector<float> buffer; // Хранит значения глубины
};
#endif //DEPTHBUFFER_H
