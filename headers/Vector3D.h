#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3D
{
public:
	Vector3D();

	Vector3D(float x, float y, float z);

	float getX() const;

	float getY() const;

	float getZ() const;

	void setX(float x);

	void setY(float y);

	void setZ(float z);

	Vector3D operator + (const Vector3D& v) const;

	Vector3D operator - (const Vector3D& v) const;

	static Vector3D cross(const Vector3D& v1, const Vector3D& v2);

	float operator * (const Vector3D& v) const;

	Vector3D operator * (float k) const;

	float length() const;

	Vector3D normalize() const;

	~Vector3D();

private:
	float x;
	float y;
	float z;
};

#endif