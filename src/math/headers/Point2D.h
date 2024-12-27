#ifndef POINT2D_H
#define POINT2D_H

#include "Vector3D.h"
#include "Vector2D.h"

#include <vector>
#include <string>
#include <iostream>

class Point2D
{

public:
    Point2D();

    Point2D(const Vector2D& vector);

    Point2D(float x, float y);

    [[nodiscard]] float getX() const;

    [[nodiscard]] float getY() const;

    void setX(float x);

    void setY(float y);

    void set(float x, float y);

private:
    float x;
    float y;

public:
	friend bool operator==(const Point2D& lhs, const Point2D& rhs)
	{
		return lhs.x == rhs.x
			   && lhs.y == rhs.y;
	}

	friend bool operator!=(const Point2D& lhs, const Point2D& rhs)
	{
		return !(lhs == rhs);
	}
	bool operator<(const Point2D& other) const
	{
		return (x < other.x) || (x == other.x && y < other.y);
	}

};

struct Point2DHash {
	size_t operator()(const Point2D& point) const {
		return std::hash<float>()(point.getX()) ^ (std::hash<float>()(point.getY()) << 1);
	}
};

#endif
