//
// Created by Ренат Асланов on 03.11.2024.
//

#include "../headers/DepthBuffer.h"

float DepthBuffer::get(const int x, const int y) const
{
    return buffer[y * width + x];
}

int DepthBuffer::size() const
{
    return width * height;
}

void DepthBuffer::set(const int x, const int y, const float depth)

{
    buffer[y * width + x] = depth;
}

int DepthBuffer::getWidth() const
{
    return width;
}

int DepthBuffer::getHeight() const
{
    return height;
}
