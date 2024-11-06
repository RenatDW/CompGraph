#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D 
{
	friend bool operator==(const Vector2D &lhs, const Vector2D &rhs)
	{
		return lhs.x == rhs.x
		       && lhs.y == rhs.y;
	}

	friend bool operator!=(const Vector2D &lhs, const Vector2D &rhs)
	{
		return !(lhs == rhs);
	}

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

	friend bool operator==(const Vector2D& lhs, const Vector2D& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	friend bool operator!=(const Vector2D& lhs, const Vector2D& rhs)
	{
		return !(lhs == rhs);
	}

	~Vector2D();

private:
	float x;
	float y;
};

#endif