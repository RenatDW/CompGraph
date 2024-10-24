#ifndef VECTOR4D_H
#define VECTOR4D_H

class Vector4D
{
public:
	Vector4D();

	Vector4D(float x, float y, float z, float w);

	float getX() const;

	float getY() const;

	float getZ() const;

	float getW() const;
	
	void setX(float x);

	void setY(float y);

	void setZ(float z);

	void setW(float w);

	~Vector4D();

private:
	float x;
	float y;
	float z;
	float w;
};

#endif