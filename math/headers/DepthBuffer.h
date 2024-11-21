#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

#include <vector>
#include <limits>

class DepthBuffer {
public:
    DepthBuffer(int width, int height)
        : width(width), height(height), buffer(width * height, std::numeric_limits<float>::infinity()) {}

    [[nodiscard]] float get(int x, int y) const;

	[[nodiscard]] int size() const;

    void set(int x, int y, float depth);

	[[nodiscard]] int getWidth() const;
	[[nodiscard]] int getHeight() const;

private:
    int width;
    int height;
    std::vector<float> buffer; // Хранит значения глубины
};
#endif //DEPTHBUFFER_H
