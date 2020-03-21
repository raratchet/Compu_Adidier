#include "artist.h"

Artist::Artist(int s_width, int s_heigth, int _tam)
{
	SCREEN_WIDTH = s_width;
	SCREEN_HEIGHT = s_heigth;
	tam = _tam;
	pixels = vector<vector<Pixel>>(SCREEN_HEIGHT,vector<Pixel>(SCREEN_WIDTH));
}

void Artist::drawLineTotal(int x1, int y1, int x2, int y2)
{
	float m, c, x, y;
	m = c = x = y = 0;

	m = (y2 - y1) / (x2 - x1);
	c = y1 - (m * x1);

	x = x1;
	y = y1;

	if (std::abs(m) <= 1)
	{
		while (x <= x2)
		{
			colorate(x, y);
			x += 1;
			y = (m * x) + c;
		}
	}
	else
	{
		while (y <= x2)
		{
			colorate(x, y);
			y += 1;
			x = (y - c) / m;
		}
	}
}

void Artist::drawLineRecharged(int x1, int y1, int x2, int y2)
{
	int deno = 0;
	float xinc = 0;
	float yinc = 0;
	int dx = x2 - x1;
	int dy = y2 - y1;
	int x = 0;
	int y = 0;

	if (std::abs(dy) < std::abs(dx))
		deno = std::abs(dx);
	else if (std::abs(dy) >= std::abs(dx))
		deno = std::abs(dy);

	xinc = dx / deno;
	yinc = dy / deno;
	x = x1;
	y = y1;

	for (int i = 0; i < deno; i++)
	{
		colorate(x, y);
		x += xinc;
		y += yinc;
	}
}

void Artist::drawLineRevege(int x1, int y1, int x2, int y2) 	//Algorítmo de bresenham para pendientes menores que 1
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int x, y, p;
	x = x1;
	y = y1;
	p = (2 * dy) - dx;

	for (unsigned i = 0; i <= dx; i++)
	{
		colorate(x, y);
		if (p < 0)
		{
			x++;
			p = (2 * dy) + p;
		}
		else if (p >= 0)
		{
			x++;
			y++;
			p = (2 * dy) - (2 * dx) + p;
		}
	}
}

void Artist::drawLineRevege_2(int x1, int y1, int x2, int y2) 	//Algorítmo de bresenham para pendientes mayores que 1
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int x, y, p;
	x = x1;
	y = y1;
	p = (2 * dx) - dy;
	for (unsigned i = 0; i <= dy; i++)
	{
		colorate(x, y);
		if (p < 0)
		{
			y++;
			p = (2 * dx) + p;
		}
		else if (p >= 0)
		{
			x++;
			y++;
			p = (2 * dx) - (2 * dy) + p;
		}
	}
}

void Artist::drawCircle(int r, int xc, int yc)
{
	int p, x, y;
	x = 0;
	y = r;
	p = 1 - r;


	for (int i = 0; x <= y; i++)
	{
		colorate(x + xc, y + yc);
		colorate(-x + xc, y + yc);
		colorate(x + xc, -y + yc);
		colorate(-x + xc, -y + yc);
		colorate(y + xc, x + yc);
		colorate(-y + xc, x + yc);
		colorate(y + xc, -x + yc);
		colorate(-y + xc, -x + yc);

		if (p <= 0)
		{
			x++;
			p = (2 * x) + p + 3;
		}
		else
		{
			x++;
			y--;
			p = (2 * x) - (2 * y) + p + 5;
		}

	}
}

void Artist::drawLine(int x1, int y1, int x2, int y2) //Algoritmo de Bresenham Completo
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	short signX, signY;
	int x, y, p;
	x = x1;
	y = y1;

	signX = (dx >= 0) ? 1 : -1;
	signY = (dy >= 0) ? 1 : -1;

	if (std::abs(dy) <= std::abs(dx))
	{
		p = (2 * dy * signY) - (dx * signX);

		for (int i = 0; i <= (dx * signX); i++)
		{
			colorate(x, y);
			if (p < 0)
			{
				x = x + signX;
				p = (2 * dy * signY) + p;
			}
			else if (p >= 0)
			{
				x = x + signX;
				y = y + signY;
				p = (2 * dy * signY) - (2 * dx * signX) + p;
			}
		}
	}
	else if (std::abs(dy) > std::abs(dx))
	{
		p = (2 * dx * signX) - (dy * signY);

		for (int i = 0; i <= (dy * signY); i++)
		{
			colorate(x, y);
			if (p < 0)
			{
				y = y + signY;
				p = (2 * dx * signX) + p;
			}
			else if (p >= 0)
			{
				x = x + signX;
				y = y + signY;
				p = (2 * dx * signX) - (2 * dy * signY) + p;
			}
		}
	}
}

void Artist::drawLine(Vector2 v1, Vector2 v2)
{
	drawLine(v1.getX(), v1.getY(), v2.getX(), v2.getY());
}

void Artist::drawStrip(const std::vector<Vector2>& points)
{
	for (auto it = points.begin(); it != points.end(); it++)
	{
		if ((it + 1) != points.end())
			drawLine(*it, *(it + 1));
		else
			break;
	}
}

void Artist::drawPoly(const std::vector<Vector2>& points)
{
	for (auto it = points.begin(); it != points.end(); it++)
	{
		if ((it + 1) != points.end())
			drawLine(*it, *(it + 1));
		else if ((it + 1) == points.end())
			drawLine(*it, points.front());
		else
			break;
	}
}

