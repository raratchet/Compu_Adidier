#pragma once
class Vector3
{
private:
	float x;
	float y;
	float z;
public:
	Vector3();
	Vector3(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	float vectorSize(Vector3 vector);
	Vector3 operator+(Vector3 v2);
	Vector3 operator-(Vector3 v2);
	float operator*(Vector3 v2);
	Vector3 operator*(float esc);
	Vector3 unitVector(Vector3 vec);
};

