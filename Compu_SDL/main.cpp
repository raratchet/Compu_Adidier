#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
#include "Vector2.h"
//#include "Matriz.h"

//Screen dimension constants
int SCREEN_WIDTH = 720;
int SCREEN_HEIGHT = 480;
int tam = 30;

//Starts up SDL and creates window
bool init();


//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);


			}
		}
	}

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;


	SDL_Quit();
}

void setScreen()
{
	if (SCREEN_WIDTH == 0 || SCREEN_HEIGHT == 0)
	{
		SCREEN_WIDTH = 720;
		SCREEN_HEIGHT = 480;
	}
	if (tam == 0)
	{
		tam = 32;
	}
}

void drawPlain()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	//Dibujamos en y desde la mitad
	SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	for (int i = SCREEN_HEIGHT / 2; i < SCREEN_HEIGHT;)
	{
		i += tam;
		SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT - i);
		SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
	}

	//Dibujamos en x desde la mitad
	for (int i = SCREEN_WIDTH / 2; i < SCREEN_WIDTH;)
	{
		i += tam;
		SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH - i, SCREEN_HEIGHT / 2);
		SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT / 2);
	}

	SDL_SetRenderDrawColor(gRenderer, 0x44, 0x44, 0x44, 0xFF);
	for (int i = (SCREEN_WIDTH / 2) + tam; i < SCREEN_WIDTH; i += tam)
	{
		for (int j = (SCREEN_HEIGHT / 2) + tam; j < SCREEN_HEIGHT; j += tam)
		{
			SDL_RenderDrawPoint(gRenderer, i, j);
			SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH - i, j);
			SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH - i, SCREEN_HEIGHT - j);
			SDL_RenderDrawPoint(gRenderer, i, SCREEN_HEIGHT - j);
		}
	}


}

void drawLineTotal(int x1, int y1, int x2, int y2)
{
	float m,c,x,y;
	m = c = x = y = 0;

	m = (y2 - y1) / (x2 - x1);
	c = y1 - (m * x1);

	x = x1;
	y = y1;

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAF, 0xBF, 0xFF);

	if (std::abs(m) <= 1)
	{
		while (x <= x2)
		{
			SDL_RenderDrawPoint(gRenderer, x, y);
			x += 1;
			y = (m * x) + c;
		}
	}
	else
	{
		while (y <= x2)
		{
			SDL_RenderDrawPoint(gRenderer, x, y);
			y += 1;
			x = (y - c) / m;
		}
	}

	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0xAF, 0xAF, 0xFF);
}

void drawLineRecharged(int x1, int y1, int x2, int y2)
{
	int deno = 0;
	float xinc = 0;
	float yinc = 0;
	int dx = x2-x1;
	int dy = y2-y1;
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

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAF, 0xBF, 0xFF);

	for (int i = 0; i < deno ; i++)
	{
		SDL_RenderDrawPoint(gRenderer, x, y);
		x += xinc;
		y += yinc;
	}
	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0xAF, 0xAF, 0xFF);
}

void drawLineRevege(int x1, int y1, int x2, int y2) 	//Algorítmo de bresenham para pendientes menores que 1
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int x, y, p;
	x = x1;
	y = y1;
	p = (2*dy) - dx;

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAF, 0xBF, 0xFF);
	for (unsigned i = 0; i <= dx; i++)
	{
		SDL_RenderDrawPoint(gRenderer, x, y);
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
	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0xAF, 0xAF, 0xFF);
}

void drawLineRevege_2(int x1, int y1, int x2, int y2) 	//Algorítmo de bresenham para pendientes mayores que 1
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int x, y, p;
	x = x1;
	y = y1;
	p = (2 * dx) - dy;

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAF, 0xBF, 0xFF);
	for (unsigned i = 0; i <= dy; i++)
	{
		SDL_RenderDrawPoint(gRenderer, x, y);
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
	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0xAF, 0xAF, 0xFF);
}

