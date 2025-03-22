#include<stdbool.h>
#include<stdio.h>
#include"SDL2/SDL.h"


const int screen_width = 640;
const int screen_height = 480;


int main(int argc, char **argv)
{
	SDL_Window *window = NULL;
	SDL_Surface *screenSurface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL didn`t initialise  %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("SDl Tutorial", SDL_WINDOWPOS_UNDEFINED, 
					  SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window not created  %s\n", SDL_GetError());
		}
		else
		{ screenSurface = SDL_GetWindowSurface(window);
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface -> format, 0xFF, 0xFF, 0xFF));

			SDL_UpdateWindowSurface( window );
			
			SDL_Event e;
			bool quit = false;
			while(!quit)
			{
				while(SDL_PollEvent( &e ))
				{
					if( e.type == SDL_QUIT)
						quit = true;
				}
			}
		}
	}

	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}
