#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D 
{
public:
	Vector2D();

	Vector2D(float x, float y);

	[[nodiscard]] float getX() const;

	[[nodiscard]] float getY() const;

	void setX(float x);

	void setY(float y);

	Vector2D operator + (const Vector2D& v) const;

	Vector2D operator - (const Vector2D& v) const;

	float operator * (const Vector2D& v) const;

	Vector2D operator * (float k) const;

	[[nodiscard]] float length() const;

	[[nodiscard]] Vector2D normalization() const;
	
	~Vector2D();

private:
	float x;
	float y;
};

#endif