void drawCircle(float r, float xc, float yc)
{
	float p, x, y;
	x = 0;
	y = r;
	p = 1 - r;

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAF, 0xBF, 0xFF);

	for (int i = 0; x <= y; i++)
	{
		SDL_RenderDrawPoint(gRenderer, x + xc, y + yc);
		SDL_RenderDrawPoint(gRenderer, -x + xc, y + yc);
		SDL_RenderDrawPoint(gRenderer, x + xc, -y + yc);
		SDL_RenderDrawPoint(gRenderer, -x + xc, -y + yc);
		SDL_RenderDrawPoint(gRenderer, y + xc, x + yc);
		SDL_RenderDrawPoint(gRenderer, -y + xc, x + yc);
		SDL_RenderDrawPoint(gRenderer, y + xc, -x + yc);
		SDL_RenderDrawPoint(gRenderer, -y + xc, -x + yc);

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
	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0xAF, 0xAF, 0xFF);
}

void drawLine(int x1, int y1, int x2, int y2) //Algoritmo de Bresenham Completo
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	short signX, signY;
	int x, y, p;
	x = x1;
	y = y1;

	signX = (dx >= 0) ? 1 : -1;
	signY = (dy >= 0) ? 1 : -1;

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAF, 0xBF, 0xFF);
	if (std::abs(dy) <= std::abs(dx))
	{
		p = (2 * dy * signY) - (dx * signX);

		for (int i = 0; i <= (dx * signX); i++)
		{
			SDL_RenderDrawPoint(gRenderer, x, y);
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
	else if(std::abs(dy) > std::abs(dx))
	{
		p = (2 * dx * signX) - (dy * signY);

		for (int i = 0; i <= (dy * signY); i++)
		{
			SDL_RenderDrawPoint(gRenderer, x, y);
			if (p < 0)
			{
				y= y + signY;
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
	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0xAF, 0xAF, 0xFF);
}

void drawLine(Vector2 v1, Vector2 v2)
{
	drawLine(v1.getX(), v1.getY(), v2.getX(), v2.getY());
}

void drawStrip(const std::vector<Vector2>& points)
{
	for (auto it = points.begin(); it != points.end(); it++)
	{
		if ((it + 1) != points.end())
			drawLine(*it, *(it + 1));
		else
			break;
	}
}

void rotate(Vector2& vector,float angle)
{
	vector.setX(cos(angle) * vector.getX() - sin(angle) * vector.getY());
	vector.setY(sin(angle) * vector.getX() + cos(angle) * vector.getY());
}

void rotate(std::vector<Vector2>& points, float angle)
{
	for (auto& point : points)
	{
		rotate(point, angle);
	}
}

void scale(Vector2& vector, float sx, float sy)
{
	vector.setX(sx * vector.getX());
	vector.setY(sy * vector.getY());
}

void scale(Vector2& vector, float s)
{
	scale(vector, s , s);
}

void scale(std::vector<Vector2>& points, float sx, float sy)
{
	for (auto& point : points)
	{
		scale(point, sx, sy);
	}
}

void scale(std::vector<Vector2>& points, float s)
{
	scale(points, s, s);
}

void translate(Vector2& vector, float tx, float ty)
{
	vector.setX(vector.getX() + tx);
	vector.setY(vector.getY() + ty);
}

void translate(std::vector<Vector2>& points, float tx, float ty)
{
	for (auto& point : points)
	{
		translate(point, tx, ty);
	}
}

void drawPoly(const std::vector<Vector2>& points)
{
	for (auto it = points.begin(); it != points.end(); it++)
	{
		if ((it + 1) != points.end())
			drawLine(*it, *(it + 1));
		else if ((it + 1) == points.end())
			drawLine(*it,points.front());
		else
			break;
	}
}

int calculateXBezier(std::vector<Vector2>& points, float t)
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

int calculateYBezier(std::vector<Vector2>& points, float t)
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

void drawBezier(std::vector<Vector2> points) //Hacerlo cada cuatro puntos
{

	SDL_SetRenderDrawColor(gRenderer, 0xcc, 0x80, 0x00, 0xFF);
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
		for (unsigned i = 0 ; i < 3; i++ )
		{
			if(points.size() > 0)
			points.erase(points.begin());
		}
	}

	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0xAF, 0xAF, 0xFF);

}

//----Examen--------------------------------------------------

void drawLineColor(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	short signX, signY;
	int x, y, p;
	x = x1;
	y = y1;

	signX = (dx >= 0) ? 1 : -1;
	signY = (dy >= 0) ? 1 : -1;

	Vector2 tercio = Vector2(x2/3, y2/3) - Vector2(x1/3, y1/3);

	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x8F, 0x39, 0xFF);
	if (std::abs(dy) <= std::abs(dx))
	{
		p = (2 * dy * signY) - (dx * signX);

		for (int i = 0; i <= (dx * signX); i++)
		{
			SDL_RenderDrawPoint(gRenderer, x, y);
			if (p < 0)
			{
				if (x > tercio.getX())
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				if (x > (tercio.getX() * 2))
					SDL_SetRenderDrawColor(gRenderer, 0xCC, 0x06, 0x05, 0x9C);
				x = x + signX;
				p = (2 * dy * signY) + p;
			}
			else if (p >= 0)
			{
				if(x > tercio.getX())
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				if (x > (tercio.getX() * 2))
					SDL_SetRenderDrawColor(gRenderer, 0xCC, 0x06, 0x05, 0x9C);
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
			SDL_RenderDrawPoint(gRenderer, x, y);
			if (p < 0)
			{
				if (y > tercio.getY())
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				if (y > (tercio.getY() * 2))
					SDL_SetRenderDrawColor(gRenderer, 0xCC, 0x06, 0x05, 0x9C);
				y = y + signY;
				p = (2 * dx * signX) + p;
			}
			else if (p >= 0)
			{
				if (y > tercio.getY())
					SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				if (y > (tercio.getY() * 2))
					SDL_SetRenderDrawColor(gRenderer, 0xCC, 0x06, 0x05, 0x9C);
				x = x + signX;
				y = y + signY;
				p = (2 * dx * signX) - (2 * dy * signY) + p;
			}
		}
	}
	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0xAF, 0xAF, 0xFF);
}

