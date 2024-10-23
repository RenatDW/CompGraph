#pragma once

class Vector2D
{
public:
	Vector2D();

	Vector2D(double x, double y);

	double getX() const;

	void setX(double x);

	double getY() const;

	void setY(double y);

	~Vector2D();

private:
	double x;
	double y;
};