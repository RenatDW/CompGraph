#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <unordered_map>
#include <QColor>
#include "Point2D.h"

class PixelBuffer {
public:
	void add(Point2D point, QColor color);
	QColor getColor(Point2D point) const;
	std::unordered_map<Point2D, QColor, Point2DHash> data;
private:
};

#endif // PIXELBUFFER_H