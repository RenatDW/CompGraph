#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
public:
	Vector3D();

	Vector3D(float x, float y, float z);

	[[nodiscard]] float getX() const;

	[[nodiscard]] float getY() const;

	[[nodiscard]] float getZ() const;

	void setX(float x);

	void setY(float y);

	void setZ(float z);

	Vector3D operator + (const Vector3D& v) const;

	Vector3D operator - (const Vector3D& v) const;

	bool operator==(const Vector3D & position) const = default;

	static Vector3D cross(const Vector3D& v1, const Vector3D& v2);

	float operator * (const Vector3D& v) const;

	Vector3D operator * (float k) const;

	[[nodiscard]] float length() const;

	[[nodiscard]] Vector3D normalize() const;

	friend bool operator==(const Vector3D &lhs, const Vector3D &rhs)
	{
		return lhs.x == rhs.x
		       && lhs.y == rhs.y
		       && lhs.z == rhs.z;
	}

	friend bool operator!=(const Vector3D &lhs, const Vector3D &rhs)
	{
		return !(lhs == rhs);
	}

	~Vector3D();

private:
	float x;
	float y;
	float z;
};

#endif