//
// Created by Ренат Асланов on 03.11.2024.
//

#include "../headers/DepthBuffer.h"

float DepthBuffer::get(int x, int y) const
{
    return buffer[y * width + x];
}

int DepthBuffer::size() const
{
    return width * height;
}

void DepthBuffer::set(int x, int y, float depth)

{
    buffer[y * width + x] = depth;
}
