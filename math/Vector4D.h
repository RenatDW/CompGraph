#pragma once

class Vector4D
{
public:
	Vector4D();

	Vector4D(double x, double y, double z, double w);

	double getX() const;

	void setX(double x);

	double getY() const;

	void setY(double y);

	double getZ() const;

	void setZ(double z);

	double getW() const;

	void setW(double w);

	~Vector4D();

private:
	double x;
	double y;
	double z;
	double w;
};