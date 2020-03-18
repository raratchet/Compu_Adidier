#include "utilities.h"

void utilities::rotate(Vector2& vector, float angle)
{
	vector.setX(cos(angle) * vector.getX() - sin(angle) * vector.getY());
	vector.setY(sin(angle) * vector.getX() + cos(angle) * vector.getY());
}

void utilities::rotate(std::vector<Vector2>& points, float angle)
{
	for (auto& point : points)
	{
		rotate(point, angle);
	}
}

void utilities::scale(Vector2& vector, float sx, float sy)
{
	vector.setX(sx * vector.getX());
	vector.setY(sy * vector.getY());
}

void utilities::scale(Vector2& vector, float s)
{
	scale(vector, s, s);
}

void utilities::scale(std::vector<Vector2>& points, float sx, float sy)
{
	for (auto& point : points)
	{
		scale(point, sx, sy);
	}
}

void utilities::scale(std::vector<Vector2>& points, float s)
{
	scale(points, s, s);
}

void utilities::translate(Vector2& vector, float tx, float ty)
{
	vector.setX(vector.getX() + tx);
	vector.setY(vector.getY() + ty);
}

void utilities::translate(std::vector<Vector2>& points, float tx, float ty)
{
	for (auto& point : points)
	{
		translate(point, tx, ty);
	}
}