void drawCarita()
{
	drawCircle(100, 100, 100);
	int x = 250;
	int y = 300;
	drawLine(70, 25, 70, 85); //ojo 1
	drawLine(140, 25, 140, 85); // ojo 2
	std::vector<Vector2> nariz;
	nariz.push_back(Vector2(100,90));
	nariz.push_back(Vector2(120,120));
	nariz.push_back(Vector2(90,120));
	drawStrip(nariz);

	std::vector<Vector2> boca;
	boca.push_back(Vector2(50, 140));
	boca.push_back(Vector2(70,165));
	boca.push_back(Vector2(140,165));
	boca.push_back(Vector2(160,140));
	drawPoly(boca);
}

void drawFillCircle(float r, float xc, float yc)
{
	float p, x, y;
	x = 0;
	y = r;
	p = 1 - r;

	SDL_SetRenderDrawColor(gRenderer, 0x80, 0x80, 0x00, 0xFF);

	for (int i = 0; x <= y; i++)
	{
		SDL_RenderDrawPoint(gRenderer, x + xc, y + yc); // 4
		SDL_RenderDrawPoint(gRenderer, -x + xc, y + yc);//5
		SDL_RenderDrawPoint(gRenderer, x + xc, -y + yc);//1
		SDL_RenderDrawPoint(gRenderer, -x + xc, -y + yc);//8
		SDL_RenderDrawPoint(gRenderer, y + xc, x + yc);//3
		SDL_RenderDrawPoint(gRenderer, -y + xc, x + yc);//6
		SDL_RenderDrawPoint(gRenderer, y + xc, -x + yc);//2
		SDL_RenderDrawPoint(gRenderer, -y + xc, -x + yc);//7


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
	SDL_SetRenderDrawColor(gRenderer, 0xAA, 0xAF, 0xAF, 0xFF);
}


//------------------------------------------------------------

int main(int argc, char* args[])
{
	std::vector<Vector2> points;
	setScreen();

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				int x, y;
				if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
				{
					points.push_back(Vector2(x, y));
				}
				else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
				{
					if (points.size() > 0)
					{
						points.pop_back();
					}
				}
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			SDL_RenderClear(gRenderer);
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

			drawPlain();

			//DrawLine(3,110,300,100);
			//a[0] = Vector2(20,20);
			//a[1] = Vector2(20,200);
			//a[2] = Vector2(200,200);
			//a[3] = Vector2(200,20);
			//a[4] = Vector2(400,20);
			//a[5] = Vector2(400,200);
			//a[6] = Vector2(200, 200);

			drawBezier(points);

			SDL_RenderPresent(gRenderer);
		}

	}

	//Free resources and close SDL
	close();

	return 0;
}