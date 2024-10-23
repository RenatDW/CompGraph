#pragma once

class Vector3D
{
public:
	Vector3D();

	Vector3D(double x, double y, double z);

	double getX() const;

	void setX(double x);

	double getY() const;

	void setY(double y);

	double getZ() const;

	void setZ(double z);

	~Vector3D();

private:
	double x;
	double y;
	double z;
};