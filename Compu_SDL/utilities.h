#pragma once
#include <vector>
#include <iostream>
#include "Vector2.h"

class utilities
{
public:

	static void rotate(Vector2& vector, float angle);
	static void rotate(std::vector<Vector2>& points, float angle);
	static void scale(Vector2& vector, float sx, float sy);
	static void scale(Vector2& vector, float s);
	static void scale(std::vector<Vector2>& points, float sx, float sy);
	static void scale(std::vector<Vector2>& points, float s);
	static void translate(Vector2& vector, float tx, float ty);
	static void translate(std::vector<Vector2>& points, float tx, float ty);

};

