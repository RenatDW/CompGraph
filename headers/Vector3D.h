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

	Vector3D dot(Vector3D v);

	~Vector3D();

private:
	float x;
	float y;
	float z;
};

#endif