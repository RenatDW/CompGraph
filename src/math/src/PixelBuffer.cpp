//
// Created by Ренат Асланов on 03.12.2024.
//

#include "../headers/PixelBuffer.h"

void PixelBuffer::add(Point2D point, QColor color) {
	data[point] = color; // Insert or update color at point
}

QColor PixelBuffer::getColor(Point2D point) const {
	auto it = data.find(point);
	if (it != data.end()) {
		return it->second; // Return the color if the point exists
	}
	return QColor(); // Return a default color (black) if not found
}