int Artist::calculateXBezier(std::vector<Vector2>& points, float t)
{
	int tmp = 0;
	if (points.size() >= 4)
	{
		tmp += pow((1 - t), 3) * points[0].getX();
		tmp += (3 * t) * pow((1 - t), 2) * points[1].getX();
		tmp += (3 * pow(t, 2)) * (1 - t) * points[2].getX();
		tmp += pow(t, 3) * points[3].getX();
	}
	else if (points.size() == 3)
	{
		tmp += pow((1 - t), 2) * points[0].getX();
		tmp += (2 * t) * (1 - t) * points[1].getX();
		tmp += pow(t, 2) * points[2].getX();
	}
	else if (points.size() == 2)
	{
		tmp += (1 - t) * points[0].getX();
		tmp += t * points[1].getX();
	}
	else if (points.size() == 1)
	{
		tmp += points[0].getX();
	}
	return tmp;
}

int Artist::calculateYBezier(std::vector<Vector2>& points, float t)
{
	int tmp = 0;
	if (points.size() >= 4)
	{
		tmp += pow((1 - t), 3) * points[0].getY();
		tmp += (3 * t) * pow((1 - t), 2) * points[1].getY();
		tmp += (3 * pow(t, 2)) * (1 - t) * points[2].getY();
		tmp += pow(t, 3) * points[3].getY();
	}
	else if (points.size() == 3)
	{
		tmp += pow((1 - t), 2) * points[0].getY();
		tmp += (2 * t) * (1 - t) * points[1].getY();
		tmp += pow(t, 2) * points[2].getY();
	}
	else if (points.size() == 2)
	{
		tmp += (1 - t) * points[0].getY();
		tmp += t * points[1].getY();
	}
	else if (points.size() == 1)
	{
		tmp += points[0].getY();
	}
	return tmp;
}

void Artist::drawBezier(std::vector<Vector2> points) //Hacerlo cada cuatro puntos
{
	while (points.size() > 0)
	{
		for (float t = 0; t < 1; t += 0.01)
		{
			int x = calculateXBezier(points, t);
			int y = calculateYBezier(points, t);

			if (t < 1)
			{
				int x2 = calculateXBezier(points, t + 0.01);
				int y2 = calculateYBezier(points, t + 0.01);
				drawLine(x, y, x2, y2);
			}
		}
		for (unsigned i = 0; i < 3; i++)
		{
			if (points.size() > 0)
				points.erase(points.begin());
		}
	}

}

void Artist::drawCarita()
{
	drawCircle(100, 100, 100);
	int x = 250;
	int y = 300;
	drawLine(70, 25, 70, 85); //ojo 1
	drawLine(140, 25, 140, 85); // ojo 2
	std::vector<Vector2> nariz;
	nariz.push_back(Vector2(100, 90));
	nariz.push_back(Vector2(120, 120));
	nariz.push_back(Vector2(90, 120));
	drawStrip(nariz);

	std::vector<Vector2> boca;
	boca.push_back(Vector2(50, 140));
	boca.push_back(Vector2(70, 165));
	boca.push_back(Vector2(140, 165));
	boca.push_back(Vector2(160, 140));
	drawPoly(boca);
}

void Artist::drawFillCircle(float r, float xc, float yc)
{
	float p, x, y;
	x = 0;
	y = r;
	p = 1 - r;


	for (int i = 0; x <= y; i++)
	{
		colorate(x + xc, y + yc);
		colorate(-x + xc, y + yc);
		colorate(x + xc, -y + yc);
		colorate(-x + xc, -y + yc);
		colorate(y + xc, x + yc);
		colorate(-y + xc, x + yc);
		colorate(y + xc, -x + yc);
		colorate(-y + xc, -x + yc);

		drawLine(x + xc, -y + yc, -x + xc, y + yc); //1-5
		drawLine(y + xc, -x + yc, -y + xc, x + yc); //2-6
		drawLine(y + xc, x + yc, -y + xc, -x + yc); //3-7
		drawLine(x + xc, y + yc, -x + xc, -y + yc); //4-8

		if (p <= 0)
		{
			x++;
			p = (2 * x) + p + 3;
		}
		else
		{
			x++;
			y--;
			p = (2 * x) - (2 * y) + p + 5;
		}

	}
}

void Artist::colorate(int x, int y)
{
	if (x >= 0 && y >= 0)
		if (x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
		{
			pixels[y][x].painted = true;
			pixels[y][x].color = color;
		}
}

vector<vector<Pixel>>* Artist::getPixels()
{
	return &pixels;
}

Pixel* Artist::getPixelAt(int x, int y)
{
	return &pixels[y][x];
}

void Artist::clearPixels()
{
	for(int x = 0; x < SCREEN_WIDTH; x++)
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			getPixelAt(x, y)->painted = false;
			getPixelAt(x, y)->color = 0;
		}
}

void Artist::drawPoint(int x, int y)
{
	for(int i = x-1; i <= x+1; i++)
		for (int j = y - 1; j <= y + 1; j++)
		{
			if(i >= 0 && j >= 0)
				if(i < SCREEN_WIDTH && j < SCREEN_HEIGHT)
					colorate(i, j);
		}


}

void Artist::erasePoint(int x, int y)
{
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i >= 0 && j >= 0)
				if (i < SCREEN_WIDTH && j < SCREEN_HEIGHT)
				{
					getPixelAt(i, j)->color = 0;
					getPixelAt(i, j)->painted = false;
				}
		}


}

void Artist::setColor(char value)
{
	color = value;
}

char Artist::getColor()
{
	return color;
}
