#pragma once
class Vector2
{
private:
	float x;
	float y;
public:
	Vector2();
	Vector2(float x, float y);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	static float vectorSize(Vector2 vector);
	Vector2 operator+(Vector2 v2);
	Vector2 operator-(Vector2 v2);
	float operator*(Vector2 v2);
	Vector2 operator*(float esc);
	bool operator==(Vector2 v2);
	bool operator!=(Vector2);
	float distance(Vector2);
	static Vector2 unitVector(Vector2 vec);
};

