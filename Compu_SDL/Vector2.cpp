#include "Vector2.h"
#include<math.h>

Vector2::Vector2()
{
	x = y = 0;
}
Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}
float Vector2::getX()
{
	return x;
}
float Vector2::getY()
{
	return y;
}
void Vector2::setX(float x)
{
	this->x = x;
}
void Vector2::setY(float y)
{
	this->y = y;
}
Vector2 Vector2::operator+(Vector2 v2)
{
	Vector2 temp;
	temp.setX(x + v2.getX());
	temp.setY(y + v2.getY());
	return temp;
}

Vector2 Vector2::operator-(Vector2 v2)
{
	Vector2 temp;
	temp.setX(x - v2.getX());
	temp.setY(y - v2.getY());
	return temp;
}

Vector2 Vector2::unitVector(Vector2 vector)
{
	float size = vectorSize(vector);
	Vector2 unit = Vector2(vector.x / size, vector.y / size);
	return unit;
}

float Vector2::vectorSize(Vector2 vector) {
	float x = vector.getX();
	float y = vector.getY();
	return (float)sqrt((x * x) + (y * y));
}

float Vector2::operator*(Vector2 v2)
{
	float temp;
	temp = x * v2.getX() + y * v2.getY();
	return temp;
}

Vector2 Vector2::operator*(float esc) {
	Vector2 temp;
	temp.setX(x * esc);
	temp.setY(y * esc);
	return temp;
}

bool Vector2::operator==(Vector2 v2)
{
	if (x == v2.getX())
		if (y == v2.getY())
			return true;
	return false;
}

bool Vector2::operator!=(Vector2 v2)
{
	if (x == v2.getX())
		if (y == v2.getY())
			return false;
	return true;
}

float Vector2::distance(Vector2 v2)
{
	return sqrt(pow(v2.getX() - x, 2) + pow(v2.getY() - y, 2));
}
