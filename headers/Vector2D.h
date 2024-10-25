#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
	Vector2D();

	Vector2D(float x, float y);

	float getX() const;

	float getY() const;

	void setX(float x);

	void setY(float y);

	~Vector2D();

private:
	float x;
	float y;
};

#endif