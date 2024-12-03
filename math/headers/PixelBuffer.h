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
public:
	PixelBuffer();
	void add_element(Point2D point, QColor color);
	//void parse_colors();
	std::unordered_map<QColor, std::vector<Point2D>,MyHashFunction> color_pixel_relationship;

private:
	std::unordered_map<Point2D, QColor,MyHashFunction> pixel_buffer;
};


#endif //PIXELBUFFER_H
