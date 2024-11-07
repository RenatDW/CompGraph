#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "Vector3D.h"

class Vector3D;

class Vector4D
{
public:
	Vector4D();

	Vector4D(float x, float y, float z, float w);

	[[nodiscard]] float getX() const;

	[[nodiscard]] float getY() const;

	[[nodiscard]] float getZ() const;

	[[nodiscard]] float getW() const;
	
	void setX(float x);

	void setY(float y);

	void setZ(float z);

	void setW(float w);

	Vector4D operator + (const Vector4D& v) const;

	Vector4D operator - (const Vector4D& v) const;

	float operator * (const Vector4D& v) const;

	Vector4D operator * (float k) const;

	[[nodiscard]] float length() const;

	[[nodiscard]] Vector4D normalization() const;

	friend bool operator==(const Vector4D &lhs, const Vector4D &rhs)
	{
		return lhs.x == rhs.x
		       && lhs.y == rhs.y
		       && lhs.z == rhs.z
		       && lhs.w == rhs.w;
	}

	friend bool operator!=(const Vector4D &lhs, const Vector4D &rhs)
	{
		return !(lhs == rhs);
	}

	static Vector4D transitionVect(Vector3D v);

	~Vector4D();

private:
	float x;
	float y;
	float z;
	float w;
};

#endif