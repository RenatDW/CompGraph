//
// Created by Ренат Асланов on 03.12.2024.
//
#include <unordered_map>
#include <QColor>
#include "Point2D.h"
#include <vector>

#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H


class PixelBuffer
{
private:
	std::unordered_map<QColor, std::vector<Point2D>> pixel_buffer;
};


#endif //PIXELBUFFER_H
