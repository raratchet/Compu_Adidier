#include "Vector3.h"
#include<math.h>

Vector3::Vector3()
{
	x = y = z = 0;
}
Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
float Vector3::getX()
{
	return x;
}
float Vector3::getY()
{
	return y;
}
float Vector3::getZ()
{
	return z;
}
void Vector3::setX(float x)
{
	this->x = x;
}
void Vector3::setY(float y)
{
	this->y = y;
}
void Vector3::setZ(float z)
{
	this->z = z;
}
Vector3 Vector3::operator+(Vector3 v2)
{
	Vector3 temp;
	temp.setX(x + v2.getX());
	temp.setY(y + v2.getY());
	temp.setZ(z + v2.getZ());
	return temp;
}

Vector3 Vector3::operator-(Vector3 v2)
{
	Vector3 temp;
	temp.setX(x - v2.getX());
	temp.setY(y - v2.getY());
	temp.setZ(z - v2.getZ());
	return temp;
}

Vector3 Vector3::unitVector(Vector3 vector)
{
	float size = vectorSize(vector);
	Vector3 unit = Vector3(vector.x / size, vector.y / size, vector.z/size);
	return unit;
}

float Vector3::vectorSize(Vector3 vector) {
	float x = vector.getX();
	float y = vector.getY();
	float z = vector.getZ();
	return (float)sqrt((x * x) + (y * y) + (z * z));
}

float Vector3::operator*(Vector3 v2)
{
	float temp;
	temp = x * v2.getX() + y * v2.getY() + z * v2.getZ();
	return temp;
}

Vector3 Vector3::operator*(float esc) {
	Vector3 temp;
	temp.setX(x * esc);
	temp.setY(y * esc);
	temp.setZ(z * esc);
	return temp;
}