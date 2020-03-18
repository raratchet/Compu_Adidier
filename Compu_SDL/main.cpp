#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "artist.h"
#include "Vector2.h"
#include "Pixel.h"
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

int main(int argc, char* args[])
{
	setScreen();

	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		Pixel** pixels;
		pixels = new Pixel * [SCREEN_WIDTH];
		for (int i = 0; i < SCREEN_WIDTH; i++)
		{
			pixels[i] = new Pixel[SCREEN_HEIGHT];
		}

		//Artist so we can draw other stuff;
		Artist artist = Artist(&SCREEN_WIDTH, &SCREEN_HEIGHT, &tam,pixels);

		std::vector<Vector2> points;

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
					artist.drawBezier(points);
				}
				else if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_RIGHT))
				{
					if (points.size() > 0)
					{
						points.clear();
					}
				}
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			SDL_RenderClear(gRenderer);
			SDL_SetRenderDrawColor(gRenderer, 0xA0, 0xA0, 0xA0, 0xFF);

			artist.drawLine(0, 0, 100, 100);

			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xA0, 0x00, 0xFF);
			for (int x = 0; x < SCREEN_WIDTH; x++)
			{
				for (int y = 0; y < SCREEN_HEIGHT; y++)
				{
					if (pixels[x][y].painted)
						SDL_RenderDrawPoint(gRenderer, x, y);
				}
			}

			SDL_SetRenderDrawColor(gRenderer, 0xA0, 0xA0, 0xA0, 0xFF);

			SDL_RenderPresent(gRenderer);
		}

	}

	//Free resources and close SDL
	close();

	return 0;
}