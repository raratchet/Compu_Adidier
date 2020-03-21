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

void trasnferPixels(Artist* artist, Artist* tmpArtist)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			Pixel* tmp = tmpArtist->getPixelAt(x, y);
			if (tmp->painted)
			{
				Pixel* art = artist->getPixelAt(x, y);
				
				art->painted = tmp->painted;
				art->color = tmp->color;
			}
		}
	}
}

void changeSDL_COLOR(char color)
{
	switch (color)
	{
	case 'r':
		SDL_SetRenderDrawColor(gRenderer, 0xCF, 0x00, 0x00, 0xFF);
		break;
	case 'g':
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0xAA, 0x00, 0xFF);
		break;
	case 'b':
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xB4, 0xFF);
		break;
	case 'n':
		SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
		break;
	case 'w':
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		break;
	case 'y':
		SDL_SetRenderDrawColor(gRenderer, 0xEB, 0xCD,0x00, 0xFF);
		break;
	case 'p':
		SDL_SetRenderDrawColor(gRenderer, 0x6B, 0x01, 0xA9, 0xFF);
		break;
	case 'a':
		SDL_SetRenderDrawColor(gRenderer, 0x6B, 0xB7, 0xA9, 0xFF);
		break;
	case 'f':
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x30, 0xD0, 0xFF);
		break;

	default:
		SDL_SetRenderDrawColor(gRenderer, 0xA0, 0xA0, 0xA0, 0xFF);
		break;
	}

}

void drawPixels(Artist* artist)
{
	char tmp = 0;

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			if (artist->getPixelAt(x, y)->painted)
			{
				char color = artist->getPixelAt(x, y)->color;
				if (color != tmp)
				{
					changeSDL_COLOR(color);
					tmp = color;
				}
				
				SDL_RenderDrawPoint(gRenderer, x, y);
			}
		}
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
		//Artist so we can draw other stuff;
		Artist artist = Artist(SCREEN_WIDTH,SCREEN_HEIGHT,tam);
		Artist tmpArtist = Artist(SCREEN_WIDTH,SCREEN_HEIGHT,tam);

		char mode = 0;
		char currentcolor = 'r';

		int x = 0 , y = 0;
		const Uint8* state;
		Uint32 mouse;

		std::vector<Vector2> points;

		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;

		//While application is running
		while (!quit)
		{

			artist.setColor(currentcolor);
			tmpArtist.setColor(currentcolor);

			if (mode == 'c')
			{
				if (points.size() != 0)
					tmpArtist.drawCircle(points[0].distance(Vector2(x, y)), points[0].getX(), points[0].getY());
			}

			if (mode == 'b')
			{
				if (points.size() != 0)
					tmpArtist.drawBezier(points);
			}

			if (mode == 'z')
			{
				if (points.size() != 0)
					tmpArtist.drawStrip(points);
			}

			if (mode == 'x')
			{
				if (points.size() != 0)
					tmpArtist.drawPoly(points);
			}

			while (SDL_PollEvent(&e) != 0)
			{
				state = SDL_GetKeyboardState(NULL);
				mouse = SDL_GetMouseState(&x, &y);

				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					if (mouse & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						if (mode == 'b')
						{
							points.push_back(Vector2(x, y));
						}

						if (mode == 'z')
						{
							points.push_back(Vector2(x, y));
						}

						if (mode == 'x')
						{
							points.push_back(Vector2(x, y));
						}

						if (mode == 'c')
						{
							points.push_back(Vector2(x, y));
						}

						if (mode == 'p')
						{
							artist.drawPoint(x, y);
						}

						if (mode == 'e')
						{
							artist.erasePoint(x, y);
						}
					}

				}

				if (e.type == SDL_MOUSEBUTTONUP)
				{
					if (mode == 'c')
					{
						points.clear();
						trasnferPixels(&artist,&tmpArtist);
					}
				}

				if (mouse & SDL_BUTTON_LEFT)
				{
					if (mode == 'p')
					{
						artist.drawPoint(x, y);
					}
				}

				if (state[SDL_SCANCODE_DELETE])
				{
					artist.clearPixels();
				}

				if (state[SDL_SCANCODE_RETURN])
				{
					if (mode == 'b' || mode == 'x' || mode == 'z')
					{
						points.clear();
						trasnferPixels(&artist, &tmpArtist);
					}
				}

				if (state[SDL_SCANCODE_C])
				{
					mode = 'c';
					points.clear();
				}

				if (state[SDL_SCANCODE_B])
				{
					mode = 'b';
					points.clear();
				}

				if (state[SDL_SCANCODE_P])
				{
					mode = 'p';
				}

				if (state[SDL_SCANCODE_E])
				{
					mode = 'e';
				}

				if (state[SDL_SCANCODE_Z])
				{
					mode = 'z';
					points.clear();
				}

				if (state[SDL_SCANCODE_X])
				{
					mode = 'x';
					points.clear();
				}

				if (state[SDL_SCANCODE_1])
				{
					currentcolor ='r';
				}
				if (state[SDL_SCANCODE_2])
				{
					currentcolor = 'g';
				}
				if (state[SDL_SCANCODE_3])
				{
					currentcolor = 'b';
				}
				if (state[SDL_SCANCODE_4])
				{
					currentcolor = 'n';
				}
				if (state[SDL_SCANCODE_5])
				{
					currentcolor = 'w';
				}
				if (state[SDL_SCANCODE_6])
				{
					currentcolor = 'y';
				}
				if (state[SDL_SCANCODE_7])
				{
					currentcolor = 'p';
				}
				if (state[SDL_SCANCODE_8])
				{
					currentcolor = 'a';
				}
				if (state[SDL_SCANCODE_9])
				{
					currentcolor = 'f';
				}

				//User requests quit
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			


			SDL_RenderClear(gRenderer);
			changeSDL_COLOR(0);

			drawPixels(&tmpArtist); 
			drawPixels(&artist);

			changeSDL_COLOR(0);
			SDL_RenderPresent(gRenderer);
			tmpArtist.clearPixels();
		}

	}

	//Free resources and close SDL
	close();

	return 0;
}