#pragma once
#include <SDL.h>
#include "Vector2.h"
#include <iostream>
#include <vector>
#include <math.h>
#include "Pixel.h"
class Artist
{
private:
	int* SCREEN_WIDTH;
	int* SCREEN_HEIGHT;
	int* tam;
	Pixel** pixels;

public:
	Artist(int* s_width, int* s_heigth,int* tam, Pixel** s_pixels);
	void drawLineTotal(int x1, int y1, int x2, int y2);
	void drawLineRecharged(int x1, int y1, int x2, int y2);
	void drawLineRevege(int x1, int y1, int x2, int y2);
	void drawLineRevege_2(int x1, int y1, int x2, int y2);
	void drawCircle(int r, int xc, int yc);
	void drawLine(int x1, int y1, int x2, int y2);
	void drawLine(Vector2 v1, Vector2 v2);
	void drawStrip(const std::vector<Vector2>& points);
	void drawPoly(const std::vector<Vector2>& points);
	void drawBezier(std::vector<Vector2> points);
	void drawCarita();
	void drawFillCircle(float r, float xc, float yc);

private:
	int calculateXBezier(std::vector<Vector2>& points, float t);
	int calculateYBezier(std::vector<Vector2>& points, float t);
	void colorate(int x, int y);
};

